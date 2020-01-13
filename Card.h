#pragma once
using std::string;
using std::pair;

class Card
{
public:
	string suit;
	pair<string, int> rank;
	int value;
	Card(pair<string, int>, string);
	Card();
	~Card();
};

