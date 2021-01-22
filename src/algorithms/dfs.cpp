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

void dfs_reku(Graph &G, StepList* DFSStepList, int v) {
    G.vertices[v].data1 = 1;
    G.vertices[v].color = sf::Color(41, 230, 230);
    
    std::vector<VertexChange> verticesChanges;
    std::vector<EdgeChange> edgesChanges; 

    VertexChange onlyChange = VertexChange(G.vertices[v]);
    verticesChanges.push_back(onlyChange);
    DFSStepList->AddState(Step(verticesChanges,edgesChanges));
    verticesChanges.clear();
    edgesChanges.clear();

    if(G.isDirected == 0) {
        for(auto id: G.vertices[v].edgesIdFrom){ 
            if(G.vertices[G.allEdges[id].idVertexFrom].data1 == 0){ 
                dfs_reku(G, DFSStepList, G.allEdges[id].idVertexFrom);
            }
        }
    }
    for(auto id: G.vertices[v].edgesIdTo) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_reku(G, DFSStepList, G.allEdges[id].idVertexTo);

    G.vertices[v].color = sf::Color(36, 158, 115);
    verticesChanges.push_back(VertexChange(G.vertices[v]));
    DFSStepList->AddState(Step(verticesChanges,edgesChanges));
}

void DFS(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
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
    Step initStep = Step(initVerticesChanges,initEdgesChanges);
    StepListPtr->InitState(initStep);
 
    dfs_reku(GKopia, StepListPtr,chosenV[0]);

}