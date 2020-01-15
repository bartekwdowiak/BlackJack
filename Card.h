#pragma once
using std::string;
using std::pair;

class Card
{
public:
	string suit;
	pair<string, int> rank;
	Card(pair<string, int>, string);
	Card();
	~Card();
};

