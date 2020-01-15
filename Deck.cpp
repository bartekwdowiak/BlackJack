#include "stdafx.h"
#include "Deck.h"

using std::for_each;
using std::make_unique;
using std::move;
using std::random_shuffle;
using std::cout;
using std::endl;

void Deck::createCards()
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

void Deck::shuffleDeck()
{
	random_shuffle(cards.begin(), cards.end());
}

Deck::Deck()
{
}


Deck::~Deck()
{
}
