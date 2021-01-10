#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

class MidEdge{
public:
    sf::Vector2f position;
	sf::Vector2f force;
    MidEdge();
    MidEdge(int,int);
};

class Edge{
public:
    int id, idVertexFrom, idVertexTo;
    int weight1, weight2;

    bool hasMultiple;
    std::vector<int> sameFromTo;
    
    MidEdge midEFrom,midETo;

    sf::Text t1, t2;
    sf::Color color;
    void SetColor(sf::Color);
    Edge();
    Edge(int,int,int,int,sf::Font*);
};


#endif
