#include "Entity.h"
#include "utils.h"
#include "SFML/Window.hpp"

sf::Vector2f Entity::getPosition()
{
	return position;
}

void Entity::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
}

int Entity::getDrawOrder()
{
	return drawOrder;
}

void Entity::setDrawOrder(int newDrawOrder)
{
	drawOrder = newDrawOrder;
}

bool Entity::toBeDespawned(sf::RenderWindow& window)
{
	return !isPointInMinMaxBox(getPosition(), -sf::Vector2f(window.getSize()), 2.0f * sf::Vector2f(window.getSize()));
}

void Entity::update(float dt)
{

}

void Entity::update(float dt, sf::RenderWindow& window, TextureHandler& textureHandler, std::vector<std::shared_ptr<Entity>>& entities, bool debugMode)
{
}

std::optional<sf::Drawable*> Entity::getGraphics()
{
	return {};
}

std::optional<sf::Shape*> Entity::getColliderShape()
{
	return {};
}

//bool Entity::operator==(Entity& other)
//{
//	return position == other.position;
//}