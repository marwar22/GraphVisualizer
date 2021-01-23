#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include "../graph.hpp"
#include "../steps.hpp"
#include "../utils.hpp"
#include <queue>
#define INF 2000000000

void MST(Graph *G,StepList *StepListPtr, std::vector<int> &chosenV) {    
    G->isDirected = 0;

    Graph GKopia(G);
    std::vector<VertexChange> initVerticesChanges;
    std::vector<EdgeChange> initEdgesChanges;
    for (Vertex &v: GKopia.vertices) {
        v.data1 = 0;
        v.data2 = 0;
        v.color = sf::Color::Magenta; 
        VertexChange singleChange = VertexChange(v);
        initVerticesChanges.push_back(singleChange);
    }
    
    std::priority_queue<std::pair<int,std::pair<int,int>>,std::vector<std::pair<int,std::pair<int,int>>>,std::greater<std::pair<int,std::pair<int,int>> > > Q;
    Q.push({0,{chosenV[0], -1}});
    Step initStep = Step(initVerticesChanges,initEdgesChanges);
    StepListPtr->InitState(initStep);

    std::vector<int> prvEdgesId;
    int prvVId = -1;
    int stepCounter = 0;
    while (!Q.empty()) {
        int v = Q.top().second.first;
        int edgeId = Q.top().second.second;
        int distance = Q.top().first; 
        Q.pop();
        if(GKopia.vertices[v].data1 == 1)
            continue;

        GKopia.vertices[v].data1 = 1;       
        GKopia.vertices[v].color = sf::Color::Red;
        
        std::vector<VertexChange> nVerticesChanges;
        std::vector<EdgeChange> nEdgesChanges;
        while (prvEdgesId.size()) {
            GKopia.allEdges[prvEdgesId.back()].color = sf::Color::Black;
            nEdgesChanges.push_back(GKopia.allEdges[prvEdgesId.back()]);
            prvEdgesId.pop_back();
        }

        if (edgeId != -1){  
            GKopia.allEdges[edgeId].color = sf::Color::Red;
            GKopia.allEdges[edgeId].isHighlighted = true;
            nEdgesChanges.push_back(EdgeChange(GKopia.allEdges[edgeId]));
        }
        if (prvVId != -1){
            GKopia.vertices[prvVId].color = sf::Color(0,100,0);
            nVerticesChanges.push_back(VertexChange(GKopia.vertices[prvVId]));   
        }
        Step nStep = Step(nVerticesChanges, nEdgesChanges);
        StepListPtr->AddState(nStep);
        prvVId = v;
        nVerticesChanges.clear();
        nEdgesChanges.clear();

        nVerticesChanges.push_back(VertexChange(GKopia.vertices[v]));
        nStep = Step(nVerticesChanges, nEdgesChanges);
        StepListPtr->AddState(nStep);
        nVerticesChanges.clear();
        
        for(int id: GKopia.vertices[v].edgesIdFrom) {
            if(GKopia.vertices[GKopia.allEdges[id].idVertexFrom].data1 == 0)   {
                int u = GKopia.allEdges[id].idVertexFrom;
                Q.push({GKopia.allEdges[id].weight1,{u, id}});

                GKopia.vertices[u].color = sf::Color::Green;
                GKopia.allEdges[id].color = sf::Color::White;
                
                nVerticesChanges.push_back(VertexChange(GKopia.vertices[u]));
                nEdgesChanges.push_back(EdgeChange(GKopia.allEdges[id]));
                prvEdgesId.push_back(id);
            }         
        }
        
        for(int id: GKopia.vertices[v].edgesIdTo) {
            if(GKopia.vertices[GKopia.allEdges[id].idVertexTo].data1 == 0){
                int u = GKopia.allEdges[id].idVertexTo;
                Q.push({GKopia.allEdges[id].weight1,{u, id}});
                GKopia.vertices[u].subText.setString("vis");
                GKopia.vertices[u].color = sf::Color::Green;
                GKopia.allEdges[id].color = sf::Color::White;

                nVerticesChanges.push_back(VertexChange(GKopia.vertices[u]));
                nEdgesChanges.push_back(EdgeChange(GKopia.allEdges[id]));
                prvEdgesId.push_back(id);
            }
        }

        Step nStep2 = Step(nVerticesChanges, nEdgesChanges);
        if(nVerticesChanges.size()) StepListPtr->AddState(nStep2);
    }

    // Dot. ostatniego kroku (wierzchołka)
    std::vector<VertexChange> nLVerticesChanges;
    std::vector<EdgeChange> nLEdgesChanges;
    if (prvVId != -1){
        GKopia.vertices[prvVId].color = sf::Color(0,100,0);
        nLVerticesChanges.push_back(VertexChange(GKopia.vertices[prvVId]));   
    }
    Step nStep = Step(nLVerticesChanges, nLEdgesChanges);
    StepListPtr->AddState(nStep);
}