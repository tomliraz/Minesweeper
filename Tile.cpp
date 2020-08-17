#include "Tile.h"
#include "Textures.h"
#include <iostream>

using namespace std;

Tile::Tile(bool _isMine)
{
	debug = false;
	isMine = _isMine;
	isRevealed = false;
	isFlagged = false;
	if (_isMine)
		setTexture(Textures::Get("mine"));
	numAdjMines = 0;
}

Tile::Tile() 
{
	debug = false;
	isMine = false;
	isRevealed = false;
	isFlagged = false;
	numAdjMines = 0;
}

bool Tile::LeftClick(unsigned int &counter)
{
	if (!isRevealed && !isFlagged)
	{
		isRevealed = true;
		if (isMine)
			return true;
		if (numAdjMines == 0)
			for (unsigned int i = 0; i < adjTiles.size(); i++)
				adjTiles[i]->LeftClick(counter);
		counter++;
	}
	return false;
}

bool Tile::IsRevealed()
{
	return isRevealed;
}

void Tile::RightClick(unsigned int &flags)
{
	if (!isRevealed) {
		if (isFlagged) {
			isFlagged = false;
			flags--;
		}
		else if (!isFlagged) {
			isFlagged = true;
			flags++;
		}
	}
}

bool Tile::IsFlagged()
{
	return isFlagged;
}

void Tile::Print()
{
	if (isMine)
		cout << "M";
	else
		cout << "n";
}

void Tile::setToMine()
{
	isMine = true;
	setTexture(Textures::Get("mine"));
}

bool Tile::IsMine()
{
	return isMine;
}

void Tile::SetAdjTiles(vector<Tile*> &_adjTiles)
{
	adjTiles = _adjTiles;
	for (unsigned int i = 0; i < adjTiles.size(); i++)
		if (adjTiles[i]->isMine)
			numAdjMines++;
	if (!isMine)
		if(numAdjMines == 0)
			setTexture(Textures::Get("tile_revealed"));
		else
			setTexture(Textures::Get("number_" + to_string(numAdjMines)));
}

void Tile::ToggleDebug()
{
	if (!debug)
		debug = true;
	else
		debug = false;
}

void Tile::FlagMine()
{
	if (isMine)
	{
		isFlagged = true;
	}
}

bool Tile::IsDebug()
{
	return debug;
}

void Tile::RevealMine()
{
	if (isMine)
	{
		isRevealed = true;
		isFlagged = false;
	}
}

void Tile:: Unflag()
{
	isFlagged = false;
}