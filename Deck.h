#pragma once
#include "Card.h"

using std::string;
using std::vector;
using std::map;
using std::unique_ptr;

class Deck
{
	const int nrOfDecks = 6;
	// suits of cards, letters respond to Hearts, Diamonds, Clubs and Spades
	vector<string> suits{ "H", "D", "C", "S" };
	// rank of a card and its value in black jack
	map<string, int> ranks{
	{ " 2", 2 },
	{ " 3", 3 },
	{ " 4", 4 },
	{ " 5", 5 },
	{ " 6", 6 },
	{ " 7", 7 },
	{ " 8", 8 },
	{ " 9", 9 },
	{ "10", 10 },
	{ " J", 10 },
	{ " Q", 10 },
	{ " K", 10 },
	{ " A", 10 } };
public:
	vector<unique_ptr<Card>> cards;
	void shuffleDeck();
	Deck();
	~Deck();
};

