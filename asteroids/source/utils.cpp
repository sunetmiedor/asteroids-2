#include "utils.h"
#include <SFML/System.hpp>


float norm(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f unitVector(sf::Angle angle)
{
    return sf::Vector2f(cos(angle.asRadians()), sin(angle.asRadians()));
}

sf::Angle getAngle(sf::Vector2f v)
{
    float radians = atan2f(v.y, v.x);
    return sf::radians(radians);
}

sf::Vector2f normalized(sf::Vector2f v)
{
    auto l = norm(v);
    if (l == 0)
        return {};
    return v / l;
}

bool isPointInMinMaxBox(sf::Vector2f v, sf::Vector2f min, sf::Vector2f max)
{
    return v.x > min.x && v.x < max.x && v.y > min.y && v.y < max.y;
}

bool isPointInCircle(sf::Vector2f point, sf::Vector2f centre, float radius)
{
    return norm(point - centre) <= radius;
}

bool circlesIntersectCheck(sf::Vector2f centre1, float radius1, sf::Vector2f centre2, float radius2)
{
    return norm(centre1 - centre2) <= radius1 + radius2;
}

float uniform01()
{
    return std::rand() % 10'000 / 10'000.0f;
}

float uniform01Inclusive()
{
    return std::rand() % 10'001 / 10'000.0f;
}

float uniform(float minInclusive, float maxExclusive)
{
    return uniform01() * (maxExclusive - minInclusive) + minInclusive;
}

float uniformInclusive(float min, float max)
{
    return uniform01Inclusive() * (max - min) + min;
}

float invLerp(float valueInterval, float startInterval, float endInterval)
{
    return (valueInterval - startInterval) / (endInterval - startInterval);
}

float lerp(float interpolationFactor, float startInterval, float endInterval)
{
    return interpolationFactor * (endInterval - startInterval) + startInterval;
}

float lerp(float valueIntervalA, float startIntervalA, float endIntervalA, float startIntervalB, float endIntervalB)
{
    return lerp(invLerp(valueIntervalA, startIntervalA, endIntervalA), startIntervalB, endIntervalB);
}
