#pragma once
#include "Dealer.h"

class Game
{
	Dealer dealer;
	Player player;
public:

	Game();
	~Game();
	void printTable();
	void mainGameLoop();
};

