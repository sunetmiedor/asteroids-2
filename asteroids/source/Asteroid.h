#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Entity.h"

class Asteroid : public Entity
{
    sf::Vector2f velocity;
    float radius;
    sf::CircleShape graphics;
    sf::CircleShape hitbox;
    int health;
    sf::Clock destructionPause;

public:

    Asteroid();

    Asteroid(float radius, sf::Vector2f velocity);

	EntityType getType() override;

	float getRadius();

	sf::Vector2f getVelocity();

	int getHealth();

	float getDestructionPauseElapsedTime();

    std::optional<sf::Drawable*> getGraphics() override;

    void setPosition(sf::Vector2f newPosition) override;

	void setTexture(sf::Texture& texture);

	void setHealth(int newHealth);

    void generate(sf::RenderWindow& window, GameTexture& rockTexture);

    void generateBoss(sf::RenderWindow& window, GameTexture& bossTexture);
  
	void enterDestructionPhase(sf::Texture& explosionTexture);

    void resetDestructionPause();

    bool isBoss();

    bool operator==(Asteroid& other);

    void update(float dt) override;

    std::optional<sf::Shape*> getColliderShape() override;

};