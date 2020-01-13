#include "stdafx.h"
#include "Deck.h"

using std::for_each;
using std::make_unique;
using std::move;


void Deck::shuffleDeck()
{
	// in black jack there are usually 6 decks
	for (int i = 0; i < nrOfDecks; i++)
	{
		// create a card for each combination of suit and rank, then put it into the deck
		for_each(suits.begin(), suits.end(), [this](string suit) 
		{
			for_each(ranks.begin(), ranks.end(), [&](pair<string, int> rank) 
			{
				unique_ptr<Card> card = make_unique<Card>(rank, suit);
				cards.push_back(move(card));
			});
		});
	}
}

Deck::Deck()
{
}


Deck::~Deck()
{
}
