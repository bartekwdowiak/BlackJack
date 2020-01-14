#pragma once
#include "Deck.h"
using std::string;
using std::vector;
using std::unique_ptr;

class Player
{
	int playersMoney = 1'000;
	string name = "name";
public:
	vector<unique_ptr<Card>> playingHand;
	int handValue = 0;

	void setName(string);
	string getName();
	Player();
	~Player();
};

