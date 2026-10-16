#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Trail : public Entity
{
	float radius;
	sf::CircleShape graphics;
	sf::Clock spawnTime;
	float lifetime = 0.3f;

public:

	Trail(GameTexture& texture, sf::Vector2f position);

	EntityType getType() override;

	sf::Time getElapsedTime();

	float getLifetime();

	bool toBeDespawned(sf::RenderWindow& window) override;

	void update(float dt) override;

	std::optional<sf::Drawable*> getGraphics() override;
};