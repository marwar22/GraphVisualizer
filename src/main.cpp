#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "graph.hpp"
#include "graphics/button.hpp"

std::mt19937 rnd(1234567);
int los(int mi,int mx) {return rnd()%(mx-mi+1)+mi;}
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Projekt PWI",sf::Style::Default,settings);
    sf::CircleShape shape(100.f,100);
    shape.setFillColor(sf::Color::Green);
    
    sf::Font gfont;
    if (!gfont.loadFromFile("Fonts/ABeeZee-Regular.ttf"))
		throw("NIE MA CZCIONKI\n");
    Graph G(&gfont);
    Button B1(1000,600,100,50,"przycisk",&gfont);
    

    window.setFramerateLimit(100);
    int n = 27, m = 0;
    /*G.AddVertex(sf::Vector2f(1000,200));
    G.AddVertex(sf::Vector2f(100,800));*/

    for (int i = 0; i < n; ++i) G.AddVertex(sf::Vector2f(los(0,1500),los(0,700)));

    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j) {
            /*int v,w;
            std::cin >> v >> w;*/
            int p;
            if (j-i <= 1)       p = 700;
            else if (j-i <= 2)  p = 100;
            else if (j-i <= 5)  p = 50;
            else if (j-i <= 7)  p = 30;
            else if (j-i <= 10) p = 10;
            else p = 2;
            //p=1000;
            if (los(1,1000) <= p) G.AddEdge(i,j,0,0);
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
        B1.draw(window);
        window.display();
    }

    return 0;
}
