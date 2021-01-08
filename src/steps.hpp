#ifndef STEPS_HPP
#define STEPS_HPP

#include <vector>
#include "edge.hpp"
#include "vertex.hpp"
#include "graph.hpp"

struct VertexChange {
    int id;
    int data1, data2;
    sf::Color color;
    VertexChange();
    VertexChange(int, int, int, sf::Color);
    VertexChange(const Vertex &);
};
struct EdgeChange{
    int id;
    int weight1, weight2;
    sf::Color color;
    EdgeChange();
    EdgeChange(int, int, int, sf::Color);
    EdgeChange(const Edge &);
};

struct Step{    
    std::vector<VertexChange> verticesChanges;
    std::vector<EdgeChange> edgesChanges;
    Step(std::vector<VertexChange>, std::vector<EdgeChange>);
};

class StepList{
public:
    Graph *G;
    std::vector<Step> forwardSteps; // kończy się na pustym (ew.)        
    std::vector<Step> backwardSteps; // zaczyna się od pustego           
    int currentStep;
    int maxStepEver;
    void InitState(Step); 
    void AddState(Step);
    void AddBackwardsState(Step);
    void GoRight(); 
    void GoLeft();
    void ClearStates();
    StepList(Graph * const);
    StepList();
    StepList &operator =(const StepList &__stepList);

    
};
#endif