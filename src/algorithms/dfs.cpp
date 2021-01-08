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
    G.vertices[v].data1   = 1;
    G.vertices[v].subText.setString("vis");
    G.vertices[v].color = sf::Color::Yellow;
    std::cerr<<"v: "<<v<<"\n";
    ///////////////////////
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; // docelowo pusty

    VertexChange onlyChange = VertexChange(G.vertices[v]);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges);
    DFSStepList->AddState(firstStep);
    ////////////////////////
    if(G.isDirected == 0) 
        for(auto id: G.vertices[v].edgesIdFrom) 
            if(G.vertices[G.allEdges[id].idVertexFrom].data1 == 0) 
                dfs_reku(G, DFSStepList, G.allEdges[id].idVertexFrom);
            

    for(auto id: G.vertices[v].edgesIdTo) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_reku(G, DFSStepList, G.allEdges[id].idVertexTo);
    
    //G->vertices[v].data1   = 1;
    //G->vertices[v].subText = "Prerobiony";
}

void DFS(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
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
    //StepList DFSStepList(&GKopia);
    //*DFSStepList = StepList(G);
    dfs_reku(GKopia, StepListPtr,chosenV[0]);
    //return DFSStepList;
}

/*
    vector<FunkcjaAlgorytmy> algorithms;
    listaKrokow = ColorsAlgorithms(nasz_graf_z_ekranu)


*/


