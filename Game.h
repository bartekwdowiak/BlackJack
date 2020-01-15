#pragma once
#include "Player.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;

class Game
{
	unique_ptr<Player> dealer = make_unique<Player>();
	//unique_ptr<Player> player = make_unique<Player>();
	vector<unique_ptr<Player>> playersVector;
	int nrOfPlayers = 4;
public:
	Game();
	~Game();
	void printTable();
	void mainGameLoop();
};

