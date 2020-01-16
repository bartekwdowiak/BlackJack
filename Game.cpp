#include "stdafx.h"
#include "Game.h"

#define MAX_BET 300
#define MIN_BET 10
#define DELAY_OF_COMPUTER_ACTION 500
#define WINNING_HAND_MULTIPLIER 2
#define BLACK_JACK_MULTIPLIER 2.5
#define	DEALERS_STOP_AMOUNT 17
#define PLAYERS_MAX_POINTS 21
#define DIFFERENCE_BETWEEN_SOFT_AND_HARD_HAND 10

using std::unique_ptr;
using std::make_unique;
using std::for_each;
using std::cout;
using std::endl;
using std::cin;
using std::endl;
using std::rand;

Game::Game()
{
	for (int i = 0; i < nrOfPlayers; i++)
	{
		unique_ptr<Player> player = make_unique<Player>();
		this->playersVector.push_back(move(player));
	}
}

Game::~Game()
{
}

void Game::printTable()
{
	auto printCard = [](const unique_ptr<Card>& card) 
	{
		cout << "|" << card->rank.first << " " << card->suit << "|";
	};

	auto printPlayer = [&](const unique_ptr<Player>& player)
	{
		cout << "PLAYER" << ((player->isPlayersTurn) ? " <-  " : "     ");
		cout << "SCORE: " << player->hardHandValue;
		if (player->softHandValue > 0)
		{
			cout << " OR: " << player->softHandValue;
		}
		cout << (player->isBust ? " BUST" : "") << endl;
		cout << player->getName() << "  Money: " << player->playersMoney << " Bet: " << player->betAmount << endl;

		for_each(player->playingHand.begin(), player->playingHand.end(), printCard);
		cout << endl << endl;
	};

	system("cls");

	cout << "                                TABLE RULES: MAX BET - " << MAX_BET << "$  MIN BET - " << MIN_BET << "$" << endl;
	cout << "                                        DEALER HITS UNTILL HARD 17" << endl;

	//print dealers hand and score
	cout << "DEALER" << ((dealer->isPlayersTurn) ? " <-  " : "     ");
	cout << "SCORE: " << dealer->hardHandValue;
	if (dealer->softHandValue > 0)
	{
		cout << " OR: " << dealer->softHandValue;
	}
	cout << (dealer->isBust ? " BUST" : "") << endl;
	for_each(dealer->playingHand.begin(), dealer->playingHand.end(), printCard);
	cout << endl << endl;

	for_each(playersVector.begin(), playersVector.end(), printPlayer);
}

