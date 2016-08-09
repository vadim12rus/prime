#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

using namespace sf;
void populate(std::list<RectangleShape>& objects, float x, float y)
{
    RectangleShape s(Vector2f(20, 20));
    s.setPosition(x, y);
    s.setFillColor(Color::Green);
    objects.push_back(s);
}

int main()
{
    RenderWindow window(sf::VideoMode(480, 320), "view demo");
    
    RectangleShape player(Vector2f(20, 20));
    player.setFillColor(Color::Red);
    player.setOrigin(10, 10);
    player.setPosition(240, 160);
    const float player_speed = 100;

    std::list<RectangleShape> objects;
    populate(objects, 310, 50);
    populate(objects, 100, 200);
    populate(objects, 250, 160);
    populate(objects, 10, 280);
    populate(objects, 70, 30);
    populate(objects, 120, 50);

    View player_view(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    
    sf::Clock clock;
    bool running = true;
	while (window.isOpen())
    {
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
			{
				window.close();
			}
        }

        float frametime = clock.getElapsedTime().asSeconds();
		//std::cout << frametime << std::endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
            player.move(0, -player_speed * 0.001);
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
            player.move(0, player_speed * 0.001);
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
            player.move(-player_speed * 0.001, 0);
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
            player.move(player_speed * 0.001, 0);
		}
    
        clock.restart();

        player_view.setCenter(player.getPosition());
        window.setView(player_view);

        window.draw(player);
        for (std::list<RectangleShape>::const_iterator it = objects.begin(); it != objects.end(); ++it)
        {
            window.draw(*it);
        }
        window.display();
        window.clear();
    }
    return 0;
}
 
