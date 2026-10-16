#include "TextureHandler.h"
#include <print>
#include <ranges>

TextureHandler::TextureHandler()
{
}

void TextureHandler::loadTexture(std::string name, std::filesystem::path filePath,  std::string type)
{
	auto newTexture = std::make_shared<GameTexture>();
	newTexture->filePath = filePath;
	newTexture->name = name;
	newTexture->type = type;
	if (!newTexture->texture.loadFromFile(filePath))
	{
		std::print("File not found! {}", filePath.string());
	}
	textures.push_back(newTexture);
}

std::shared_ptr<GameTexture> TextureHandler::getTexture(std::string fileName)
{
	for (auto& texture : textures)
	{
		if (texture->name == fileName)
		{
			return texture;
		}
	}
	println("Texture not found! {}", fileName);
	return nullptr;
}

std::vector<std::shared_ptr<GameTexture>> TextureHandler::getAllTypeTextures(std::string requestedType)
{
	std::vector<std::shared_ptr<GameTexture>> typeTextures;
	for (auto& texture : textures)
	{
		if (texture->type == requestedType)
		{
			typeTextures.push_back(texture);
		}
	}
	return typeTextures;
}

void TextureHandler::clearTextures()
{
	textures.clear();
}