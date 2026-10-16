#pragma once
#include <SFML\Graphics.hpp>
#include "TextureHandler.h"

enum class EntityType
{
	Ship,
	Asteroid,
	Projectile,
	HomingProjectile,
	Trail,
	Upgrade,
	Star
};

class Entity
{
protected:

	sf::Vector2f position;
	int drawOrder = 0; //lower drawOrder drawn first
	EntityType type;
	
public:

	sf::Vector2f getPosition();

	virtual void setPosition(sf::Vector2f newPosition);

	int getDrawOrder();

	void setDrawOrder(int newDrawOrder);

	virtual EntityType getType() = 0;

	virtual bool toBeDespawned(sf::RenderWindow& window);

	virtual void update(float dt);

	virtual void update(float dt, sf::RenderWindow& window, TextureHandler& textureHandler, std::vector<std::shared_ptr<Entity>>& entities, bool debugMode);

	virtual std::optional<sf::Drawable*> getGraphics();

	virtual std::optional<sf::Shape*> getColliderShape();

	//virtual bool operator==(Entity& other);
};