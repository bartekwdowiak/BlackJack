#include "stdafx.h"
#include "Player.h"


void Player::setName(string name)
{
	this->name = name;
}

string Player::getName()
{
	return this->name;
}

void Player::resetScore()
{
	this->handValue = 0;
	this->playingHand.clear();
	this->isBust = false;
	this->betAmount = 0;
}

Player::Player()
{
}

Player::Player(bool isDealer)
{
	this->isDealer = isDealer;
}

Player::~Player()
{
}
