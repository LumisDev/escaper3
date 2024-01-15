#include <SFML/Graphics.hpp>
#include <box2D/box2D.h>
#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

// Create the main window



int main()
{
           
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML + Box2D Example");
    window.setFramerateLimit(60);

    // Create a Box2D world
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    b2BodyDef circleBodyDef;
    circleBodyDef.type = b2_dynamicBody;
    circleBodyDef.position.Set(400.0f, 100.0f);

    b2BodyDef rectangleBodyDef;
    rectangleBodyDef.type = b2_staticBody;
    rectangleBodyDef.position.Set(400.0f, 300.0f);

    // Create the body

    b2Body* circleBody = world.CreateBody(&circleBodyDef);
    b2Body* rectangleBody = world.CreateBody(&rectangleBodyDef);

    // Create the shape
    b2CircleShape circleShape;
    circleShape.m_radius = 20.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    circleBody->CreateFixture(&fixtureDef);
    b2PolygonShape rectangleShape;
    rectangleShape.SetAsBox(50.0f, 25.0f);
    fixtureDef.shape = &rectangleShape;
    rectangleBody->CreateFixture(&fixtureDef);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::Space:
                            circleBody->ApplyForceToCenter(b2Vec2(0.0f, -100.0f), true);
                            break;
                        case sf::Keyboard::Left:
                            circleBody->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f), true);
                            break;
                        case sf::Keyboard::Right:
                            circleBody->ApplyForceToCenter(b2Vec2(100.0f, 0.0f), true);
                            break;
                        case sf::Keyboard::Up:
                            circleBody->ApplyForceToCenter(b2Vec2(0.0f, -100.0f), true);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        // Update Box2D world
        world.Step(1.0f / 60.0f, 8, 3);

        // Clear the window
        window.clear(sf::Color::Cyan);

        // Draw the circle at the updated position
        sf::CircleShape sfmlCircle(20.0f);
        sfmlCircle.setFillColor(sf::Color::Red);
        sfmlCircle.setOrigin(20.0f, 20.0f);
        sfmlCircle.setOutlineColor(sf::Color::White);
        sfmlCircle.setOutlineThickness(1.0f);
        sfmlCircle.setPosition(circleBody->GetPosition().x, circleBody->GetPosition().y);
        sf::RectangleShape sfmlRectangle(sf::Vector2f(100.0f, 50.0f));
        sfmlRectangle.setFillColor(sf::Color::Black);
        sfmlRectangle.setOrigin(50.0f, 25.0f);
        sfmlRectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);
        sfmlRectangle.setRotation(rectangleBody->GetAngle() * 180.0f / b2_pi);
        sfmlRectangle.setScale(1, 1);
        sfmlRectangle.setOutlineColor(sf::Color::White);
        sfmlRectangle.setOutlineThickness(1.0f);
        // Draw the circle
        window.draw(sfmlCircle);
        window.draw(sfmlRectangle);
        // Display the contents of the window
        window.display();
    }

    return 0;
}
