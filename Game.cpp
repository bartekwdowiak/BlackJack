#include "stdafx.h"
#include "Game.h"

using std::unique_ptr;
using std::make_unique;
using std::for_each;
using std::cout;
using std::endl;
using std::cin;
using std::endl;


Game::Game()
{
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

	//print dealers hand and score
	cout << "DEALER" << endl;
	cout << "Score: " << dealer->handValue << endl;
	for_each(dealer->playingHand.begin(), dealer->playingHand.end(), printCard);
	cout << endl << endl << endl << endl;


	// print players hand and score
	for_each(player->playingHand.begin(), player->playingHand.end(), printCard);
	cout << endl;
	cout << "Score: " << player->handValue << endl;
	cout << "Player: " << player->getName() << endl;
}

void Game::dealCard(unique_ptr<Player> &player, unique_ptr<Deck> &deck)
{
	player->playingHand.push_back(move(deck->cards.back()));
	deck->cards.pop_back();
	player->handValue += player->playingHand.back()->rank.second;
}

void Game::mainGameLoop()
{
	bool gameIsRunning = true;
	bool dealingCards;
	int option;

	while (gameIsRunning)
	{
		option = 0;
		dealingCards = true;

		unique_ptr<Deck> deck = make_unique<Deck>();
		deck->createCards();
		deck->shuffleDeck();

		while (dealingCards)
		{
			printTable();

			cout << "Pick option: [1] continue, [2] end" << endl;
			cin >> option;

			dealCard(player, deck);

			system("cls");
		}
		if (option == 2)
		{
			system("cls");
			break;
		}

		system("cls");
	}

	cout << "Thank you for playing!" << endl;
}