#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;

class Tile : public sf::Sprite
{
	bool debug;
	bool isMine;
	bool isRevealed;
	bool isFlagged;
	int numAdjMines;
	vector<Tile*> adjTiles;

public:
	
	Tile(bool _isMine);
	Tile();
	bool LeftClick(unsigned int& counter);
	bool IsRevealed();
	void RightClick(unsigned int &flags);
	bool IsFlagged();
	void Print();
	void setToMine();
	bool IsMine();
	void SetAdjTiles(vector<Tile*> &_adjTiles);
	void ToggleDebug();
	void FlagMine();
	bool IsDebug();
	void RevealMine();
	void Unflag();
};

