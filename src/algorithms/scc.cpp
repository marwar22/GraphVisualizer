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

int idx = 0;
int nr = 1;
std::vector<int> order;

std::map<int,sf::Color> mapa={
    {0,sf::Color::Black},
    {1,sf::Color::Magenta},
    {2,sf::Color::Red},
    {3,sf::Color((uint)204,(uint)102,(uint)0,(uint)255)},
    {4,sf::Color((uint)153,(uint)0,(uint)0,(uint)255)},
    {5,sf::Color((uint)0,(uint)102,(uint)102,(uint)255)}
};
int num = mapa.size();
int cdx;

void dfs_reku1(Graph &G, StepList* DFSStepList, int v) {
    G.vertices[v].data1   = 1;
    G.vertices[v].color = sf::Color::Yellow;
    
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; 
    VertexChange onlyChange = VertexChange(G.vertices[v]);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges);
    DFSStepList->AddState(firstStep);

    for(auto id: G.vertices[v].edgesIdTo) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_reku1(G, DFSStepList, G.allEdges[id].idVertexTo);
    
    G.vertices[v].data2   = idx++;
    G.vertices[v].color   = sf::Color::Cyan;
    VertexChange onlyChange2 = VertexChange(G.vertices[v]);
    std::vector<VertexChange> secondVerticesChanges;
    std::vector<EdgeChange> secondEdgesChanges; 
    secondVerticesChanges.push_back(onlyChange2);
    Step secondStep = Step(secondVerticesChanges,secondEdgesChanges);
    DFSStepList->AddState(secondStep);
    order.push_back(v);
}

void dfs_reku2(Graph &G, StepList* DFSStepList, int v) {
    G.vertices[v].data1   = 1;
    G.vertices[v].data2   = nr;
  
    G.vertices[v].color = mapa[cdx];
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges;

    VertexChange onlyChange = VertexChange(G.vertices[v]);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges);
    DFSStepList->AddState(firstStep);

    for(auto id: G.vertices[v].edgesIdFrom) 
        if(G.vertices[G.allEdges[id].idVertexFrom].data1 == 0) 
            dfs_reku2(G, DFSStepList, G.allEdges[id].idVertexFrom);
}

void SCC(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
    nr = 1;
    idx = 0; 
    cdx = 0;
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
    initVerticesChanges.clear();
    for(Vertex &v: GKopia.vertices)
        if(v.data1 == 0)
            dfs_reku1(GKopia, StepListPtr,v.id);
    for (Vertex &v: GKopia.vertices) {
        v.data1 = 0;
        v.data2 = 0;
        v.color = sf::Color::Magenta;
        VertexChange singleChange = VertexChange(v);
        initVerticesChanges.push_back(singleChange);
    }
    Step nextStep = Step(initVerticesChanges,initEdgesChanges);
    StepListPtr->AddState(nextStep);
    
    for(int i = order.size()-1; i >= 0; i--) {
        int v = order[i];
        if(GKopia.vertices[v].data1 == 0) {
            dfs_reku2(GKopia, StepListPtr,v);
            nr++;
            cdx = (cdx + 1) % num;
        }
    }
    order.clear();
}
