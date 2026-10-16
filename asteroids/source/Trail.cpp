#include "Trail.h"
#include "utils.h"

Trail::Trail(GameTexture& texture, sf::Vector2f position)
{
	radius = 5.0f;
	setDrawOrder(1);
	this->position = position;
	graphics.setPosition(position);
	graphics.setTexture(&texture.texture);
	graphics.setRadius(radius);
	graphics.setOrigin(sf::Vector2f(radius, radius));
}

EntityType Trail::getType()
{
	return EntityType::Trail;
}

sf::Time Trail::getElapsedTime()
{
	return spawnTime.getElapsedTime();
}

float Trail::getLifetime()
{
	return lifetime;
}

bool Trail::toBeDespawned(sf::RenderWindow& window)
{
	return invLerp(getElapsedTime().asSeconds(), 0.0f, lifetime) >= 1.0f;
}


void Trail::update(float dt)
{
	float n = invLerp(getElapsedTime().asSeconds(), 0.0f, lifetime);
	graphics.setFillColor(sf::Color(255, 255, 255, std::uint8_t(lerp(pow(n, 0.4f), 255.0f, 0.0f))));
	float s = lerp(pow(n, 1.0f), 1.0f, 5.0f);
	graphics.setScale(sf::Vector2f(s, s));
	graphics.rotate(sf::radians(3.141592f * 2.0f) * dt);	
}

std::optional<sf::Drawable*> Trail::getGraphics()
{
	return std::optional<sf::Drawable*>(&graphics);
}
