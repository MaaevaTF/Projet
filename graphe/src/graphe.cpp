#include "graphe.h"
#include <iostream>
#include <stdio.h>
using namespace std;

Vertex::Vertex()
{
    //cout << "333" << endl;  //test
}

Vertex::Vertex(vector<int> _in,vector<int> _out)
{
    m_in=_in;
    m_out=_out;
    //cout << "444" << endl; //test
}

Vertex::~Vertex()
{
    //dtor
}

Edge::Edge()
{
    //cout << "111" << endl;  //test
}

Edge::Edge(int _from , int _to)
{
    //cout << "222" << endl;  //test
    m_from=_from;
    m_to=_to;
}

Edge::~Edge()
{
    //dtor
}

Graphe::Graphe()
{

}

Graphe::Graphe(map<int, Edge> _edges , map<int, Vertex> _vertices)
{
    m_edges=_edges;
    m_vertices=_vertices;
    cout << m_edges[1].m_from << endl;  //test
    cout << m_vertices[0].m_in[0] << endl;  //test
}

Graphe::~Graphe()
{
    //dtor
}

void Graphe::setedge(map<int, Edge> _edges)
{
    m_edges=_edges;
}

void Graphe::setvert(map<int, Vertex> _vertices)
{
    m_vertices=_vertices;
}
