#include "HomingProjectile.h"
#include <print>
#include "utils.h"
#include <memory>
#include <vector>

HomingProjectile::HomingProjectile(sf::Texture& texture, std::vector<std::shared_ptr<Entity>> entities) :
    Projectile(texture)
{
	setDrawOrder(2);
    for (auto& entity : entities)
    {
        if (auto rock = dynamic_cast<Asteroid*>(entity.get()))
        {
            _rocksInEntities.push_back(rock);
        }
	}
}

EntityType HomingProjectile::getType()
{
    return EntityType::HomingProjectile;
}

sf::Vector2f HomingProjectile::getNearestAsteroidPosition()
{
    sf::Vector2f asteroidPosition;
    float asteroidDistance = std::numeric_limits<float>::infinity();
    for (const auto& rock : _rocksInEntities)
    {
        if (norm(position - rock->getPosition()) < asteroidDistance)
        {
            asteroidDistance = norm(position - rock->getPosition());
            asteroidPosition = rock->getPosition();
        }
    }
    return asteroidPosition;
}

void HomingProjectile::update(float dt)
{
	//std::println("HomingProjectile::update");
    if (getElapsedTime().asSeconds() > 0.2f)
    {
        auto targetPos = getNearestAsteroidPosition();
        setAcceleration(1500.0f * normalized(targetPos - position));
    }
    Projectile::update(dt);
}
