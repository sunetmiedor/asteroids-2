#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <print>
#include <ranges>
#include <memory>
#include <filesystem>
#include "source/utils.h"
#include "source/Asteroid.h"
#include "source/Projectile.h"
#include "source/HomingProjectile.h"
#include "source/Star.h"
#include "source/Ship.h"
#include "source/Upgrade.h"
#include "source/Trail.h"
#include "source/TextureHandler.h"
#include "source/GameTexture.h"

int main()
{
	TextureHandler textureHandler;
	textureHandler.loadTexture("volumeOnButtonTexture", "sprites/volumeOn.png", "utility");
	textureHandler.loadTexture("volumeOffButtonTexture", "sprites/volumeOff.png", "utility");
	textureHandler.loadTexture("backgroundTexture", "sprites/bkg.png", "background");
	textureHandler.loadTexture("shipTexture", "sprites/ship.png", "ship");
	textureHandler.loadTexture("bulletTexture", "sprites/energyBullet.png", "bullet");
	textureHandler.loadTexture("homingBulletTexture", "sprites/homingRocket.png", "bullet");
	textureHandler.loadTexture("trailTexture", "sprites/trail.png", "trail");
	textureHandler.loadTexture("spreadUpgrade", "sprites/spreadUpgrade.png", "upgrade");
	textureHandler.loadTexture("pierceUpgrade", "sprites/pierceUpgrade.png", "upgrade");
	textureHandler.loadTexture("trackerUpgrade", "sprites/trackerUpgrade.png", "upgrade");
	textureHandler.loadTexture("bossAsteroid", "sprites/bossAsteroid.png", "bossAsteroid");
	textureHandler.loadTexture("mediumAsteroid1", "sprites/mediumAsteroid1.png", "mediumAsteroid");
	textureHandler.loadTexture("mediumAsteroid2", "sprites/mediumAsteroid2.png", "mediumAsteroid");
	textureHandler.loadTexture("mediumAsteroid3", "sprites/mediumAsteroid3.png", "mediumAsteroid");
	textureHandler.loadTexture("smallAsteroid1", "sprites/smallAsteroid1.png", "smallAsteroid");
	textureHandler.loadTexture("smallAsteroid2", "sprites/smallAsteroid2.png", "smallAsteroid");
	textureHandler.loadTexture("smallAsteroid3", "sprites/smallAsteroid3.png", "smallAsteroid");
	textureHandler.loadTexture("explosion", "sprites/explosion.png", "explosion");

	std::vector<std::shared_ptr<Entity>> entities; // asteroids, trails, stars, upgrades, bullets, ship
	std::vector<std::shared_ptr<Entity>> entitiesToBeDespawned;
	std::vector<std::shared_ptr<Entity>> entitiesToBeSpawned;

	sf::Music mainTheme("sounds/bkgmusic.mp3");
	sf::Music bossTheme("sounds/bossmusic.mp3");

	sf::RenderWindow window(sf::VideoMode({ 700, 1080 }), "Asteroids");
	mainTheme.setLooping(true);
	mainTheme.setVolume(50.0f);
	bossTheme.setLoopPoints({ sf::seconds(5), sf::seconds(78) });
	bossTheme.setLooping(true);
	mainTheme.setVolume(50.0f);

	sf::SoundBuffer rockHitSoundEffect("sounds/rocksound.mp3");
	sf::SoundBuffer bulletSoundEffect("sounds/bulletsound.mp3");
	sf::Sound rockHitSound(rockHitSoundEffect);
	sf::Sound bulletSound(bulletSoundEffect);


	sf::RectangleShape volumeButton(sf::Vector2f(50.0f, 50.0f));
	volumeButton.setPosition(sf::Vector2f(30.0f, 30.0f));
	volumeButton.setTexture(&textureHandler.getTexture("volumeOnButtonTexture")->texture);


	sf::Sprite background(textureHandler.getTexture("backgroundTexture")->texture);
	background.setScale(sf::Vector2f(static_cast<float>(window.getSize().x) / textureHandler.getTexture("backgroundTexture")->texture.getSize().x, static_cast<float>(window.getSize().x) / textureHandler.getTexture("backgroundTexture")->texture.getSize().x));
	background.setPosition(sf::Vector2f(0.0f, 0.0f));
	sf::Sprite background2(textureHandler.getTexture("backgroundTexture")->texture);
	background2.setScale(sf::Vector2f(static_cast<float>(window.getSize().x) / textureHandler.getTexture("backgroundTexture")->texture.getSize().x, static_cast<float>(window.getSize().x) / textureHandler.getTexture("backgroundTexture")->texture.getSize().x));
	background2.setPosition(sf::Vector2f(background.getGlobalBounds().size.x, 0.0f));
	background2.rotate(sf::degrees(180.0f));


	sf::Font font("ariblk.ttf");
	sf::Text endText(font);
	endText.setString("Game Over!");
	endText.setCharacterSize(30);
	endText.setFillColor(sf::Color::Red);
	endText.setOrigin(sf::Vector2f(endText.getGlobalBounds().size.x / 2.0f, endText.getGlobalBounds().size.y / 2.0f));
	endText.setPosition(sf::Vector2f((float)window.getSize().x / 2.0f, (float)window.getSize().y / 2.0f));

	sf::Text startTitle(font);
	startTitle.setString("ASTEROIDS");
	startTitle.setCharacterSize(50);
	startTitle.setFillColor(sf::Color::White);
	startTitle.setOrigin(sf::Vector2f(startTitle.getGlobalBounds().size.x / 2.0f, startTitle.getGlobalBounds().size.y / 2.0f));
	startTitle.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 4.0f));
	sf::Text startText1(font);
	startText1.setString("1 Player");
	startText1.setCharacterSize(30);
	startText1.setFillColor(sf::Color::Yellow);
	startText1.setOrigin(sf::Vector2f(startText1.getGlobalBounds().size.x / 2.0f, startText1.getGlobalBounds().size.y / 2.0f));
	startText1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	sf::Text startText2(font);
	startText2.setString("2 Player");
	startText2.setCharacterSize(30);
	startText2.setFillColor(sf::Color::White);
	startText2.setOrigin(sf::Vector2f(startText2.getGlobalBounds().size.x / 2.0f, startText2.getGlobalBounds().size.y / 2.0f));
	startText2.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50.0f));

	sf::Text pauseText(font);
	pauseText.setString("Paused");
	pauseText.setCharacterSize(30);
	pauseText.setFillColor(sf::Color::Yellow);
	pauseText.setOrigin(sf::Vector2f(pauseText.getGlobalBounds().size.x / 2.0f, pauseText.getGlobalBounds().size.y / 2.0f));
	pauseText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	sf::Text scoreText(font);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));

	sf::Clock frameClock;
	float dt = 0.0f;

	sf::Clock asteroidCooldown;
	sf::Clock starCooldown;

	auto isNotNull = std::views::filter([](auto& entity) {return entity != nullptr; });
	auto isAsteroid = std::views::filter([](auto& entity) {return entity->getType() == EntityType::Asteroid; });
	auto isShip = std::views::filter([](auto& entity) {return entity->getType() == EntityType::Ship; });
	auto isUpgrade = std::views::filter([](auto& entity) {return entity->getType() == EntityType::Upgrade; });
	auto isAnyProjectile = std::views::filter([](auto& entity) {return entity->getType() == EntityType::Projectile || entity->getType() == EntityType::HomingProjectile; });


	bool gameStarted = false;
	int score = 0;
	bool intersection = false;
	bool paused = false;
	bool pauseKeyPrev = false;
	bool resetKeyPrev = false;
	bool muteClickPrev = false;
	bool soundMuted = false;
	bool secondPlayer = false;
	bool bossSpawned = false;
	bool debugMode = false;
	std::vector<sf::Keyboard::Scancode> comboBuffer;
	std::vector<sf::Keyboard::Scancode> debugCode = { sf::Keyboard::Scancode::Up,
											  sf::Keyboard::Scancode::Up,
											  sf::Keyboard::Scancode::Down,
											  sf::Keyboard::Scancode::Down,
											  sf::Keyboard::Scancode::Left,
											  sf::Keyboard::Scancode::Right,
											  sf::Keyboard::Scancode::Left,
											  sf::Keyboard::Scancode::Right,
											  sf::Keyboard::Scancode::B,
											  sf::Keyboard::Scancode::A };

	for (int i = 0; i < 100; i++)
	{
		auto star = std::make_shared<Star>();
		star->setPosition(sf::Vector2f(uniformInclusive(0.0f, (float)window.getSize().x), uniformInclusive(0.0f, (float)window.getSize().y)));
		entities.push_back(star);
	}


	mainTheme.play();
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::KeyPressed>())
				comboBuffer.push_back(event->getIf<sf::Event::KeyPressed>()->scancode);
		}

		dt = frameClock.restart().asSeconds();

		for (auto& entity : entities | isShip)
		{
			for (auto& rockEntity : entities | isAsteroid)
			{
				auto ship = std::dynamic_pointer_cast<Ship>(entity);
				auto asteroid = std::dynamic_pointer_cast<Asteroid>(rockEntity);
				if (circlesIntersectCheck(entity->getPosition(), ship->getColliderRadius(), rockEntity->getPosition(), asteroid->getRadius()))
				{
					intersection = true;
					break;
				}
			}
			if (intersection)
			{
				break;
			}
		}

		if (!debugMode)
		{
			if (comboBuffer == debugCode)
			{
				debugMode = true;
				comboBuffer.clear();
			}
			for (int key = 0; key < comboBuffer.size(); key++)
			{
				if (comboBuffer[key] == debugCode[key])
				{
					continue;
				}
				else
				{
					comboBuffer.clear();
					break;
				}
			}
		}

		bool pauseKeyCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0, 9);
		if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0, 9)) && !pauseKeyPrev) && !intersection && gameStarted)
		{
			paused = !paused;
		}
		pauseKeyPrev = pauseKeyCurr;

		if (!intersection && !paused)
		{

			//move background
			if (background.getPosition().y >= background.getGlobalBounds().size.y)
			{
				background.setPosition(sf::Vector2f(0.0f, -background.getGlobalBounds().size.y));
			}
			else if (background2.getPosition().y >= background2.getGlobalBounds().size.y * 2)
			{
				background2.setPosition(sf::Vector2f(background.getGlobalBounds().size.x, 0.0f));
			}
			background.setPosition(background.getPosition() + sf::Vector2f(0.0f, 50.0f) * dt);
			background2.setPosition(background2.getPosition() + sf::Vector2f(0.0f, 50.0f) * dt);

			//stars
			if (starCooldown.getElapsedTime().asSeconds() > 0.05f)
			{
				auto star = std::make_shared<Star>();
				star->setPosition(sf::Vector2f(uniformInclusive(0.0f, (float)window.getSize().x), -3.0f));
				entities.push_back(star);
				starCooldown.restart();
			}

			for (auto& entity : entities | isNotNull)
			{

				if (entity->getType() == EntityType::Ship)
				{
					entity->update(dt, window, textureHandler, entitiesToBeSpawned, debugMode);
				}
				else
				{
					entity->update(dt);
				}

				if (entity->toBeDespawned(window))
				{
					entitiesToBeDespawned.push_back(entity);
				}

			}

			if (!gameStarted)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < 0)
				{
					startText2.setFillColor(sf::Color::Yellow);
					startText1.setFillColor(sf::Color::White);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 0)
				{
					startText1.setFillColor(sf::Color::Yellow);
					startText2.setFillColor(sf::Color::White);
				}
				if (startText2.getFillColor() == sf::Color::Yellow && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Joystick::isButtonPressed(0, 1))))
				{
					entities.push_back(std::make_shared<Ship>(*textureHandler.getTexture("shipTexture"), 0));
					entities.push_back(std::make_shared<Ship>(*textureHandler.getTexture("shipTexture"), 1));
					secondPlayer = true;
					gameStarted = true;
				}
				else if (startText1.getFillColor() == sf::Color::Yellow && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Joystick::isButtonPressed(0, 1))))
				{
					entities.push_back(std::make_shared<Ship>(*textureHandler.getTexture("shipTexture"), 0));
					gameStarted = true;
				}
				const auto cursorHand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
				const auto cursorArrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
				bool muteClickCurr = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
				if (volumeButton.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					window.setMouseCursor(cursorHand);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !muteClickPrev)
					{
						if (!soundMuted)
						{
							volumeButton.setTexture(&textureHandler.getTexture("volumeOffButtonTexture")->texture);
							mainTheme.pause();
							soundMuted = true;
						}
						else
						{
							volumeButton.setTexture(&textureHandler.getTexture("volumeOnButtonTexture")->texture);
							mainTheme.play();
							soundMuted = false;
						}
					}
				}
				else
				{
					window.setMouseCursor(cursorArrow);
				}
				muteClickPrev = muteClickCurr;
				window.clear();
				window.draw(background);
				window.draw(background2);
				for (auto entity : entities)
				{
					auto graphics = entity->getGraphics();
					if (graphics.has_value())
					{
						window.draw(*graphics.value());
					}
				}
				window.draw(startTitle);
				window.draw(startText1);
				window.draw(startText2);
				window.draw(volumeButton);
			}

			else
			{
				window.setMouseCursorVisible(false);

				//create asteroid
				if (score % 5000 != 0 || score == 0)
				{
					if (asteroidCooldown.getElapsedTime().asSeconds() >= 1.0f)
					{
						auto rock = std::make_shared<Asteroid>();
						rock->generate(window, *textureHandler.getAllTypeTextures("mediumAsteroid")[rand() % 3]);
						entities.push_back(rock);
						asteroidCooldown.restart();
					}
				}
				else if (!bossSpawned && score % 5000 == 0 && score > 0)
				{
					for (auto entity : entities | isNotNull | isAsteroid)
					{
						std::erase(entities, entity);
					}
					auto rock = std::make_shared<Asteroid>(100.0f, sf::Vector2f(0, 75.0f));
					rock->generateBoss(window, *textureHandler.getTexture("bossAsteroid"));
					entities.push_back(rock);
					asteroidCooldown.restart();
					bossSpawned = true;
					if (!soundMuted)
					{
						mainTheme.pause();
						bossTheme.play();
					}
				}

				//bullet hits asteroid/oob
				for (auto& projectileEntity : entities | isNotNull | isAnyProjectile)
				{
					for (auto& asteroidEntity : entities | isAsteroid)
					{
						auto projectile = std::dynamic_pointer_cast<Projectile>(projectileEntity);
						auto rock = std::dynamic_pointer_cast<Asteroid>(asteroidEntity);
						if (circlesIntersectCheck(rock->getPosition(), rock->getRadius(), projectile->getPosition(), projectile->getRadius()))
						{
							if (rock->isBoss() == false && bossSpawned == false)
							{
								score += 100;
								scoreText.setString("Score: " + std::to_string(score));
								projectile->setPierceCount(projectile->getPierceCount() - 1);
								if (projectile->getPierceCount() == 0)
								{
									entitiesToBeDespawned.push_back(projectileEntity);
								}
								rock->setTexture(textureHandler.getTexture("explosion")->texture);
								rock->resetDestructionPause();
								/*auto upgrade = std::make_shared<Upgrade>(upgradeTexture);
								upgrade->setPosition(rock->getPosition());
								entities.push_back(upgrade);*/
								if (!soundMuted)
								{
									rockHitSound.play();
								}
								if (rock->getRadius() / 2.0f >= 25.0f)
								{
									auto rock1 = std::make_shared<Asteroid>(rock->getRadius() / 1.5f, sf::Vector2f(uniformInclusive(-1, 0), rock->getVelocity().y));
									auto rock2 = std::make_shared<Asteroid>(rock->getRadius() / 1.5f, sf::Vector2f(uniformInclusive(0, 1), rock->getVelocity().y));
									rock1->setTexture(textureHandler.getAllTypeTextures("smallAsteroid")[rand() % 3]->texture);
									rock2->setTexture(textureHandler.getAllTypeTextures("smallAsteroid")[rand() % 3]->texture);
									rock1->setPosition(sf::Vector2f(rock->getPosition().x - rock->getRadius() * 0.5f, rock->getPosition().y));
									rock2->setPosition(sf::Vector2f(rock->getPosition().x + rock->getRadius() * 0.5f, rock->getPosition().y));
									entitiesToBeSpawned.push_back(rock1);
									entitiesToBeSpawned.push_back(rock2);
								}
								asteroidEntity = std::make_shared<Asteroid>(*rock);
								entitiesToBeDespawned.push_back(asteroidEntity);
							}
							else
							{
								if (rock->getHealth() > 1)
								{
									rock->setHealth(rock->getHealth() - 1);
									entitiesToBeDespawned.push_back(projectileEntity);
								}
								else
								{
									if (!soundMuted)
									{
										bossTheme.stop();
										mainTheme.play();
									}
									score += 500;
									scoreText.setString("Score: " + std::to_string(score));
									entitiesToBeDespawned.push_back(projectileEntity);
									rock->setTexture(textureHandler.getTexture("explosion")->texture);
									rock->getVelocity() = sf::Vector2f(0.0f, 0.0f);
									if (!soundMuted)
									{
										rockHitSound.play();
									}
									auto upgrade = std::make_shared<Upgrade>(textureHandler.getAllTypeTextures("upgrade"));
									upgrade->setPosition(rock->getPosition());
									entities.push_back(upgrade);
									if (rock->getRadius() / 2 >= 25)
									{
										auto rock1 = std::make_shared<Asteroid>(rock->getRadius() / 1.5f, sf::Vector2f(uniformInclusive(-1, 0), rock->getVelocity().y));
										auto rock2 = std::make_shared<Asteroid>(rock->getRadius() / 1.5f, sf::Vector2f(uniformInclusive(0, 1), rock->getVelocity().y));
										rock1->setTexture(textureHandler.getAllTypeTextures("mediumAsteroid")[rand() % 3]->texture);
										rock2->setTexture(textureHandler.getAllTypeTextures("mediumAsteroid")[rand() % 3]->texture);
										rock1->setPosition(sf::Vector2f(rock->getPosition().x - rock->getRadius() * 0.5f, rock->getPosition().y));
										rock2->setPosition(sf::Vector2f(rock->getPosition().x + rock->getRadius() * 0.5f, rock->getPosition().y));
										entitiesToBeSpawned.push_back(rock1);
										entitiesToBeSpawned.push_back(rock2);
									}
									rock->resetDestructionPause();
									asteroidEntity = std::make_shared<Asteroid>(*rock);
									entitiesToBeDespawned.push_back(asteroidEntity);
									bossSpawned = false;
								}
							}

						}
						if (projectileEntity == nullptr)
						{
							break;
						}
					}

				}

				for (auto& entity : entities | isNotNull | isAnyProjectile)
				{
					auto bullet = std::dynamic_pointer_cast<Projectile>(entity);
					if (int(bullet->getElapsedTime().asMilliseconds()) % 15 == 0 && bullet->getElapsedTime().asSeconds() > 0.0f)
					{
						entitiesToBeSpawned.push_back(std::make_shared <Trail>(*textureHandler.getTexture("trailTexture"), bullet->getGraphicsPosition()));
					}
				}

				for (auto& entity : entities | isNotNull | isShip)
				{
					for (auto& upgradeEntity : entities | isUpgrade)
					{
						auto ship = std::dynamic_pointer_cast<Ship>(entity);
						auto upgrade = std::dynamic_pointer_cast<Upgrade>(upgradeEntity);
						if (circlesIntersectCheck(ship->getPosition(), ship->getColliderRadius(), upgrade->getPosition(), upgrade->getRadius()))
						{
							ship->applyUpgrade(upgrade->getUpgradeType());
							entitiesToBeDespawned.push_back(upgradeEntity);
						}
					}
				}

				for (auto& entity : entitiesToBeSpawned)
				{
					entities.push_back(entity);
				}

				entitiesToBeSpawned.clear();

				for (auto& entity : entitiesToBeDespawned | isNotNull)
				{
					if (entity->getType() == EntityType::Asteroid)
					{
						auto rock = std::dynamic_pointer_cast<Asteroid>(entity);
						rock->enterDestructionPhase(textureHandler.getTexture("explosion")->texture);
						std::erase(entities, entity);
						if (rock->getDestructionPauseElapsedTime() > 0.2f)
						{
							entity.reset();
						}
					}
					else
					{
						auto where = std::ranges::find(entities, entity);
						if (where != entities.end())
						{
							std::swap(*where, entities.back());
							entities.pop_back();
						}
					}
				}

				//draw
				window.clear();
				window.draw(background);
				window.draw(background2);
				std::ranges::sort(entities, [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) mutable {return a->getDrawOrder() < b->getDrawOrder(); });
				for (auto entity : entities)
				{
					auto graphics = entity->getGraphics();
					if (graphics)
					{
						window.draw(*graphics.value());
						auto collider = entity->getColliderShape();
						if (debugMode && collider)
						{
							window.draw(*collider.value());
						}
					}
				}
				for (auto& entity : entitiesToBeDespawned | isNotNull | isAsteroid)
				{
					auto rock = std::dynamic_pointer_cast<Asteroid>(entity);
					auto graphics = rock->getGraphics();
					if (graphics.has_value())
					{
						window.draw(*graphics.value());
					}
				}
				window.draw(scoreText);

				//std::println("Entities count: {}", entities.size());
				//std::println("Clock= {} s   fps={} ", dt, 1.0f / dt);
			}
		}
		if (intersection)
		{
			//game over
			window.draw(endText);
		}
		if (paused)
		{
			window.draw(pauseText);
		}
		window.display();
		// reset  
		bool resetKeyCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) || sf::Joystick::isButtonPressed(0, 8);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) || sf::Joystick::isButtonPressed(0, 8)) && !resetKeyPrev && gameStarted == true)
		{
			entities.clear();
			entitiesToBeDespawned.clear();
			entities.push_back(std::make_shared<Ship>(*textureHandler.getTexture("shipTexture"), 0));
			if (secondPlayer)
			{
				entities.push_back(std::make_shared<Ship>(*textureHandler.getTexture("shipTexture"), 1));
			}
			intersection = false;
			score = 0;
			scoreText.setString("Score: " + std::to_string(score));
			paused = false;
			for (int i = 0; i < 100; i++)
			{
				auto star = std::make_shared<Star>();
				star->setPosition(sf::Vector2f(uniformInclusive(0.0f, (float)window.getSize().x), uniformInclusive(0.0f, (float)window.getSize().y)));
				entities.push_back(star);
			}
		}
		resetKeyPrev = resetKeyCurr;
	}
	textureHandler.clearTextures();
}

