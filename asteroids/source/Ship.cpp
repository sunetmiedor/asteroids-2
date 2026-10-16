#include "Ship.h"
#include <SFML/System.hpp>
#include "utils.h"
#include "Projectile.h"
#include "HomingProjectile.h"

Ship::Ship(GameTexture& shipTexture, int player) :
	shipGraphics(shipTexture.texture)
{
	playerNumber = player;
	setDrawOrder(3);
	position.x = 350.0f;
	position.y = 1015.0f;
	shipGraphics.setOrigin(sf::Vector2f(shipTexture.texture.getSize().x / 2.0f, shipTexture.texture.getSize().y / 2.0f));
	shipGraphics.setScale(sf::Vector2f(2.0f * radius / shipTexture.texture.getSize().x, 2.0f * radius / shipTexture.texture.getSize().x));
	if (playerNumber == 1)
	{
		shipGraphics.setColor(sf::Color(64, 128, 255));
	}

	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setRadius(getColliderRadius());
	hitbox.setOrigin(sf::Vector2f(getColliderRadius(), getColliderRadius()));
}

EntityType Ship::getType()
{
	return EntityType::Ship;
}

void Ship::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	shipGraphics.setPosition(position);
}

float Ship::getRadius()
{
	return radius;
}

float Ship::getGunCooldown()
{
	return gunCooldown;
}

int Ship::getSelectedWeapon()
{
	return selectedWeapon;
}

int Ship::getPlayerNumber()
{
	return playerNumber;
}

std::vector<sf::Keyboard::Key> Ship::getControlScheme(int playerNumber)
{
	return controlSchemes[playerNumber];
}

float Ship::getColliderRadius()
{
	return radius * 0.5f;
}

std::optional<sf::Drawable*> Ship::getGraphics()
{
	return std::optional<sf::Drawable*>(&shipGraphics);
}

void Ship::shootWeapon(int weaponType, sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>>& entities, TextureHandler& textureHandler)
{
	switch (weaponType)
	{
	case 1:
		// shoot three bullets in a spread
	{
		sf::Angle spread = sf::radians(3.141592f / 12);

		auto bulletLeft = std::make_shared<Projectile>(textureHandler.getTexture("bulletTexture")->texture);
		bulletLeft->setAcceleration(2000.0f * unitVector(-sf::radians(3.141592f / 2) - spread));
		bulletLeft->setPosition(sf::Vector2f(position.x, position.y - radius) + bulletLeft->getVelocity() * 0.04f);
		bulletLeft->setRotation(getAngle(bulletLeft->getVelocity()) + sf::radians(3.141592f / 2));
		entities.push_back(bulletLeft);

		auto bulletMiddle = std::make_shared<Projectile>(textureHandler.getTexture("bulletTexture")->texture);
		bulletMiddle->setAcceleration(sf::Vector2f(0, -2000));
		bulletMiddle->setPosition(sf::Vector2f(position.x, position.y - radius) + bulletMiddle->getVelocity() * 0.04f);
		entities.push_back(bulletMiddle);

		auto bulletRight = std::make_shared<Projectile>(textureHandler.getTexture("bulletTexture")->texture);
		bulletRight->setAcceleration(2000.0f * unitVector(-sf::radians(3.141592f / 2) + spread));
		bulletRight->setPosition(sf::Vector2f(position.x, position.y - radius) + bulletRight->getVelocity() * 0.04f);
		bulletRight->setRotation(getAngle(bulletRight->getVelocity()) + sf::radians(3.141592f / 2));
		entities.push_back(bulletRight);
	}
	break;

	case 2:
		// Shoot piercing bullet
	{
		auto bullet = std::make_shared<Projectile>(textureHandler.getTexture("bulletTexture")->texture);
		bullet->setPierceCount(3);
		bullet->setPosition(sf::Vector2f(position.x, position.y - radius));
		bullet->setAcceleration(sf::Vector2f(0, -2000));
		entities.push_back(bullet);
	}
	break;

	case 3:
	{
		auto bullet = std::make_shared<HomingProjectile>(textureHandler.getTexture("homingBulletTexture")->texture, entities);
		bullet->setPosition(sf::Vector2f(position.x, position.y - radius));
		bullet->setVelocity(sf::Vector2f(990, 0));
		bullet->setAcceleration(sf::Vector2f(-2000, 0));
		entities.push_back(bullet);

		bullet = std::make_shared<HomingProjectile>(textureHandler.getTexture("homingBulletTexture")->texture, entities);
		bullet->setPosition(sf::Vector2f(position.x, position.y - radius));
		bullet->setVelocity(sf::Vector2f(-900, 0));
		bullet->setAcceleration(sf::Vector2f(2000, 0));
		entities.push_back(bullet);
	}
	break;

	default:
	{
		auto bullet = std::make_shared<Projectile>(textureHandler.getTexture("bulletTexture")->texture);
		bullet->setPosition(sf::Vector2f(position.x, position.y - radius));
		bullet->setAcceleration(sf::Vector2f(0, -2000));
		entities.push_back(bullet);
	}
	break;
}
}

void Ship::applyUpgrade(int upgradeType)
{
	selectedWeapon = upgradeType;
}

void Ship::update(float dt, sf::RenderWindow& window, TextureHandler& textureHandler, std::vector<std::shared_ptr<Entity>>& entities, bool debugMode)
{
	sf::Vector2f desiredDirection;
	if (sf::Keyboard::isKeyPressed(getControlScheme(playerNumber)[0]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -50)
	{
		desiredDirection.y -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(getControlScheme(playerNumber)[1]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50)
	{
		desiredDirection.x -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(getControlScheme(playerNumber)[2]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 50)
	{
		desiredDirection.y += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(getControlScheme(playerNumber)[3]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50)
	{
		desiredDirection.x += 1.0f;
	}
	if (desiredDirection.x != 0 || desiredDirection.y != 0)
	{
		desiredDirection *= 1.0f / norm(desiredDirection);
	}
	auto velocity = desiredDirection * speed;
	auto futurePosition = position + velocity * dt;
	if (isPointInMinMaxBox(futurePosition, sf::Vector2f(radius, radius), sf::Vector2f(window.getSize()) - sf::Vector2f(radius, radius)))
	{
		setPosition(futurePosition);
	}
	if (debugMode)
	{
		if (sf::Joystick::isConnected(0))
		{
			if (sf::Joystick::isButtonPressed(0, 5))
			{
				selectedWeapon += 1;
				if (selectedWeapon > 3)
				{
					selectedWeapon = 0;
				}
			}
			else if (sf::Joystick::isButtonPressed(0, 4))
			{
				selectedWeapon -= 1;
				if (selectedWeapon < 0)
				{
					selectedWeapon = 3;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			selectedWeapon = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			selectedWeapon = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			selectedWeapon = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
		{
			selectedWeapon = 0;
		}
	}


	if ((sf::Keyboard::isKeyPressed(getControlScheme(playerNumber)[4]) || sf::Joystick::isButtonPressed(0, 1)) && ((selectedWeapon != 3 && gunCooldownClock.getElapsedTime().asSeconds() >= gunCooldown) || (gunCooldownClock.getElapsedTime().asSeconds() >= 0.7f)))
	{

		shootWeapon(selectedWeapon, window, entities, textureHandler);
		gunCooldownClock.restart();
	}

	hitbox.setPosition(position);
}


std::optional<sf::Shape*> Ship::getColliderShape()
{	
	return std::optional<sf::Shape*>(&hitbox);
}
