#pragma once

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Tile.h"
#include<iostream>
#include <random>
#include "Board.h"
#include "FlagCounter.h"
using namespace std;

void DrawTile(sf::RenderWindow &window, Tile &tile);

int main()
{
	bool gameOver = false;
	unsigned int tilesClicked = 0;
	Board board(50, false);
	unsigned int numFlags = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	FlagCounter counter(numFlags, 50);

	sf::Sprite debug;
	debug.setTexture(Textures::Get("debug"));
	debug.setPosition(496, 512);
	
	sf::Sprite face;
	face.setTexture(Textures::Get("face_happy"));
	face.setPosition(368, 512);

	sf::Sprite test1;
	test1.setTexture(Textures::Get("test_1"));
	test1.setPosition(560, 512);

	sf::Sprite test2;
	test2.setTexture(Textures::Get("test_2"));
	test2.setPosition(624, 512);

	sf::Sprite test3;
	test3.setTexture(Textures::Get("test_3"));
	test3.setPosition(688, 512);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed) 
			{
				auto mousePos = sf::Mouse::getPosition(window);
				for (unsigned int i = 0; i < board.Size(); i++) 
				{
					if (board[i].getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
						{
							bool clickedMine = board[i].LeftClick(tilesClicked);
							if (clickedMine)
							{
								gameOver = true;
								face.setTexture(Textures::Get("face_lose"));
								board.RevealMines();
							}
							else if (tilesClicked == board.Size()-board.getNumMines()) 
							{
								gameOver = true;
								face.setTexture(Textures::Get("face_win"));
								board.FlagMines();
							}
						}
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !gameOver)
						{
							
							board[i].RightClick(numFlags);
							counter.Update(numFlags);
						}
					}
				}
				if (debug.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						board.ToggleDebug();
					}

				if (face.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						bool isDebug = board.IsDebug();
						board = Board(50, isDebug);
						numFlags = 0;
						counter = FlagCounter(numFlags, board.getNumMines());
						face.setTexture(Textures::Get("face_happy"));
						gameOver = false;
						tilesClicked = 0;
					}
				if (test1.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						face.setTexture(Textures::Get("face_happy"));
						bool isDebug = board.IsDebug();
						board = Board("testboard1", isDebug);
						numFlags = 0;
						gameOver = false;
						counter = FlagCounter(numFlags, board.getNumMines());
						tilesClicked = 0;
					}
				if (test2.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						face.setTexture(Textures::Get("face_happy"));
						bool isDebug = board.IsDebug();
						board = Board("testboard2", isDebug);
						numFlags = 0;
						gameOver = false;
						counter = FlagCounter(numFlags, board.getNumMines());
						tilesClicked = 0;
					}
				if (test3.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameOver)
					{
						face.setTexture(Textures::Get("face_happy"));
						bool isDebug = board.IsDebug();
						board = Board("testboard3", isDebug);
						numFlags = 0;
						counter = FlagCounter(numFlags, board.getNumMines());
						tilesClicked = 0;
					}
			}
		}
		window.clear(sf::Color(255, 255, 255, 255));

		//========== Draw Stuff ============//
		window.draw(debug);
		window.draw(face);
		window.draw(test1);
		window.draw(test2);
		window.draw(test3);

		for(unsigned int i=0; i<board.Size(); i++)
			DrawTile(window, board[i]);
		for (int i = 0; i < 3; i++)
			window.draw(counter[i]);

		window.display();
	}

	return 0;
}


void DrawTile(sf::RenderWindow &window, Tile &tile) {
	if (tile.IsRevealed())
	{
		sf::Sprite revealedTile;
		revealedTile.setTexture(Textures::Get("tile_revealed"));
		revealedTile.setPosition(tile.getPosition());
		window.draw(revealedTile);
	}
	else
	{
		sf::Sprite hiddenTile;
		hiddenTile.setTexture(Textures::Get("tile_hidden"));
		hiddenTile.setPosition(tile.getPosition());
		window.draw(hiddenTile);
	}
	if (tile.IsRevealed() || (tile.IsDebug() && tile.IsMine()))
		window.draw(tile);
	
	if (tile.IsFlagged())
	{
		sf::Sprite flag;
		flag.setTexture(Textures::Get("flag"));
		flag.setPosition(tile.getPosition());
		window.draw(flag);
	}
}
