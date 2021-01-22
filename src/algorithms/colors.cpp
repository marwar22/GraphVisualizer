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

std::mt19937 rndColor(123);
int losColor(int mi,int mx) {return rndColor()%(mx-mi+1)+mi;}

void ColorsAlgorithm(Graph *G,StepList *StepListPtr, std::vector<int> &chosenV) {  
    //StepList colorStepList = StepList(G);
    
    
    
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; 

    StepListPtr->InitState(Step(firstVerticesChanges,firstEdgesChanges));

    for (int i = 0; i < 1000; ++i) {      
        firstVerticesChanges.clear();
        for (Vertex v: G->vertices) {
            VertexChange vChange = VertexChange(v.id, 0, 0, sf::Color((uint)losColor(0,255),(uint)losColor(0,255),(uint)losColor(0,255),(uint)255));
            firstVerticesChanges.push_back(vChange);
        }
        StepListPtr->InitState(Step(firstVerticesChanges,firstEdgesChanges));
    }       
}