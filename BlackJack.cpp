#include "stdafx.h"
#include "Game.h"
using std::cout;
using std::endl;

int main()
{
	Game *BlackJack = new Game();
	BlackJack->mainGameLoop();

    return 0;
}

