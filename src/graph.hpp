#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#define N 1000
typedef std::pair<int, int> pii;
typedef std::vector<int> VI;
typedef std::vector<std::pair<int, int> > VII;

class Vertex{
public:
	int id;///5
    sf::Text text1;
	sf::Vector2f position;
	sf::Vector2f force;
    std::vector<int> edgesIdFrom;/////  1 2 3 4 ..  7 8 9 10 11 12 13
    std::vector<int> edgesIdTo;
	sf::Sprite circle;
	Vertex();
	Vertex(sf::Vector2f, int, sf::Font&);
};

class Edge{
public:
    int id, idVertexFrom, idVertexTo;
    int weight1, weight2;
    bool isHighlighted;

    Edge();
    Edge(int,int,int,int);
};	

class Graph {
public:
    std::vector<Vertex> vertices; //wszystkie wierzchołki
	std::vector<Edge> allEdges; //wszystkie krawędzie
    sf::Font font;
    bool isDirected, isWeighted;

	float GravityForce(float);
	float RepulsionForce(float);
	float AttractionForce(float);//w argumentach indeksy wierzcholkow

	void CalculateForces();
	void ApplyForces();

    void AddEdge(int,int,int,int);
    void AddVertex(sf::Vector2f);
    void RemoveEdgeFromVertex(int,int);
	void RemoveEdge(int);
    void RemoveVertex(int);


	void Draw(sf::RenderWindow&);
    Graph();
};

#endif