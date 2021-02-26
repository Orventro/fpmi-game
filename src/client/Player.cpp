#include "Player.h"

Player::Player(sf::Vector2f _position) :
    position(_position),
    velocity(0,0),
    health(1),
    origin(50,50),
    traingle(50,3),
    lastShot(chrono::system_clock::now())
{
    traingle.setOrigin(origin);
    traingle.setFillColor(sf::Color::White);
}

void Player::accelerate(sf::Vector2f acceleration)
{
    velocity += acceleration;
}

void Player::rotate_to(sf::Vector2f target)
{
    sf::Vector2f delta = target - position;
    targetAngle = atan2(delta.y, delta.x);
    traingle.setRotation(targetAngle * 180 / M_PI + 90);
}

bool Player::render(sf::RenderWindow& window)
{   
    position += velocity;
    velocity *= .8f;
    traingle.setPosition(position);
    // traingle.rotate(1.1f);

    window.draw(traingle);

    sf::CircleShape circle(5.f);
    circle.setOrigin(5.0f, 5.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(position);
    window.draw(circle);

    return 1;
}

sf::Vector2f Player::getPosition()
{
    return position;
}

Bullet* Player::shoot()
{
    auto t = chrono::high_resolution_clock::now();
    if(t - lastShot <= RELOAD_TIME)
        return 0;
    else {
        lastShot = t;
        sf::Vector2f direction(cos(targetAngle), sin(targetAngle));
        return new Bullet(position + direction*50.0f, direction*BULLET_SPEED , targetAngle * 180 / M_PI);
    }
}