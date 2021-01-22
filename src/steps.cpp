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

VertexChange::VertexChange(const Vertex &v){
    id = v.id;
    data1 = v.data1;
    data2 = v.data2;
    color = v.color;
};

VertexChange::VertexChange(){}
EdgeChange::EdgeChange(){}

EdgeChange::EdgeChange(int __id, int __weight1, int __weight2, sf::Color __color, bool __isHighlighted){
    id = __id;
    weight1 = __weight1;
    weight2 = __weight2;
    color = __color;
    isHighlighted = __isHighlighted;
};

EdgeChange::EdgeChange(const Edge &e){
    id = e.id;
    weight1 = e.weight1;
    weight2 = e.weight2;
    color = e.color;
    isHighlighted = e.isHighlighted;
}

Step::Step(std::vector<VertexChange> __verticesChanges, std::vector<EdgeChange> __edgesChanges){
    verticesChanges = __verticesChanges;
    edgesChanges = __edgesChanges;
}


StepList& StepList::operator=(const StepList &__stepList) 
{
    G = __stepList.G;
    forwardSteps  = std::vector<Step>(__stepList.forwardSteps);       
    backwardSteps = std::vector<Step>(__stepList.backwardSteps);         
    currentStep = __stepList.currentStep;
    maxStepEver= __stepList.maxStepEver; 

    return *this;  
} 

StepList::StepList(Graph * const ptr) {
    currentStep = -1;
    maxStepEver = 0;
    G = ptr;    
}
StepList::StepList() {}

void StepList::InitState(Step step){
    forwardSteps.push_back(step); 
}

void StepList::AddState(Step step) {
    if (step.edgesChanges.empty() && step.verticesChanges.empty()) 
        return;
    
    forwardSteps.push_back(step);
}
void StepList::AddBackwardsState(Step step){
    for (VertexChange &vc: step.verticesChanges) {
        vc.data1 = G->vertices[vc.id].data1;       
        vc.data2 = G->vertices[vc.id].data2;         
        vc.color = G->vertices[vc.id].color;       
    }

    for (EdgeChange &ec: step.edgesChanges) {
        ec.weight1 = G->allEdges[ec.id].weight1;
        ec.weight2 = G->allEdges[ec.id].weight2;
        ec.color   = G->allEdges[ec.id].color;
        ec.isHighlighted = G->allEdges[ec.id].isHighlighted;
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
        G->allEdges[ec.id].isHighlighted = ec.isHighlighted;
    }
}

void StepList::GoRight() {
    if(currentStep + 1 >= forwardSteps.size()) 
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
        G->allEdges[ec.id].isHighlighted = ec.isHighlighted;
    }
}

void StepList::ClearStates() {
    currentStep = -1;
    maxStepEver = 0;
    forwardSteps.clear();
    backwardSteps.clear();
}