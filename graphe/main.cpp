#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "include\graphe.h"
#include "include\programme.h"
#include <map>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Graphe* graphe=new Graphe();

    chargement(graphe);

    //cout << "Le sommet de départ de l'arete 0 est " << graphe->m_edges[0].m_from << endl;
    //cout << "Le sommet d'arrive de l'arete 1 est " << graphe->m_edges[1].m_from << endl;
    cout << "Les aretes arrivant au sommet 0 sont : ";
    for (int i=0;i<(graphe->m_vertices[0].m_in).size();i++)
    {
        cout << graphe->m_vertices[0].m_in[i] << ", ";
    }
    cout << endl;

    return 0;
}
