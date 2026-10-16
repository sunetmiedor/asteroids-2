#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <optional>
#include <filesystem>
#include "GameTexture.h"

class TextureHandler
{
	std::vector<std::shared_ptr<GameTexture>> textures;

public:
	TextureHandler();
	
	void loadTexture(std::string name, std::filesystem::path filePath,  std::string type);

	std::shared_ptr<GameTexture> getTexture(std::string fileName);

	std::vector<std::shared_ptr<GameTexture>> getAllTypeTextures(std::string requestedType);

	void clearTextures();
};