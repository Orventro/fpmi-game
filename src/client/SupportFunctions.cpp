#include "consts.h"

float norm(sf::Vector2f v)
{
    return v.x * v.x + v.y * v.y;
}

float vlen(sf::Vector2f v)
{
    return std::hypotf(v.x, v.y);
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

int64_t get_microseconds(std::chrono::nanoseconds a)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(a).count();
}

std::mt19937 rng;