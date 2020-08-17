#pragma once
#include <SFML/Graphics.hpp>
class FlagCounter
{
	sf::Sprite digits[3];
	sf::Sprite digitsImage;
	int numMines;
	int count;
public:
	FlagCounter(int _numFlags, int _numMine);
	void Update(int _numFlags);
	sf::Sprite& operator[](unsigned int index);
};

