#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Entity.h"

class Projectile : public Entity
{
    sf::CircleShape hitbox;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius = 15.0f;
    sf::Sprite graphics;
    int pierceCount = 1;
    float maxSpeed = 900.0f;
    sf::Clock elapsedTime;

public:

    Projectile(sf::Texture& texture);

	EntityType getType() override;

    void setMaxSpeed(float newMaxSpeed);

    void setPosition(sf::Vector2f newPosition) override;

    void setVelocity(sf::Vector2f newVelocity);

    void setAcceleration(sf::Vector2f newAcceleration);

	void setRotation(sf::Angle angle);

	void setPierceCount(int newPierceCount);

	sf::Vector2f getVelocity();

	float getRadius();

	sf::Time getElapsedTime();

	int getPierceCount();

    std::optional<sf::Drawable*> getGraphics() override;

	sf::Vector2f getGraphicsPosition();

    bool operator==(const Projectile& other);

    virtual void update(float dt) override;

    virtual std::optional<sf::Shape*> getColliderShape() override;
};