#include "Upgrade.h"


Upgrade::Upgrade(std::vector<std::shared_ptr<GameTexture>> upgradeTexture)
{
	setDrawOrder(5);
	radius = 20.0f;
	upgradeType = (rand() % 3) + 1;
	graphics.setRadius(radius);
	graphics.setOrigin(sf::Vector2f(radius, radius));
	graphics.setTexture(&upgradeTexture[upgradeType - 1]->texture);
	velocity.y = 100.0f;
}

EntityType Upgrade::getType()
{
	return EntityType::Upgrade;
}

std::optional<sf::Drawable*> Upgrade::getGraphics()
{
	return std::optional<sf::Drawable*>(&graphics);
}

int Upgrade::getUpgradeType()
{
	return upgradeType;
}

float Upgrade::getRadius()
{
	return radius;
}

void Upgrade::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	graphics.setPosition(position);
}

bool Upgrade::operator==(const Upgrade& other)
{
	return position == other.position;
}

void Upgrade::update(float dt)
{
	position += velocity * dt;
	graphics.setPosition(position);
}