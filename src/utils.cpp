#include "graph.hpp"
#include <iostream>
#include <vector>


void PrintGraphLog(Graph &G) {
    std::cerr<<"\n---------------------------";
    std::cerr<<"WIERZCHOŁKI\n"<<std::endl;
    for (Vertex v: G.vertices){        
        std::cerr<<v.id<<"  | eIdFrom: ";
        for (int w: v.edgesIdFrom) std::cerr<<w<<" ";
        std::cerr<<"  | eIdTo: ";
        for (int w: v.edgesIdTo  ) std::cerr<<w<<" ";
        std::cerr<<"\n";
    }
    std::cerr<<"\n";
    std::cerr<<"KRAWĘDZIE\n"<<std::endl;
    for (Edge e: G.allEdges){
        std::cerr<<"id: "<<e.id<<"  from: "<<e.idVertexFrom<<"   to: "<<e.idVertexTo<<std::endl;
    }
    std::cerr<<"---------------------------\n\n";
}