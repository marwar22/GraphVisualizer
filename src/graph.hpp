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
	float EdgeAttractionForce(float);
    float MidEdgeOtherMidEdgeRepulsionForce(float);
    float MidEdges1EdgeAttractionForce(float,float);
	float MidEdgeVertexAttractionForce(float,float);

    void CalculateRepulsionForceMidEdges(MidEdge &me1, MidEdge &me2);

	void CalculateForces(const int width,const int height);
	void ApplyForces(const int width,const int height);

    void AddEdge(int,int,int,int);
    void AddEdge(int,int,int,int,sf::Vector2f,sf::Vector2f);
    void ChangeAll(int,int);
    void AddVertex(sf::Vector2f);
    void RemoveEdgeFromVertex(int,int);
	void RemoveEdge(int);
    void RemoveVertex(int);

    void AddMiddlePointsToEdge(Edge &);
    float midPointRepulsionForce(sf::Vector2f, sf::Vector2f);

	void Draw(sf::RenderTarget&,bool editLook);
    Graph( sf::Font *);
    Graph();
    Graph(Graph*);
};

#endif