#pragma once
#include "Dealer.h"

using std::unique_ptr;
using std::make_unique;

class Game
{
	unique_ptr<Dealer> dealer = make_unique<Dealer>();
	unique_ptr<Player> player = make_unique<Player>();
public:
	Game();
	~Game();
	void printTable();
	void dealCard(unique_ptr<Player> &player, unique_ptr<Deck> &deck);
	void mainGameLoop();
};

