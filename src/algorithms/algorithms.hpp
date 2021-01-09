#include "../steps.hpp"
#include "../graph.hpp"
void ColorsAlgorithm(Graph *G,StepList * stepList, std::vector<int> &chosenV);
void DFS(Graph *G,StepList* stepList, std::vector<int> &chosenV);
void BFS(Graph *G,StepList* stepList, std::vector<int> &chosenV);
void DIJKSTRA(Graph *G,StepList* stepList, std::vector<int> &chosenV);
void SCC(Graph *G,StepList* stepList, std::vector<int> &chosenV);