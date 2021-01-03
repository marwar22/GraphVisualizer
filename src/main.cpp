#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "graph.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Projekt PWI");
    sf::CircleShape shape(100.f,100);
    shape.setFillColor(sf::Color::Green);
    
    Graph G;
    //if (!G.graphics.font.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		//throw("NIE MA CZCIONKI\n");
    
    window.setFramerateLimit(100);
    int n=20, m=0;
    //std::cin >> n >> m; 
    {
        int n2 = n,m2 = m;
        while (n2--) {
            G.AddVertex(n2+1);
        }
        while (m2--) {
            int v, w;
            std::cin >> v >> w;
            G.AddEdge(v,w);
        }
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        G.Draw(window);
        window.display();
    }

    return 0;
}
