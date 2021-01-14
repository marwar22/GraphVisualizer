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

int GLOBAL_POSTORDER_COUNTER = 0;

void dfs_postorder(Graph &G, StepList* POSTStepList, int v) {
    G.vertices[v].data1 = 1;
    G.vertices[v].color = sf::Color(41, 230, 230);

    ///////////////////////
    std::vector<VertexChange> verticesChanges;
    std::vector<EdgeChange> edgesChanges; // docelowo pusty

    verticesChanges.push_back(VertexChange(G.vertices[v]));
    POSTStepList->AddState(Step(verticesChanges,edgesChanges));
    verticesChanges.clear();
    edgesChanges.clear();
    ////////////////////////
    if(G.isDirected == 0) {
        for(auto id: G.vertices[v].edgesIdFrom){ 
            if(G.vertices[G.allEdges[id].idVertexFrom].data1 == 0) 
                dfs_postorder(G, POSTStepList, G.allEdges[id].idVertexFrom);
        }
    }
    for(auto id: G.vertices[v].edgesIdTo) 
        if(G.vertices[G.allEdges[id].idVertexTo].data1 == 0) 
            dfs_postorder(G, POSTStepList, G.allEdges[id].idVertexTo);

    G.vertices[v].color = sf::Color(36, 158, 115);
    GLOBAL_POSTORDER_COUNTER += 1;
    G.vertices[v].data2 = GLOBAL_POSTORDER_COUNTER;
    verticesChanges.push_back(VertexChange(G.vertices[v]));
    POSTStepList->AddState(Step(verticesChanges,edgesChanges));
}

void POSTORDER(Graph *G,StepList *StepListPtr, std::vector<int>  &chosenV) {  
    GLOBAL_POSTORDER_COUNTER = 0;
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
 
    dfs_postorder(GKopia, StepListPtr,chosenV[0]);

}