void Game::mainGameLoop()
{
	bool gameIsRunning = true;
	bool dealingCards;
	int option;
	int playersSeat = 0;
	string playersName = "";

	srand(time(0));

	cout << "TAKE A SEAT:" << endl;
	cout << "[0] [1] [2] [3]" << endl;
	cin >> playersSeat;
	cout << "WHAT'S YOUR NAME?" << endl;
	cin >> playersName;

	playersVector[playersSeat]->isComputerControlled = false;
	playersVector[playersSeat]->setName(playersName);

	while (gameIsRunning)
	{
		dealingCards = true;

		unique_ptr<Deck> deck = make_unique<Deck>();
		deck->createCards();
		deck->shuffleDeck();
	
		auto takeBet = [&](unique_ptr<Player>& player)
		{
			player->isPlayersTurn = true;
			int bet = 0;
			if (player->isComputerControlled && !player->isOutOfMoney)
			{
				printTable();
				Sleep(DELAY_OF_COMPUTER_ACTION);
				bet = (player->playersMoney > MAX_BET) ? ((rand() % 30 + 1)*10) : ((rand() % player->playersMoney / 10 + 1)*10);
			}
			else if (!player->isComputerControlled)
			{
				printTable();
				cout << "How much do you want to bet?" << endl << "Enter amount: ";
				cin >> bet;
				cout << endl;

				while (bet < MIN_BET || bet > MAX_BET || bet > player->playersMoney || bet % MIN_BET != 0)
				{
					cout << "Invalid amount! Try Again: ";
					cin >> bet;
					cout << endl;
				}
			}
			player->playersMoney -= bet;
			player->betAmount = bet;
			player->isPlayersTurn = false;
		};

		auto checkScore = [](unique_ptr<Player>& player)
		{
			if (player->hardHandValue > PLAYERS_MAX_POINTS)
			{
				if (player->softHandValue == 0)
				{
					player->isBust = true;
				}
				else
				{
					player->hardHandValue = player->softHandValue;
					player->softHandValue = 0;
				}
			}
			else if (player->hardHandValue == PLAYERS_MAX_POINTS && player->playingHand.size() == 2)
			{
				player->isBlackJack = true;
				player->softHandValue = 0;
			}
		};

		auto dealCard = [&](unique_ptr<Player>& player)
		{
			if (!player->isOutOfMoney)
			{
				player->playingHand.push_back(move(deck->cards.back()));
				deck->cards.pop_back();
				player->hardHandValue += player->playingHand.back()->rank.second;
				if (player->softHandValue > 0)
				{
					player->softHandValue += player->playingHand.back()->rank.second;
				}
				printTable();
				Sleep(DELAY_OF_COMPUTER_ACTION);
			}

			// If there's an ACE on players hand, he might have a soft hand
			// This can be done only once per turn thus aceCountsAsOne flag check
			if (std::any_of(player->playingHand.begin(), player->playingHand.end(),
				[](const unique_ptr<Card>& card) { return card->rank.second == 11; }) &&
				!player->aceCountsAsOne &&
				!player->isBlackJack)
			{
				player->softHandValue = player->hardHandValue - DIFFERENCE_BETWEEN_SOFT_AND_HARD_HAND;
				player->aceCountsAsOne = true;
			}
		};

		auto playTurn = [&](unique_ptr<Player>& player)
		{
			if (!player->isBlackJack && !player->isOutOfMoney)
			{
				player->isPlayersTurn = true;
				option = HIT;
				if (player->isComputerControlled)
				{
					while ((option == HIT) && (!player->isBust))
					{
						printTable();
						option = player->basicStrategy[player->hardHandValue - 4][dealer->hardHandValue - 2];
						Sleep(DELAY_OF_COMPUTER_ACTION);
						if (option == HIT)
						{
							dealCard(player);
							checkScore(player);
						}
					}
				}
				else
				{
					while ((option == HIT) && (!player->isBust))
					{
						printTable();
						cout << "Pick option: [1] HIT, [2] STAND" << endl;
						cin >> option;
						if (option == HIT)
						{
							dealCard(player);
							checkScore(player);
						}
					}
				}
				player->isPlayersTurn = false;
			}
		};

		auto roundSummary = [&](unique_ptr<Player> &player) 
		{
			if (player->playersMoney < MIN_BET && (player->isBust || player->hardHandValue < dealer->hardHandValue))
			{
				player->isOutOfMoney = true;
			}
			else if (player->isBlackJack)
			{
				player->playersMoney += static_cast<int>(player->betAmount * BLACK_JACK_MULTIPLIER);
			}
			else if (player->hardHandValue > dealer->hardHandValue && !player->isBust)
			{
				player->playersMoney += player->betAmount * WINNING_HAND_MULTIPLIER;
			}
			else if (player->hardHandValue == dealer->hardHandValue && !player->isBust)
			{
				player->playersMoney += player->betAmount;
			}
			player->resetScore();
		};

		// Take bets
		printTable();
		for_each(playersVector.begin(), playersVector.end(), takeBet);
		
		// Opening sequence - deal 2 cards to every player and 1 card to the dealer
		for_each(playersVector.begin(), playersVector.end(), dealCard);
		dealCard(dealer);
		for_each(playersVector.begin(), playersVector.end(), dealCard);
		for_each(playersVector.begin(), playersVector.end(), checkScore);

		// Players turns
		for_each(playersVector.begin(), playersVector.end(), playTurn);

		// Dealers turn
		while (dealer->hardHandValue < DEALERS_STOP_AMOUNT)
		{
			// If there's an ACE on players hand, he might have a soft hand
			// This can be done only once per turn thus aceCountsAsOne flag check
			//if (std::any_of(dealer->playingHand.begin(), dealer->playingHand.end(),
			//	[](const unique_ptr<Card>& card) { return card->rank.second == 11; }) &&
			//	!dealer->aceCountsAsOne)
			//{
			//	dealer->softHandValue = dealer->hardHandValue - DIFFERENCE_BETWEEN_SOFT_AND_HARD_HAND;
			//	dealer->aceCountsAsOne = true;
			//}

			dealCard(dealer);
			checkScore(dealer);
		}
		printTable();

		for_each(playersVector.begin(), playersVector.end(), roundSummary);
		dealer->resetScore();
		
		if (!playersVector[playersSeat]->isOutOfMoney)
		{
			cout << "END OF TURN, WANT TO BET AGAIN?: [1] YES [2] NO" << endl;
			cin >> option;
		}

		if (option == 2 || playersVector[playersSeat]->isOutOfMoney)
		{
			system("cls");
			cout << "Thank you for playing!" << endl;
			cout << "Your final money: " << playersVector[playersSeat]->playersMoney << endl;
			gameIsRunning = false;
		}
	}
}