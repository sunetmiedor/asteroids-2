#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"

class Upgrade : public Entity
{
	float radius;
	sf::CircleShape graphics;
	sf::Vector2f velocity;
	int upgradeType; // 1 = spread, 2 = pierce, 3 = tracking

public:

	Upgrade(std::vector<std::shared_ptr<GameTexture>> upgradeTexture);

	EntityType getType() override;

	std::optional<sf::Drawable*> getGraphics() override;

	int getUpgradeType();

	float getRadius();

	void setPosition(sf::Vector2f newPosition) override;

	bool operator==(const Upgrade& other);

	void update(float dt) override;
};