#include "graph.hpp"
#include <vector>
#include <random>
std::mt19937 rnd;
int los(int mi,int mx) {return rnd() % (mx-mi+1)+mi;}

Graph::Graph() {
	graphics.font.loadFromFile("Fonts/ABeeZee-Regular.ttf"); 
}

void Graph::AddEdge(int v,int w) {
    Edge edge;
    edge.v1 = vertices.begin() + v - 1;
    edge.v2 = vertices.begin() + w - 1;
    edges.push_back(edge);
    vertices[v-1].edgesOf.push_back(edges.end()-1);
    vertices[w-1].edgesOf.push_back(edges.end()-1);
}

void Graph::AddVertex(int v) {
    Vertex vertex;
    vertex.value1 = v;
    vertex.position = sf::Vector2f(los(0,1500),los(0,700));
    vertices.push_back(vertex);
}
void Graph::Draw(sf::RenderWindow& window) {
    sf::CircleShape shape(20.f,100);
    shape.setFillColor(sf::Color::Green);
    for (Vertex vertex:vertices) {
        shape.setPosition(vertex.position);
        window.draw(shape);
    }
}

float Distance(sf::Vector2f v,sf::Vector2f w) {
    double dx = (v.x-w.x);
    double dy = (v.y-w.y);
    return sqrt(dx*dx + dy*dy);
}

float GetForce(float d) {
    d -= 10;
    if (d>=0) return (d*d)/1000000;
    else return d/1000000;
}

void Graph::MoveVertices() {

    for (Vertex &v : vertices) {
       v.speed.x = 0;
       v.speed.y = 0;
    }

    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = i+1; j < vertices.size(); ++j) {
            float d = Distance(vertices[i].position,vertices[j].position);
            float f = GetForce(d);
            
            float dot = (vertices[i].position.x * vertices[j].position.x) + (vertices[i].position.y * vertices[j].position.y);
            float der = (vertices[i].position.x * vertices[j].position.y) - (vertices[i].position.y * vertices[j].position.x);
            float angle = atan2(dot,der);
            vertices[i].speed -= sf::Vector2f(0,f * cos(angle));
            vertices[j].speed += sf::Vector2f(0,f * cos(angle));
        }
    }

    for (Vertex &v : vertices) {
        v.position += v.speed;
    }
}