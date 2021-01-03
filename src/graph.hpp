#include <string>
#include <vector>
#include "graphics.cpp"
//class Vertex;
class Edge;

class Vertex{
public:
    //std::string text;    
    float value1;
    sf::Vector2f position;
    //int value2;
    std::vector<std::vector<Edge>::iterator> edgesOf;
};

class Edge{
public:
    //std::string text;
    std::vector<Vertex>::iterator v1;
    std::vector<Vertex>::iterator v2;    
    //int value1;
    //int value2;    
};

class Graph{
public:
    std::vector<Vertex>  vertices;
    std::vector<Edge> edges;
    
    GraphGraphics graphics;
    Graph();
    void CalculateForces();
	void ApplyForces();
    void AddEdge(int,int);
    void AddVertex(int);
    void Draw(sf::RenderWindow&);
};