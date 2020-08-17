#include "FlagCounter.h"
#include "Textures.h"

FlagCounter::FlagCounter(int _numFlags, int _numMines)
{
	for (int i = 0; i < 3; i++)
	{
		digits[i].setTexture(Textures::Get("digits"));
		digits[i].setPosition(float(21 * i), float(512));
	}
	numMines = _numMines;
	Update(_numFlags);
}

void FlagCounter::Update(int _numFlags)
{
	count = numMines - _numFlags;

	if (count >= 0)
	{
		int temp = count;
		digits[2].setTextureRect(sf::IntRect(21 * (temp % 10), 0, 21, 32));
		temp /= 10;
		digits[1].setTextureRect(sf::IntRect(21 * (temp % 10), 0, 21, 32));
		temp /= 10;
		digits[0].setTextureRect(sf::IntRect(21 * (temp % 10), 0, 21, 32));
	}
	else
	{
		int temp = count * (-1);
		digits[2].setTextureRect(sf::IntRect(21 * (temp % 10), 0, 21, 32));
		temp /= 10;
		digits[1].setTextureRect(sf::IntRect(21 * (temp % 10), 0, 21, 32));
		digits[0].setTextureRect(sf::IntRect(210, 0, 21, 32));
	}
}

sf::Sprite &FlagCounter::operator[](unsigned int index)
{
	return digits[index];
}