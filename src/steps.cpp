#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "steps.hpp"
#include <iostream>

VertexChange::VertexChange(int __id, int __data1, int __data2, sf::Color __color){
    id = __id;
    data1 = __data1;
    data2 = __data2;
    color = __color;
};

VertexChange::VertexChange(Vertex &v){
    id = v.id;
    data1 = v.data1;
    data2 = v.data2;
    color = v.color;
};

VertexChange::VertexChange(){}
EdgeChange::EdgeChange(){}

EdgeChange::EdgeChange(int __id, int __weight1, int __weight2, sf::Color __color){
    id = __id;
    weight1 = __weight1;
    weight2 = __weight2;
    color = __color;
};

EdgeChange::EdgeChange(Edge &e){
    id = e.id;
    weight1 = e.weight1;
    weight2 = e.weight2;
    color = e.color;
}

Step::Step(std::vector<VertexChange> __verticesChanges, std::vector<EdgeChange> __edgesChanges){
    verticesChanges = __verticesChanges;
    edgesChanges = __edgesChanges;
}


StepList& StepList::operator=(const StepList &__stepList) 
{
    G = __stepList.G;
    forwardSteps  = std::vector<Step>(__stepList.forwardSteps); // kończy się na pustym (ew.)        
    backwardSteps = std::vector<Step>(__stepList.backwardSteps); // zaczyna się od pustego           
    currentStep = __stepList.currentStep;
    maxStepEver= __stepList.maxStepEver; 

    return *this;  
} 

StepList::StepList(Graph *ptr) {
    currentStep = -1;
    maxStepEver = 0;
    G = ptr;    
}
StepList::StepList() {}

void StepList::InitState(Step step){
    forwardSteps.push_back(step); 
}

void StepList::AddState(Step step){
    forwardSteps.push_back(step);
}
void StepList::AddBackwardsState(Step step){
    for (VertexChange &vc: step.verticesChanges) {
        vc.data1 = G->vertices[vc.id].data1;       
        vc.data2 = G->vertices[vc.id].data2;         
        vc.color = G->vertices[vc.id].color;       
        if (vc.color == sf::Color::Red)
            std::cerr<< "backstep: Red\n";

        if (vc.color == sf::Color::Green)
            std::cerr<< "backstep: Green\n";      
        if (vc.color == sf::Color::Cyan)
            std::cerr<< "backstep: Cyan\n";
    }

    for (EdgeChange &ec: step.edgesChanges) {
        ec.weight1 = G->allEdges[ec.id].weight1;
        ec.weight2 = G->allEdges[ec.id].weight2;
        ec.color   = G->allEdges[ec.id].color;
    }

    backwardSteps.push_back(step);
}
void StepList::GoLeft() {
    if(currentStep <= 0)
        return;
    currentStep--;
    for (VertexChange vc: backwardSteps[currentStep].verticesChanges){
        G->vertices[vc.id].data1 = vc.data1;
        G->vertices[vc.id].data2 = vc.data2;
        G->vertices[vc.id].color = vc.color;
    }

    for (EdgeChange ec: backwardSteps[currentStep].edgesChanges){
        G->allEdges[ec.id].weight1 = ec.weight1;
        G->allEdges[ec.id].weight2 = ec.weight2;
        G->allEdges[ec.id].color = ec.color;
    }
}

void StepList::GoRight() {
    if(currentStep + 1 >= forwardSteps.size()) //   cs = -1 0FStep cs = 0 1FStep cs=1 2FStep 3FStep 4FStep cs = 4;
        return;                                
    ++currentStep;
    if (currentStep > maxStepEver) {
        maxStepEver = currentStep;
        AddBackwardsState(forwardSteps[currentStep]);
    }   
    for (VertexChange vc: forwardSteps[currentStep].verticesChanges){
        G->vertices[vc.id].data1 = vc.data1;
        G->vertices[vc.id].data2 = vc.data2;
        G->vertices[vc.id].color = vc.color;
    }
    for (EdgeChange ec: forwardSteps[currentStep].edgesChanges){
        G->allEdges[ec.id].weight1 = ec.weight1;
        G->allEdges[ec.id].weight2 = ec.weight2;
        G->allEdges[ec.id].color = ec.color;
    }
}

void StepList::ClearStates() {
    currentStep = -1;
    maxStepEver = 0;
    forwardSteps.clear();
    backwardSteps.clear();
}