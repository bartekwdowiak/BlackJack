#pragma once
#include "Deck.h"
using std::string;
using std::vector;
using std::array;
using std::unique_ptr;

enum Action { HIT = 1, STAND = 2, DOUBLE_DOWN = 3};

class Player
{
	string name = "John Doe";
public:
	vector<unique_ptr<Card>> playingHand;
	// TODO: make fields below private and add getters and setters
	int playersMoney = 1'000;
	int hardHandValue = 0;
	int softHandValue = 0;
	int betAmount = 0;
	bool isDealer = false;
	bool isBust = false;
	bool isPlayersTurn = false;
	bool isComputerControlled = true;
	bool isOutOfMoney = false;
	bool aceCountsAsOne = false;
	bool isBlackJack = false;

	array<array<Action, 10>, 18> basicStrategy =
	{{  /* Dealers card:
		     2            3            4            5            6            7            8            9            10           11  Players cards value: */
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//4
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//5
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//6
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//7
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//8
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//9
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//10
		{   HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT,         HIT },//11
		{   HIT,         HIT,       STAND,       STAND,       STAND,         HIT,         HIT,         HIT,         HIT,         HIT },//12
		{ STAND,       STAND,       STAND,       STAND,       STAND,         HIT,         HIT,         HIT,         HIT,         HIT },//13
		{ STAND,       STAND,       STAND,       STAND,       STAND,         HIT,         HIT,         HIT,         HIT,         HIT },//14
		{ STAND,       STAND,       STAND,       STAND,       STAND,         HIT,         HIT,         HIT,         HIT,         HIT },//15
		{ STAND,       STAND,       STAND,       STAND,       STAND,         HIT,         HIT,         HIT,         HIT,         HIT },//16
		{ STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND },//17
		{ STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND },//18
		{ STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND },//19
		{ STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND },//20
		{ STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND,       STAND } //21
	}};

	void setName(string);
	string getName();
	void resetScore();
	Player();
	Player(bool);
	~Player();
};

