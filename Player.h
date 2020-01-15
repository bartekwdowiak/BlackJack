#pragma once
#include "Deck.h"
using std::string;
using std::vector;
using std::unique_ptr;

class Player
{
	string name = "John Doe";
public:
	vector<unique_ptr<Card>> playingHand;
	// TODO: make fields below private and add getters and setters
	int playersMoney = 1'000;
	int handValue = 0;
	int betAmount = 0;
	bool isDealer = false;
	bool isBust = false;
	bool isPlayersTurn = false;
	bool isComputerControlled = true;
	bool isOutOfMoney = false;

	void setName(string);
	string getName();
	void resetScore();
	Player();
	Player(bool);
	~Player();
};

