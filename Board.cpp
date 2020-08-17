#include "Board.h"
#include <iostream>
#include "Textures.h"
#include <fstream>
using namespace std;

Board::Board(int numMines, bool isDebug)
{
	debug = false;
	minesNum = numMines;
	for (unsigned int i = 0; i < 400; i++)
	{
		Tile tile(false);
		tile.setPosition(float((i % 25) * 32), float((i / 25) * 32));
		tiles.push_back(tile);
	}
	
	vector<unsigned int> mineIndices;
	unsigned int index = (unsigned int)Random(0, 399);
	for (int i = 0; i < numMines; i++) 
	{
		while (Contains(mineIndices, index))
			index = (unsigned int)Random(0, 399);
		mineIndices.push_back(index);
	}

	for (unsigned int i = 0; i < mineIndices.size(); i++)
	{
		tiles[mineIndices[i]].setToMine();
	}

	
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		vector<Tile*> adjTiles;
		//top left
		if (i != 0 && i / 25 == (i - 1) / 25 && i > 24)
			adjTiles.push_back(&tiles[i - 26]);

		//bottom left
		if (i != 0 && i / 25 == (i - 1) / 25 && i < 375)
			adjTiles.push_back(&tiles[i + 24]);

		//top right
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25 && i > 24)
			adjTiles.push_back(&tiles[i - 24]);
				

		//bottom right
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25 && i < 375)
			adjTiles.push_back(&tiles[i + 26]);

		// The one to the left.
		if (i != 0 && i / 25 == (i - 1) / 25)
			adjTiles.push_back(&tiles[i - 1]);


		//The one to the right.
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25)
			adjTiles.push_back(&tiles[i + 1]);

		// The one above.
		if (i > 24)
			adjTiles.push_back(&tiles[i - 25]);

		// The one below.
		if (i < 375)
			adjTiles.push_back(&tiles[i + 25]);
				
		tiles[i].SetAdjTiles(adjTiles);

	}
	if (isDebug)
		ToggleDebug();
}

Board::Board(string fileName, bool isDebug)
{
	debug = false;
	string path = "boards/" + fileName + ".brd";
	ifstream file(path);
	unsigned int index = 0;
	char binMine;
	minesNum = 0;
	while (file.read(&binMine, 1))
	{
		
		if (binMine == '0' || binMine == '1')
		{
			Tile tile;
			if (binMine == '0')
				tile = Tile(false);
			else
			{
				tile = Tile(true);
				minesNum++;
			}
			tile.setPosition(float((index % 25) * 32), float((index / 25) * 32));
			tiles.push_back(tile);
			index++;
		}
	}

	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		vector<Tile*> adjTiles;
		//top left
		if (i != 0 && i / 25 == (i - 1) / 25 && i > 24)
			adjTiles.push_back(&tiles[i - 26]);

		//bottom left
		if (i != 0 && i / 25 == (i - 1) / 25 && i < 375)
			adjTiles.push_back(&tiles[i + 24]);

		//top right
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25 && i > 24)
			adjTiles.push_back(&tiles[i - 24]);


		//bottom right
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25 && i < 375)
			adjTiles.push_back(&tiles[i + 26]);

		// The one to the left.
		if (i != 0 && i / 25 == (i - 1) / 25)
			adjTiles.push_back(&tiles[i - 1]);


		//The one to the right.
		if (i != tiles.size() - 1 && i / 25 == (i + 1) / 25)
			adjTiles.push_back(&tiles[i + 1]);

		// The one above.
		if (i > 24)
			adjTiles.push_back(&tiles[i - 25]);

		// The one below.
		if (i < 375)
			adjTiles.push_back(&tiles[i + 25]);


		tiles[i].SetAdjTiles(adjTiles);
	}
	if (isDebug)
		ToggleDebug();
}


int Board::Random(int min, int max)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

bool Board::Contains(vector<unsigned int> list, unsigned int element)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i] == element)
			return true;
	}
	return false;
}

void Board::Print()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (i % 25 == 0 && i != 0)
			cout << endl;
		tiles[i].Print();
		cout << " ";
		
	}
}

Tile& Board::operator[](unsigned int index)
{
	return tiles[index];
}

unsigned int Board::Size()
{
	return tiles.size();
}


void Board::ToggleDebug()
{
	for (unsigned int i = 0; i< tiles.size(); i++)
		tiles[i].ToggleDebug();
	debug = !debug;
}

void Board::FlagMines()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		tiles[i].FlagMine();
}

void Board::RevealMines()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		tiles[i].RevealMine();
}

void Board::UnflagAll()
{
	for (Tile tile : tiles)
		tile.Unflag();
}

unsigned int Board::getNumMines()
{
	return minesNum;
}

bool Board::IsDebug()
{
	return debug;
}