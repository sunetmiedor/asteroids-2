#include "Asteroid.h"
#include <SFML\Graphics.hpp>
#include "utils.h"

Asteroid::Asteroid()
{
	setDrawOrder(4);
	velocity.x = uniformInclusive(-100.0f, 100.0f);
	velocity.y = uniformInclusive(200.0f, 400.0f);
	radius = uniformInclusive(40.0f, 65.0f);
	graphics.setRadius(radius);
	graphics.setOrigin(sf::Vector2f(radius, radius));
	health = 1;


	hitbox.setRadius(radius);
	hitbox.setOrigin(sf::Vector2f(radius, radius));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
}

Asteroid::Asteroid(float radius, sf::Vector2f velocity)
{
	setDrawOrder(4);
	this->velocity = velocity;
	this->radius = radius;
	graphics.setRadius(radius);
	graphics.setOrigin(sf::Vector2f(radius, radius));
	health = 5;

	hitbox.setRadius(radius);
	hitbox.setOrigin(sf::Vector2f(radius, radius));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
}

EntityType Asteroid::getType()
{
	return EntityType::Asteroid;
}

float Asteroid::getRadius()
{
	return radius;
}

sf::Vector2f Asteroid::getVelocity()
{
	return velocity;
}

int Asteroid::getHealth()
{
	return health;
}

float Asteroid::getDestructionPauseElapsedTime()
{
	return destructionPause.getElapsedTime().asSeconds();
}

std::optional<sf::Drawable*> Asteroid::getGraphics()
{
	return std::optional<sf::Drawable*>(&graphics);
}

void Asteroid::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	graphics.setPosition(position);
	hitbox.setPosition(position);
}

void Asteroid::setTexture(sf::Texture& texture)
{
	graphics.setTexture(&texture);
}

void Asteroid::setHealth(int newHealth)
{
	health = newHealth;
}

void Asteroid::generate(sf::RenderWindow& window, GameTexture& rockTexture)
{
	graphics.setTexture(&rockTexture.texture);
	setPosition(sf::Vector2f(uniformInclusive(75.0f, (float)window.getSize().x + 75), -50.0f)); //50 being the minimum position for the maximum radius (apologies for the magic number)
}

void Asteroid::generateBoss(sf::RenderWindow& window, GameTexture& bossTexture)
{
	graphics.setTexture(&bossTexture.texture);
	setPosition(sf::Vector2f(350, -100));
}

void Asteroid::enterDestructionPhase(sf::Texture& explosionTexture)
{
	velocity = sf::Vector2f(0.0f, 0.0f);
	setTexture(explosionTexture);
	graphics.setRadius(radius / 1.5f);
}

void Asteroid::resetDestructionPause()
{
	destructionPause.restart();
}

bool Asteroid::isBoss()
{
	return radius >= 100.0f;
}

bool Asteroid::operator==(Asteroid& other)
{
		return position == other.getPosition() && radius == other.getRadius();

}

void Asteroid::update(float dt)
{
	setPosition(position + velocity * dt);
	graphics.rotate(sf::radians(3.141592f / 4.0f) * dt);

	hitbox.setPosition(position);
}

std::optional<sf::Shape*> Asteroid::getColliderShape()
{
	return std::optional<sf::Shape*>(&hitbox);
}