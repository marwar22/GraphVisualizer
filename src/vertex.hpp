#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

typedef std::pair<int, int> pii;
typedef std::vector<int> VI;
typedef std::vector<std::pair<int, int> > VII;

class Vertex{
public:
	int id;

    std::vector<int> edgesIdFrom;
    std::vector<int> edgesIdTo;
    
    sf::Text text1;
	sf::Vector2f position;
	sf::Vector2f force;
	sf::Sprite circle;
    sf::Color color;

    void SetColor(sf::Color);

	Vertex();
	Vertex(sf::Vector2f, int, sf::Font&);
};

#endif