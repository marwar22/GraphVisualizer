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

void ColorsAlgorithm(Graph *G,StepList *StepListPtr, std::vector<int> &chosenV) {  
    //StepList colorStepList = StepList(G);

    std::vector<VertexChange> firstVerticesChanges;
    std::vector<EdgeChange> firstEdgesChanges; // docelowo pusty

    VertexChange onlyChange = VertexChange(0, 100, 100, sf::Color::Green);
    firstVerticesChanges.push_back(onlyChange);
    Step firstStep = Step(firstVerticesChanges,firstEdgesChanges); 

    StepListPtr->InitState(firstStep);
    //onlyChange.color = 
    //G->vertices[0].color = sf::Color::Cyan;
    firstVerticesChanges[0].color = sf::Color::Cyan;
    Step secondStep = Step(firstVerticesChanges,firstEdgesChanges); 
    StepListPtr->AddState(secondStep);
    //return colorStepList;
}

/*
    vector<FunkcjaAlgorytmy> algorithms;
    listaKrokow = ColorsAlgorithms(nasz_graf_z_ekranu)


*/


