#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <set>
#include <iostream>
#include <algorithm>
#include "vertex.hpp"
#include "graph.hpp"
#include "utils.hpp"

Vertex::Vertex(sf::Vector2f __position, int __id, sf::Font& font){
    position = __position;
	id = __id;
    text1.setString(std::to_string(id));
    text1.setFont(font);
    text1.setOrigin(sf::Vector2f(text1.getGlobalBounds().width/2,text1.getGlobalBounds().height/2));
    text1.setCharacterSize(20);
    subText.setString("");
    subText.setFont(font);
    subText.setOrigin(sf::Vector2f(subText.getGlobalBounds().width/2,subText.getGlobalBounds().height/2));
    subText.setCharacterSize(20);
    subText2.setString("");
    subText2.setFont(font);
    subText2.setOrigin(sf::Vector2f(subText2.getGlobalBounds().width/2,subText2.getGlobalBounds().height/2));
    subText2.setCharacterSize(20);
    force = sf::Vector2f(0.f,0.f);
    color = sf::Color::Red;
    data1 = data2 = 0;
    isBeingChosen = false;
}

void Vertex::SetColor(sf::Color temp_color){
    color = temp_color;
}
void Vertex::KeepInGraphArea(int width, int height) {
        if (position.x < GRAPH_AREA_BORDER)          position.x = GRAPH_AREA_BORDER;
        if (position.x > width  - GRAPH_AREA_BORDER) position.x = width  - GRAPH_AREA_BORDER;
        if (position.y < GRAPH_AREA_BORDER)          position.y = GRAPH_AREA_BORDER;
        if (position.y > height - GRAPH_AREA_BORDER) position.y = height - GRAPH_AREA_BORDER;
}
void Graph::AddVertex(sf::Vector2f position){
    int newId = vertices.size();
    sf::Text text1("",*font);
    Vertex vertexToAdd = Vertex(position, newId, *font);
    vertices.push_back(vertexToAdd);
}

void Graph::ChangeAll(int from, int to) {
    for (Vertex &v: vertices){
        for (int i=0; i<v.edgesIdTo.size(); i++)
            if (v.edgesIdTo[i] == from)
                v.edgesIdTo[i] = to;

        for (int i=0; i<v.edgesIdFrom.size(); i++)
            if (v.edgesIdFrom[i] == from)
                v.edgesIdFrom[i] = to;
    }    
}

void Graph::RemoveVertex(int id) {
    std::set<int> S;
    
    for (int i = 0; i < vertices[id].edgesIdFrom.size(); i++){  
        int edgeId = vertices[id].edgesIdFrom[i];
        S.insert(edgeId);
    }

    for (int i = 0; i < vertices[id].edgesIdTo.size(); i++){  
        int edgeId = vertices[id].edgesIdTo[i];
        S.insert(edgeId);        
    }

    for (auto it = S.begin(); it != S.end(); it++) {
        RemoveEdgeFromVertex(*it, allEdges[*it].idVertexFrom);
        RemoveEdgeFromVertex(*it, allEdges[*it].idVertexTo);
    }
    auto it =S.end();
    while (S.size()) {
        --it;
        allEdges.erase(allEdges.begin()+ *it);
        if (it == S.begin()) break;
    }
    for (int i=0; i < allEdges.size(); i++) {
        ChangeAll(allEdges[i].id, i); 
        allEdges[i].id = i;
    }

    for (int e: vertices.back().edgesIdFrom) allEdges[e].idVertexTo   = id;
    for (int e: vertices.back().edgesIdTo  ) allEdges[e].idVertexFrom = id;
    
    std::swap(vertices[id],vertices.back());
    vertices[id].id = id;
    vertices.pop_back();
}
