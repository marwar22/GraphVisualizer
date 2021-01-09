#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include "graph.hpp"
#include "edge.hpp"
#include "utils.hpp"
#define pb push_back

Edge::Edge(){
    idVertexFrom = idVertexTo = weight1 = weight2 = -1;
}

Edge::Edge(int v, int w, int w1, int w2,sf::Font *font) {
    idVertexFrom = v;
    idVertexTo = w;
    weight1 = w1;
    weight2 = w2;
    color = sf::Color::Black;//defaultowo na czarny
    t1.setFont(*font);
    t2.setFont(*font);
    t1.setString(std::to_string(w1));
    t2.setString(std::to_string(w1));
    t1.setCharacterSize(15);
    t2.setCharacterSize(15);
    t1.setOrigin(sf::Vector2f(t1.getGlobalBounds().width/2,t1.getGlobalBounds().height/2));
    t2.setOrigin(sf::Vector2f(t2.getGlobalBounds().width/2,t2.getGlobalBounds().height/2));
}

void Edge::SetColor(sf::Color temp_color){
    color = temp_color;
}

void Graph::AddEdge(int v,int w, int weight1=0, int weight2=0) {
	Edge edge = Edge(v, w, weight1, weight2,font);
	edge.midEdgePosition.x = (vertices[v].position.x + vertices[w].position.x)/2;
	edge.midEdgePosition.y = (vertices[v].position.y + vertices[w].position.y)/2;
	edge.id = allEdges.size();
    vertices[edge.idVertexFrom].edgesIdTo.push_back(edge.id);
    vertices[edge.idVertexTo].edgesIdFrom.push_back(edge.id);
    allEdges.push_back(edge);
}

void Graph::AddEdge(int v,int w, int weight1=0, int weight2=0,int midEPosX=0,int midEPosY=0) {
	Edge edge = Edge(v, w, weight1, weight2,font);
	edge.midEdgePosition.x = midEPosX;
	edge.midEdgePosition.y = midEPosY;
	edge.id = allEdges.size();
    vertices[edge.idVertexFrom].edgesIdTo.push_back(edge.id);
    vertices[edge.idVertexTo].edgesIdFrom.push_back(edge.id);
    allEdges.push_back(edge);
}

void Graph::RemoveEdgeFromVertex(int id,int v) {
    for (int i = 0; i < vertices[v].edgesIdFrom.size(); ++i) {
        if (vertices[v].edgesIdFrom[i] == id) {
            std::swap(vertices[v].edgesIdFrom[i],vertices[v].edgesIdFrom.back());
            vertices[v].edgesIdFrom.pop_back();
            return;
        }
    }
    for (int i = 0; i < vertices[v].edgesIdTo.size(); ++i) {
        if (vertices[v].edgesIdTo[i] == id) {
            std::swap(vertices[v].edgesIdTo[i],vertices[v].edgesIdTo.back());
            vertices[v].edgesIdTo.pop_back();
            return;
        }
    }
}


void Graph::RemoveEdge(int id) {
    std::cerr<<"Usuwanie edge "<<id<<" "<<allEdges[id].idVertexFrom<<" "<<allEdges[id].idVertexTo<<std::endl;
    RemoveEdgeFromVertex(id,allEdges[id].idVertexFrom);
    RemoveEdgeFromVertex(id,allEdges[id].idVertexTo);
    std::swap(allEdges[id],allEdges.back());
    allEdges.pop_back();
    for (int &v: vertices[allEdges[id].idVertexFrom].edgesIdFrom) {
        if (v == allEdges.size()) {
            v = id;
            break;
        }
    }
    for (int &v: vertices[allEdges[id].idVertexTo].edgesIdTo) {
        if (v == allEdges.size()) {
            v = id;
            break;
        }
    }    
    for(int i=0; i<allEdges.size(); i++)
        allEdges[i].id = i;
    
    for (int &v: vertices[allEdges[id].idVertexFrom].edgesIdTo) {
        if (v == allEdges.size()) {
            v = id;
        }
    }
    
    for (int &v: vertices[allEdges[id].idVertexTo].edgesIdFrom) {
        if (v == allEdges.size()) {
            v = id;
        }
    }


    std::cerr<<"\n\npo usunieciu"<<std::endl;
    for(Vertex v2: vertices) {
        std::cerr<<"V: "<<v2.id<<std::endl;
    }
                        
    std::cerr<<"edges:"<<std::endl;
    for(Edge e2: allEdges) {
        std::cerr<<"E: "<<e2.id<<" "<<e2.idVertexFrom<<", "<<e2.idVertexTo<<std::endl;
    }
}
