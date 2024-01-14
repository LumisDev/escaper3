#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_world.h>
#include <box2d/b2_math.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_polygon_shape.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Escaper 3");
    window.setFramerateLimit(30);
    // Create a Box2D world
    b2Vec2 gravity(0.0f, 30.0f);
    b2World world(gravity);

    // Create a dynamic circle body
    b2BodyDef circleBodyDef;
    circleBodyDef.type = b2_dynamicBody;
    circleBodyDef.position.Set(400.0f, 100.0f);

    b2Body* circleBody = world.CreateBody(&circleBodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 20.0f; // Radius of the circle

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    fixtureDef.filter.categoryBits = 0x0002;
    fixtureDef.filter.maskBits = 0x0001;

    circleBody->CreateFixture(&fixtureDef);

    b2BodyDef rectangleBodyDef;
    rectangleBodyDef.type = b2_staticBody;
    rectangleBodyDef.position.Set(400.0f, 300.0f);

    b2Body* rectangleBody = world.CreateBody(&rectangleBodyDef);
    b2PolygonShape rectangleShape;
    rectangleShape.SetAsBox(200.0f, 100.0f);

    b2FixtureDef rectangleFixtureDef;
    rectangleFixtureDef.shape = &rectangleShape;
    rectangleFixtureDef.density = 1.0f;
    rectangleFixtureDef.friction = 0.3f;

    rectangleBody->CreateFixture(&rectangleFixtureDef);

    // Create an SFML circle shape
    sf::CircleShape circle(20.0f); // Radius of the circle
    sf::Color color(255, 0, 0);
    circle.setFillColor(color);

    sf::RectangleShape rectangle(sf::Vector2f(200, 100));
    sf::Color recColor(255, 0, 0);
    rectangle.setFillColor(recColor);
    rectangle.setPosition(rectangleBodyDef.position.x-200, rectangleBodyDef.position.y-100);

    // Main loop

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update physics simulation
        world.Step(1.f / 30.f, 8, 3);

        // Update object position based on Box2D physics
        b2Vec2 position = circleBody->GetPosition();
        circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius());
        window.clear();
        window.draw(rectangle);
        window.draw(circle);
        window.display();
    }

    return 0;
}
