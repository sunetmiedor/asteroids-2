#include "Star.h"
#include <SFML/Graphics.hpp>
#include "utils.h"

Star::Star()
{
	layer = std::rand() % 2;
	if (layer)
	{
		velocity.y = 125.0f;
		graphics.setFillColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		velocity.y = 75.0f;
		graphics.setFillColor(sf::Color(255, 255, 255, 150));
	}
	radius = uniformInclusive(1, 3);
	setDrawOrder(0);
	graphics.setRadius(radius);
	graphics.setOrigin(sf::Vector2f(radius, radius));
}

EntityType Star::getType()
{
	return EntityType::Star;
}

void Star::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	graphics.setPosition(position);
}

bool Star::toBeDespawned(sf::RenderWindow& window)
{
	return position.y > window.getSize().y*2.0f;
}

void Star::update(float dt)
{
	setPosition(position + velocity * dt);
}

bool Star::operator== (const Star& other) const
{
	return position == other.position;
}

std::optional<sf::Drawable*> Star::getGraphics()
{
	return std::optional<sf::Drawable*>(&graphics);
}
