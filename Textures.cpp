#include "Textures.h"

map<string, sf::Texture> Textures::textures;

void Textures::LoadTexture(string textureName)
{
	string path = "images/" + textureName + ".png";
	textures[textureName].loadFromFile(path);
}


sf::Texture& Textures::Get(string textureName)
{
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}