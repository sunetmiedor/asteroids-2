#pragma once
#include <SFML\Graphics.hpp>
#include "Projectile.h"
#include "Asteroid.h"
#include "HomingProjectile.h"

float norm(sf::Vector2f v);

sf::Vector2f unitVector(sf::Angle angle);

sf::Angle getAngle(sf::Vector2f v);

sf::Vector2f normalized(sf::Vector2f v);

bool isPointInMinMaxBox(sf::Vector2f v, sf::Vector2f min, sf::Vector2f max);

bool isPointInCircle(sf::Vector2f point, sf::Vector2f centre, float radius);

bool circlesIntersectCheck(sf::Vector2f centre1, float radius1, sf::Vector2f centre2, float radius2);

float uniform01();

float uniform01Inclusive();

float uniform(float minInclusive, float maxExclusive);

float uniformInclusive(float min, float max);

float invLerp(float valueInterval, float startInterval, float endInterval);

float lerp(float interpolationFactor, float startInterval, float endInterval);

float lerp(float valueIntervalA, float startIntervalA, float endIntervalA, float startIntervalB, float endIntervalB); //linear interpolation

