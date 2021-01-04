#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "graph.hpp"

std::mt19937 rnd(21);
int los(int mi,int mx) {return rnd()%(mx-mi+1)+mi;}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Projekt PWI");
    sf::CircleShape shape(100.f,100);
    shape.setFillColor(sf::Color::Green);
    
    Graph G;
    if (!G.font.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    
    window.setFramerateLimit(100);
    int n = 3, m = 0;
    /*G.AddVertex(sf::Vector2f(1000,200));
    G.AddVertex(sf::Vector2f(100,800));*/

    {
        
        for (int i = 0; i < n; ++i) G.AddVertex(sf::Vector2f(los(0,1500),los(0,700)));

        for (int i = 0; i < n; ++i){
            for (int j = i + 1; j < n; ++j) {
                /*int v,w;
                std::cin >> v >> w;*/
                G.AddEdge(i,j,0,0);
            }
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
        G.CalculateForces();
        G.ApplyForces();
        window.clear(sf::Color::White);        
        G.Draw(window);
        window.display();
    }

    return 0;
}
