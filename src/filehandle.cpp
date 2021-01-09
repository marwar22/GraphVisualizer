#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "vertex.hpp"
#include "edge.hpp"
#include "graph.hpp"
void WriteBool( bool b, std::ofstream* ff )
{
    char c;
    if (b)
        c = 127;
    else
        c = -128;
    ff->write((const char*)&c, sizeof c);
}
bool ReadBool(std::ifstream* ff)
{
    char c;
    ff->read((char*)&c, sizeof c);
    return c >= 0;
}
void WriteChar(char c, std::ofstream* ff)
{
    ff->write((const char*)&c, sizeof c);
}
char ReadChar(std::ifstream* ff)
{
    char c;
    ff->read((char*)&c, sizeof c);
    return c;
}
void WriteInt(int n, std::ofstream* ff)
{
    int r;
    char c;
    bool z = true;
    if (n < 0) {
        z = false;
        n = -n;
    }
    WriteBool(z, ff);
    for (int i = 0; i < 4; i++)
    {
        r = n % 256;
        if (r > 127)
            r -= 256;
        c = r;
        n /= 256;
        WriteChar(c, ff);
    }
}
int ReadInt(std::ifstream* ff)
{
    int r, n = 0;
    char c;
    bool z = ReadBool(ff);
    for (int i = 0; i < 4; i++)
    {
        c = ReadChar(ff);
        r = c;
        if (r < 0)
            r += 256;
        for (int j = 0; j < i; j++)
            r *= 256;
        n += r;
    }
    return z ? n : -n;
}
void ReadFile( const char * name, Graph * G )
{
    G->vertices.clear();
    G->allEdges.clear();
    float itf;
    int vs, es, fr, to, w1, w2, mdpx, mdpy;
    sf::Vector2f tmp;
    std::ifstream ff(name, std::ios::binary | std::ios::in);
    G->isDirected = ReadBool(&ff);
    G->isWeighted = ReadBool(&ff);
    vs = ReadInt(&ff);
    for (int i = 0; i < vs; i++) {
        itf = ReadInt(&ff);
        tmp.x = itf;
        itf = ReadInt(&ff);
        tmp.y = itf;
        G->AddVertex(tmp);
    }
    es = ReadInt(&ff);
    for (int i = 0; i < es; i++) {
        fr = ReadInt(&ff);
        to = ReadInt(&ff);
        w1 = ReadInt(&ff);
        w2 = ReadInt(&ff);
        mdpx = ReadInt(&ff);
        mdpy = ReadInt(&ff);
        G->AddEdge(fr, to, w1, w2);
    }
}
void WriteFile(const char* name, Graph* G)
{
    int fti;
    std::ofstream ff(name, std::ios::binary | std::ios::trunc | std::ios::out);
    WriteBool(G->isDirected, &ff);
    WriteBool(G->isWeighted, &ff);
    WriteInt(G->vertices.size(), &ff);
    for (int i = 0; i < G->vertices.size(); i++){
        fti = G->vertices[i].position.x;
        WriteInt(fti, &ff);
        fti = G->vertices[i].position.y;
        WriteInt(fti, &ff);
    }
    WriteInt(G->allEdges.size(), &ff);
    for (int i = 0; i < G->allEdges.size(); i++) {
        WriteInt(G->allEdges[i].idVertexFrom, &ff);
        WriteInt(G->allEdges[i].idVertexTo, &ff);
        WriteInt(G->allEdges[i].weight1, &ff);
        WriteInt(G->allEdges[i].weight2, &ff);
        WriteInt(G->allEdges[i].midEdgePosition.x, &ff);
        WriteInt(G->allEdges[i].midEdgePosition.y, &ff);
    }
}