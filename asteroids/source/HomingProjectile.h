#pragma once
#include "Projectile.h"
#include "Asteroid.h"

class HomingProjectile : public Projectile
{
	std::vector<Asteroid*> _rocksInEntities;
	bool startedTracking = false;
	sf::Vector2f getNearestAsteroidPosition();

public:
	HomingProjectile(sf::Texture& texture, std::vector<std::shared_ptr<Entity>> entities);

	EntityType getType() override;

	void update(float dt) override;
};