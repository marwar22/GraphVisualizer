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

// grupa \in {1,2}
void dfs_reku_bipartial(Graph &G, StepList* DFSStepList, int v, int group,int parent) {
    G.vertices[v].data1 = group;
    
    std::vector<VertexChange> verticesChanges;
    std::vector<EdgeChange> edgesChanges; 

    if (parent != -1) {
        if (G.vertices[parent].data1 == 1)
            G.vertices[parent].color = sf::Color(0,200,0); //jasnozielony
        else 
            G.vertices[parent].color = sf::Color(255,153,0);// pomarańczowy
        
        verticesChanges.push_back(VertexChange(G.vertices[parent]));
        DFSStepList->AddState(Step(verticesChanges,edgesChanges));
        verticesChanges.clear();
    }

    if (group == 1)
        G.vertices[v].color = sf::Color(0,100,0); //zielony
    else 
        G.vertices[v].color = sf::Color(155,53,0);// ciemno-pomarańczowy

    //std::cerr<<"v: "<<v<<"\n";
    ///////////////////////
   

    verticesChanges.push_back(VertexChange(G.vertices[v]));        
    DFSStepList->AddState(Step(verticesChanges,edgesChanges));
    verticesChanges.clear();
    edgesChanges.clear();
    ////////////////////////





    /// wywołania rekurencyjne
    for(auto id: G.vertices[v].edgesIdFrom){
        if (G.allEdges[id].color != sf::Color::Black)
            continue;
        
        if (G.vertices[G.allEdges[id].idVertexFrom].data1 == 0){             
            G.allEdges[id].color = sf::Color::Green;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
            dfs_reku_bipartial(G, DFSStepList, G.allEdges[id].idVertexFrom, 3 - group,v);
        } 
        else if (G.vertices[G.allEdges[id].idVertexFrom].data1 == group) {
            G.allEdges[id].color = sf::Color::Red;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
        } 
        else {
            G.allEdges[id].color = sf::Color::Green;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
        }
        
    }
    
    for(auto id: G.vertices[v].edgesIdTo) {
        if (G.allEdges[id].color != sf::Color::Black)
            continue;

        if (G.vertices[G.allEdges[id].idVertexTo].data1 == 0) {
            G.allEdges[id].color = sf::Color::Green;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
            dfs_reku_bipartial(G, DFSStepList, G.allEdges[id].idVertexTo, 3 - group,v);
        }
        else if (G.vertices[G.allEdges[id].idVertexTo].data1 == group) {
            G.allEdges[id].color = sf::Color::Red;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
        } 
        else {
            G.allEdges[id].color = sf::Color::Green;
            edgesChanges.push_back(EdgeChange(G.allEdges[id]));
            DFSStepList->AddState(Step(verticesChanges,edgesChanges));
            edgesChanges.clear();
        }
    
    }

    if (parent != -1) {
        if (G.vertices[parent].data1 == 1)
            G.vertices[parent].color = sf::Color(0,100,0); //zielony
        else 
            G.vertices[parent].color = sf::Color(155,53,0);// ciemno-pomarańczowy
            
        verticesChanges.push_back(VertexChange(G.vertices[parent]));
        DFSStepList->AddState(Step(verticesChanges,edgesChanges));
        verticesChanges.clear();
    }
    if (group == 1)
        G.vertices[v].color = sf::Color(0,200,0); //jasno zielony
    else 
        G.vertices[v].color = sf::Color(255,153,0);// pomarańczowy

    verticesChanges.push_back(VertexChange(G.vertices[v]));
    DFSStepList->AddState(Step(verticesChanges,edgesChanges));
}

void BIPARTIAL_CHECK(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
    G->isDirected = 0;
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
 
    dfs_reku_bipartial(GKopia, StepListPtr,chosenV[0],1,-1);


}
