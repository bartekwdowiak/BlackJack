#include "stdafx.h"
#include "Game.h"

using std::unique_ptr;
using std::make_unique;
using std::for_each;
using std::cout;
using std::endl;
using std::cin;
using std::endl;
using std::rand;

// TODO: outOfMoney, NPC basic strategy

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
		cout << "|" << card->rank.first << " " << card->suit << "|" << endl;
	};

	auto printPlayer = [&](const unique_ptr<Player>& player)
	{
		cout << ((player->isDealer) ? "DEALER" : "PLAYER") << ((player->isPlayersTurn) ? " <-  " : "     ");
		cout << "SCORE: " << player->handValue << endl;
		cout << player->getName() << "  Money: " << player->playersMoney << " Bet: " << player->betAmount << endl;

		for_each(player->playingHand.begin(), player->playingHand.end(), printCard);
		cout << endl << endl;
	};

	system("cls");

	//print dealers hand and score
	cout << "DEALER" << ((dealer->isPlayersTurn) ? " <-  " : "     ");
	cout << "SCORE: " << dealer->handValue << endl << endl;
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
			if (player->isComputerControlled)
			{
				printTable();
				bet = (player->playersMoney > 300) ? ((rand() % 30 + 1)*10) : ((rand() % player->playersMoney / 10 + 1)*10);
			}
			else
			{
				printTable();
				cout << "How much do you want to bet?" << endl << "Enter amount: ";
				cin >> bet;
				cout << endl;

				while (bet < 10 || bet > 300 || bet > player->playersMoney || bet % 10 != 0)
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
			if (player->handValue > 21)
			{
				player->isBust = true;
			}
		};

		auto dealCard = [&](unique_ptr<Player>& player)
		{
			player->playingHand.push_back(move(deck->cards.back()));
			deck->cards.pop_back();
			player->handValue += player->playingHand.back()->rank.second;
			printTable();
			Sleep(500);
		};

		auto playTurn = [&](unique_ptr<Player>& player)
		{
			player->isPlayersTurn = true;
			option = 1;
			while ((option == 1) && (!player->isBust))
			{
				printTable();
				cout << "Pick option: [1] HIT, [2] PASS" << endl;
				cin >> option;
				if (option == 1)
				{
					dealCard(player);
					checkScore(player);
				}
			}
			player->isPlayersTurn = false;
		};

		// Take bets
		printTable();
		for_each(playersVector.begin(), playersVector.end(), takeBet);


		// Opening sequence - deal 2 cards to every player and 1 card to the dealer
		for_each(playersVector.begin(), playersVector.end(), dealCard);
		dealCard(dealer);
		for_each(playersVector.begin(), playersVector.end(), dealCard);

		// Players turns
		for_each(playersVector.begin(), playersVector.end(), playTurn);

		// Dealers turn
		while (dealer->handValue < 17)
		{
			dealCard(dealer);
			checkScore(dealer);
		}
		printTable();
		for_each(playersVector.begin(), playersVector.end(), [](unique_ptr<Player> &player) { player->resetScore(); });
		dealer->resetScore();
		cout << "END OF TURN" << endl;
		system("pause");
	}

	cout << "Thank you for playing!" << endl;
}