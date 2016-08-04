#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::View view; 
    view.reset(sf::FloatRect(0, 0, window.getSize().x-100, window.getSize().y-100));
    
    Image map_image;
	map_image.loadFromFile("img/bg.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

            
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = view.getCenter().x - (window.getSize().x / 2); i <= view.getCenter().x + (window.getSize().x / 2); i += 30)
	    {
            for (int j = view.getCenter().y - (window.getSize().y / 2); j <= view.getCenter().y + (window.getSize().y / 2); j += 30)
		    {
                s_map.setTextureRect(sf::IntRect(0, 0, 30, 30));
                s_map.setPosition(i, j);
				window.draw(s_map);
		    }
	    }
        window.display();
 
    }
 
    return 0;
 
}
