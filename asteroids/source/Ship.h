#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Projectile.h"
#include "Asteroid.h"
#include "Entity.h"
#include "TextureHandler.h"


class Ship : public Entity
{
    sf::CircleShape hitbox;
    int playerNumber;
    float speed = 500.0f;
    float radius = 35.0f;
    float gunCooldown = 0.4f;
    sf::Clock gunCooldownClock;
    sf::Sprite shipGraphics;
    int selectedWeapon = 0;
    std::vector<std::vector<sf::Keyboard::Key>> controlSchemes = {
        { sf::Keyboard::Key::Up, sf::Keyboard::Key::Left, sf::Keyboard::Key::Down, sf::Keyboard::Key::Right, sf::Keyboard::Key::Space},
        { sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::LControl}
	};

public:

    Ship(GameTexture& shipTexture, int player);

	EntityType getType() override;

    void setPosition(sf::Vector2f newPosition) override;

	float getRadius();

	float getGunCooldown();

	int getSelectedWeapon();

	int getPlayerNumber();

	std::vector<sf::Keyboard::Key> getControlScheme(int playerNumber);

	std::optional<sf::Drawable*> getGraphics() override;

    void shootWeapon(int weaponType, sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>>& entities, TextureHandler& textureHandler);

    void applyUpgrade(int upgradeType);

    void update(float dt, sf::RenderWindow& window, TextureHandler& textureHandler, std::vector<std::shared_ptr<Entity>>& entities, bool debugMode) override;

    float getColliderRadius();

    std::optional<sf::Shape*> getColliderShape() override;

};