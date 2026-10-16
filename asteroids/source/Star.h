#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Star : public Entity
{
	float radius;
	sf::CircleShape graphics;
	sf::Vector2f velocity;
	bool layer; // true = foreground, false = background

public:

	Star();

	EntityType getType() override;

	void setPosition(sf::Vector2f newPosition) override;

	bool toBeDespawned(sf::RenderWindow& window) override;

	void update(float dt) override;

	bool operator== (const Star& other) const;

	std::optional<sf::Drawable*> getGraphics() override;
};