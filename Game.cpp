#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::printTable()
{
	using std::cout;
	using std::endl;
	using std::for_each;

	//auto printCard = [](const Card& card) 
	//{ 
	//	cout << "|" << card.rank << " " << card.suit << "|";
	//};

	// print dealers hand and score
	//cout << "DEALER" << endl;
	//cout << "Score: " << dealer.handValue << endl;
	//for_each(dealer.playingHand.begin(), dealer.playingHand.end(), printCard);
	//cout << endl << endl << endl << endl;


	//// print players hand and score
	//for_each(player.playingHand.begin(), player.playingHand.end(), printCard);
	//cout << endl;
	//cout << "Score: " << player.handValue << endl;
	//cout << "Player: " << player.getName() << endl;
}

void Game::mainGameLoop()
{
	using std::cout;
	using std::cin;
	using std::endl;

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		int option = 0;

		printTable();

		cout << "Pick option: [1] continue, [2] end" << endl;
		cin >> option;

		if (option == 2)
		{
			break;
		}
	}
}