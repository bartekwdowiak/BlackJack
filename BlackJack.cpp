#include "stdafx.h"
#include "Game.h"
using std::cout;
using std::endl;

int main()
{
	Game *BlackJack = new Game();

	Deck deck;

	deck.shuffleDeck();

	BlackJack->mainGameLoop();

    return 0;
}

