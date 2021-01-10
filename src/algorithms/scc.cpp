#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include "../graph.hpp"
#include "../steps.hpp"
#include "../utils.hpp"//NIE DOTYKAC TEGO KODU

/*
Black;       
White;       
Red;         
 Green;       
Blue;        
Yellow;      
Magenta;     
Cyan;        
*/

int idx = 0;
int nr = 1;
std::vector<int> order;

void dfs_reku1(Graph &G, StepList* DFSStepList, int v) {
    G.vertices[v].data1   = 1;//visited
    G.vertices[v].data2   = idx++;//postorder
    //G.vertices[v].subText.setString("vis");
    G.vertices[v].color = sf::Color::Yellow;
    
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; // docelowo pusty

    VertexChange onlyChange = VertexChange(G.vertices[v]);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges);
    DFSStepList->AddState(firstStep);
    ////////////////////////
    for(auto id: G.vertices[v].edgesIdTo) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_reku1(G, DFSStepList, G.allEdges[id].idVertexTo);
    order.push_back(v);
}

void dfs_reku2(Graph &G, StepList* DFSStepList, int v) {
    G.vertices[v].data1   = 1;//visited
    G.vertices[v].data2   = nr;//nr skladowej
    //G.vertices[v].subText.setString("vis");

    G.vertices[v].color = sf::Color::Yellow;//kolejnny kolor DO POPRAWKI

    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; // docelowo pusty

    VertexChange onlyChange = VertexChange(G.vertices[v]);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges);
    DFSStepList->AddState(firstStep);
    ////////////////////////
    for(auto id: G.vertices[v].edgesIdFrom) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_reku2(G, DFSStepList, G.allEdges[id].idVertexTo);
}

void SCC(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
    //ZEROWANIE
    //Graph
    Graph GKopia(G);
    std::vector<VertexChange> initVerticesChanges;
    std::vector<EdgeChange> initEdgesChanges;
    for (Vertex &v: GKopia.vertices) {
        v.data1 = 0;
        v.data2 = 0;
        v.color = sf::Color::Magenta;//dlaczego
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
        v.color = sf::Color::Magenta;//dlaczego
        VertexChange singleChange = VertexChange(v);
        initVerticesChanges.push_back(singleChange);
    }
    Step nextStep = Step(initVerticesChanges,initEdgesChanges);
    StepListPtr->AddState(nextStep);
    //tutaj aktualizacje all wierzhcolkow kolory bo nowy dfs
    for(int i = order.size()-1; i >= 0; i--) {
        int v = order[i];
        if(GKopia.vertices[v].data1 == 0) {
            dfs_reku2(GKopia, StepListPtr,v);
            nr++;
        }
    }
    //return DFSStepList;
}
