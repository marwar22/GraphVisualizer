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
#include "utils.cpp"

Vertex::Vertex(sf::Vector2f __position, int __id, sf::Font& font){
    position = __position;
	id = __id;
    text1.setString(std::to_string(id));
    text1.setFont(font);
    text1.setOrigin(sf::Vector2f(text1.getGlobalBounds().width/2,text1.getGlobalBounds().height/2));
    text1.setCharacterSize(20);
    force = sf::Vector2f(0.f,0.f);
    color = sf::Color::Red;
    isBeingMoved = false;
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
    //Text (const String &string, const Font &font, unsigned int characterSize=30)
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
    std::cerr<<"Usuwanie v: "<<id<<std::endl;
    std::set<int> S;
    
    for (int i = 0; i < vertices[id].edgesIdFrom.size(); i++){  
        int edgeId = vertices[id].edgesIdFrom[i];
        std::cerr<<edgeId<<std::endl;
        S.insert(edgeId);
    }

    //std::<<cerr<<"vertices[id].edgesIdTo.size(): "<<vertices[id].edgesIdTo.size()<<std::endl;
    for (int i = 0; i < vertices[id].edgesIdTo.size(); i++){  
        int edgeId = vertices[id].edgesIdTo[i];
        std::cerr<<edgeId<<std::endl;
        S.insert(edgeId);        
    }


    // 0,1,2,3,4,5
    // USUN 2,4
    // 0, 1, 3, 5
    // 
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
        ChangeAll(allEdges[i].id, i); //zmien (Z, DO)
        allEdges[i].id = i;
    }
    /* parametry dla Edge: id, idVertexFrom, idVertexTo;        
        OK, 1) usuwamy krawędzie From v i To v
            
        OK, 2) -> wywalamy te krawędzie z list w wierzchołku, bez reindeksacji
        3) -> dla kazdej kraw, swap dla allEdges, i wtedy reindeksacje dla fromV i toV dla Vertices

        //ostatni wierzchołek wszędzie przyjmuje id tego co usuwamy
    */

    // 0,1,2, 3DU ,4,5,6;
    //lastVId = 6;

    //6 -> czegoś
    //3 -> czegośB
    //int lastVId = vertices.size()-1;
    for (int e: vertices.back().edgesIdFrom) allEdges[e].idVertexTo   = id;
    //E[0] 1 -> 2 //from 1 to 2
    //allEdges[0].idVertexFrom = 1
    //allEdges[0].idVertexTo = 2

    //vertices[1].edgesIdFrom = {}
    //vertices[1].edgesIdTo   = {0} //edgesidto zawiera krawędzie z których 1 prowadzi, czyli 1 -> x, 
                                    //edgesidto zawiera krawędzie dla których 1 jest "to",czyli takie x, że x -> 1
    //vertices[2].edgesIdFrom = {0}
    //vertices[2].edgesIdTo   = {}
    //1 from wychodzi krawędź 0;
    //2 to wchodzi krawędź 0;
    for (int e: vertices.back().edgesIdTo  ) allEdges[e].idVertexFrom = id;
    std::swap(vertices[id],vertices.back());
    vertices[id].id = id;
    vertices.pop_back();
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