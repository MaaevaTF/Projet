#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

class Vertex
{
    friend class Graph;
    friend class Edge;

    private :

        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
        //vector<int> m_in;

        /// liste des indices des arcs partant du sommet : accès aux successeurs
        //vector<int> m_out;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...

    public :

        vector<int> m_in;
        vector<int> m_out;
        Vertex();
        Vertex(vector<int>,vector<int>);
        ~Vertex();
};

class Edge
{
     friend class Graph;

     private :

        /// indice du sommet de départ de l'arc
        //int m_from;

        /// indice du sommet d'arrivée de l'arc
        //int m_to;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...

    public :

        int m_from;
        int m_to;
        Edge();
        Edge(int,int);
        ~Edge();
};

class Graphe
{

    private :

        /// La "liste" des arêtes
        //map<int, Edge> m_edges;

        /// La liste des sommets
        //map<int, Vertex> m_vertices;

    public :

        map<int, Edge> m_edges;
        map<int, Vertex> m_vertices;
        Graphe();
        Graphe(map<int, Edge>,map<int, Vertex>);
        ~Graphe();

        void setedge(map<int, Edge>);
        void setvert(map<int, Vertex>);
};
#endif // GRAPHE_H
