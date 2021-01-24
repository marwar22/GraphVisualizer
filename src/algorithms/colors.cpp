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
    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; 

    StepListPtr->InitState(Step(firstVerticesChanges,firstEdgesChanges));

    for (int i = 0; i < 1000; ++i) {      
        firstVerticesChanges.clear();
        firstEdgesChanges.clear(); 
        for (Vertex v: G->vertices) {
            VertexChange vChange = VertexChange(v.id, v.data1, v.data2, sf::Color((unsigned int)losColor(0,255),(unsigned int)losColor(0,255),(unsigned int)losColor(0,255),(unsigned int)255));
            firstVerticesChanges.push_back(vChange);
        }
        for (Edge e: G->allEdges) {
            EdgeChange eChange = EdgeChange(e.id, e.weight1, e.weight2, sf::Color((unsigned int)losColor(0,255),(unsigned int)losColor(0,255),(unsigned int)losColor(0,255),(unsigned int)255),e.isHighlighted);
            firstEdgesChanges.push_back(eChange);
        }
        StepListPtr->InitState(Step(firstVerticesChanges,firstEdgesChanges));
    }       
}