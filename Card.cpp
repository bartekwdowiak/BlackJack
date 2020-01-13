#include "stdafx.h"
#include "Card.h"


Card::Card(pair<string, int> rank, string suit)
{
	this->rank = rank;
	this->suit = suit;
}

Card::Card()
{
}

Card::~Card()
{
}
