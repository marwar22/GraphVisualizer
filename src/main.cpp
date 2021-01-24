#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>
#include "graph.hpp"
#include "graphics/button.hpp"
#include "app.hpp"


std::mt19937 rnd;
int los(int mi,int mx) {return rnd()%(mx-mi+1)+mi;}

int main()
{
    rnd.seed(time(NULL));
    system("mkdir -p savedGraphs");
    Application app;
    
    int n = 10, m = 0;
    for (int i = 0; i < n; ++i) app.G.AddVertex(sf::Vector2f(los(0,1600),los(0,800)));
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j) {
            int p;
            if (j-i <= 1)       p = 700;
            else if (j-i <= 2)  p = 100;
            else if (j-i <= 5)  p = 50;
            else if (j-i <= 7)  p = 30;
            else if (j-i <= 10) p = 10;
            else p = 2;
            p*=2;
            if (los(1,1000) <= p) app.G.AddEdge(i,j,los(0,10),0);
        }
    }

    int loop_x = los(0,9);
    int v = los(0,9), u = los(0,9);
    while(v == u) u = los(0,9);
    app.G.AddEdge(loop_x, loop_x,los(0,10),0);
    app.G.AddEdge(u,v,los(0,10),0);
    app.G.AddEdge(v,u,los(0,10),0);
    app.Run();
    return 0;
}
