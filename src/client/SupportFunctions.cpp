#include "consts.h"

float norm(sf::Vector2f v)
{
    return v.x * v.x + v.y * v.y;
}

float vlen(sf::Vector2f v)
{
    return std::hypotf(v.x, v.y);
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}