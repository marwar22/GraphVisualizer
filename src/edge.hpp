#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
class Edge{
public:
    int id, idVertexFrom, idVertexTo;
    int weight1, weight2;

    bool hasMultiple;
    std::vector<int> sameFromTo;
    sf::Vector2f midEdgePosition;
    //std::vector<sf::Vector2f> middlePoints;
	sf::Vector2f midEdgeForce;    
    sf::Text t1, t2;
    sf::Color color;
    void SetColor(sf::Color);
    Edge();
    Edge(int,int,int,int,sf::Font*);
};


#endif
