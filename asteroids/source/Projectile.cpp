#include "Projectile.h" 
#include "utils.h"
#include <memory>
#include <vector>

Projectile::Projectile(sf::Texture& texture) :
	graphics(texture)
{
	setDrawOrder(2);
	graphics.setScale(sf::Vector2f(radius * 2.0f / texture.getSize().x, radius * 2.0f / texture.getSize().x));
	graphics.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().x / 2.0f));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setRadius(radius);
	hitbox.setOrigin(sf::Vector2f(radius, radius));
}

EntityType Projectile::getType()
{
	return EntityType::Projectile;
}

void Projectile::setMaxSpeed(float newMaxSpeed)
{
	maxSpeed = newMaxSpeed;
}

void Projectile::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	graphics.setPosition(position);
}

void Projectile::setVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
	if (norm(velocity) > maxSpeed)
	{
		velocity = normalized(velocity) * maxSpeed;
	}
}

void Projectile::setAcceleration(sf::Vector2f newAcceleration)
{
	acceleration = newAcceleration;
}

void Projectile::setRotation(sf::Angle angle)
{
	graphics.setRotation(angle);
}

void Projectile::setPierceCount(int newPierceCount)
{
	pierceCount = newPierceCount;
}

sf::Vector2f Projectile::getVelocity()
{
	return velocity;
}

float Projectile::getRadius()
{
	return radius;
}

sf::Time Projectile::getElapsedTime()
{
	return elapsedTime.getElapsedTime();
}

int Projectile::getPierceCount()
{
	return pierceCount;
}

std::optional<sf::Drawable*> Projectile::getGraphics()
{
	return std::optional<sf::Drawable*>(&graphics);
}

sf::Vector2f Projectile::getGraphicsPosition()
{
	return graphics.getPosition();
}

bool Projectile::operator==(const Projectile& other)
{
	return position == other.position;
}

void Projectile::update(float dt)
{
	setVelocity(velocity + acceleration * dt);
	setPosition(position + velocity * dt);
	graphics.setRotation(getAngle(velocity) + sf::radians(3.141592f / 2.0f));
	hitbox.setPosition(position);
}

std::optional<sf::Shape*> Projectile::getColliderShape()
{
	return std::optional<sf::Shape*>(&hitbox);
}