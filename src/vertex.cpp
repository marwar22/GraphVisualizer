#include "vertex.hpp"
#include "graph.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>

Vertex::Vertex(sf::Vector2f __position, int __id, sf::Font& font){
    position = __position;
	id = __id;
    text1.setString(std::to_string(id));
    text1.setFont(font);
    force = sf::Vector2f(0.f,0.f);
    color = sf::Color::Red;
}

void Vertex::SetColor(sf::Color temp_color){
    color = temp_color;
}

void Graph::AddVertex(sf::Vector2f position){
    int newId = vertices.size();
    sf::Text text1("",*font);
    //Text (const String &string, const Font &font, unsigned int characterSize=30)
    Vertex vertexToAdd = Vertex(position, newId, *font);
    vertices.push_back(vertexToAdd);
}

void Graph::RemoveVertex(int id) {
    
    for (int w: vertices[id].edgesIdFrom) RemoveEdge(w);
    for (int w: vertices[id].edgesIdTo) RemoveEdge(w);
    
    std::swap(vertices[id], vertices.back());
    vertices.pop_back();
    if (id == 0) return;
    vertices[id].id = id;
    for (int w: vertices[id].edgesIdFrom) {
        if (allEdges[w].idVertexFrom == vertices.size()) allEdges[w].idVertexFrom = id;
        if (allEdges[w].idVertexTo   == vertices.size()) allEdges[w].idVertexTo   = id;
    }
    for (int w: vertices[id].edgesIdTo) {
        if (allEdges[w].idVertexFrom == vertices.size()) allEdges[w].idVertexFrom = id;
        if (allEdges[w].idVertexTo   == vertices.size()) allEdges[w].idVertexTo   = id;
    }
}


/*
sf::Color::     Black
                White
                Red
                Green
                Blue
                Yellow
                Magenta
                Cyan
                Transparent
                sf::Color(r,g,b,a);
*/