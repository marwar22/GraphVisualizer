#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "vertex.hpp"
#include "edge.hpp"


class Graph {
public:
    std::vector<Vertex> vertices; //wszystkie wierzchołki
	std::vector<Edge> allEdges; //wszystkie krawędzie
    sf::Font * font;
    bool isDirected, isWeighted;

	float CenterGravityForce(float);
	float VertexRepulsionForce(float);
	float EdgeAttractionForce(float);//w argumentach indeksy wierzcholkow

	void CalculateForces(const int width,const int height);
	void ApplyForces(const int width,const int height);

    void AddEdge(int,int,int,int);
    void ChangeAll(int,int);
    void AddVertex(sf::Vector2f);
    void RemoveEdgeFromVertex(int,int);
	void RemoveEdge(int);
    void RemoveVertex(int);

	void Draw(sf::RenderTarget&);
    Graph( sf::Font *);
    Graph();
    Graph(Graph*);
};

#endif