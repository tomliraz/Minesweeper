#pragma once
#include <SFML/graphics.hpp>
#include <map>
#include <string>

using std::map;
using std::string;

class Textures
{
	static map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
public:
	
	static sf::Texture& Get(string textureName);
};

