#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "vertex.hpp"
typedef std::pair<int, int> pii;
typedef std::vector<int> VI;
typedef std::vector<std::pair<int, int> > VII;



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
    sf::Font * font;
    bool isDirected, isWeighted;

	float CenterGravityForce(float);
	float VertexGravityForce(float);
	float EdgeAttractionForce(float);//w argumentach indeksy wierzcholkow

	void CalculateForces();
	void ApplyForces();

    void AddEdge(int,int,int,int);
    void AddVertex(sf::Vector2f);
    void RemoveEdgeFromVertex(int,int);
	void RemoveEdge(int);
    void RemoveVertex(int);


	void Draw(sf::RenderWindow&);
    Graph( sf::Font *);
};

#endif