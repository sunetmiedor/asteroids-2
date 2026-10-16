#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <filesystem>

class GameTexture
{
public:
	std::filesystem::path filePath;
	std::string name;
	std::string type;
	sf::Texture texture;
};
