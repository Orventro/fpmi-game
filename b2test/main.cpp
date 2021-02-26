#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

int main() {
    b2Vec2 gravity(0.0f, 10.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 20.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    sf::RenderWindow window(sf::VideoMode(1080, 720), "Box2d test");
    sf::CircleShape box(40, 4);

    int fps = 60;
    float timeStep = 1.0f / fps;

    window.setFramerateLimit(fps);

    int frame = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // body.
        }

        world.Step(timeStep, 6, 2);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();

        box.setPosition(position.x*100, position.y*100);
        box.setRotation(angle+45);

        window.clear();
        window.draw(box);
        window.display();
    }
}