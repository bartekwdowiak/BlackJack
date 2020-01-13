#pragma once
#include "Deck.h"
using std::string;

using std::vector;

class Player
{
	int playersMoney = 1'000;
	string name = "name";
public:
	vector<Card> playingHand;
	int handValue = 0;

	void setName(string);
	string getName();
	Player();
	~Player();
};

