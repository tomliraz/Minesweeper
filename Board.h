#pragma once
#include <string>
#include "Tile.h"
#include <random>
#include <vector>

using std::vector;
using std::string;

class Board
{
	bool debug;
	int Random(int min, int max);
	vector<Tile> tiles;
	bool Contains(vector<unsigned int> list, unsigned int element);
	unsigned int minesNum;
public:
	Board(int numMines, bool isDebug);
	Board(string fileName, bool isDebug);
	void Print();
	Tile& operator[](unsigned int index);
	unsigned int Size();
	void ToggleDebug();
	void FlagMines();
	void RevealMines();
	void UnflagAll();
	unsigned int getNumMines();
	bool IsDebug();
};

