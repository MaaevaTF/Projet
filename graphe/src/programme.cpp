#include "programme.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


void chargement(Graphe* graphe)
{
    vector<int> v1;
    vector<int> v2;
    vector<int> tab;
    int word;
    int i;
    int indice;
    map <int, Vertex> ver1;
    map <int, Edge> edg1;

    ifstream fichier("savane.txt", ios::in);  //ouvre en lecture
    if(fichier)
    {
        while (fichier >> word && word!=999)
        {
            while (fichier >> word && word!=666)
            {
                v1.push_back(word);
            }
            while (fichier >> word && word!=666)
            {
                v2.push_back(word);
            }
            while (fichier >> word && word!=666)
            {
                indice=word;
            }
            cout << "Sommet : " << endl;
            for(int i=0; i<v1.size(); i++)
            {
                cout << "v1 : ";
                cout << v1[i] << endl;
            }

            for(int i=0; i<v2.size(); i++)
            {
                cout << "v2 : ";
                cout << v2[i] << endl;
            }

            cout << "Indice : " << indice << endl;

            cout << endl;

            ver1[indice] = Vertex(v1,v2);
            cout << "etape1" << endl;

            for(int i=v1.size(); i>0; i--)
            {
                v1.pop_back();
            }
            //cout << "taille : " << v1.size() << endl;   //test

            for(int i=v2.size(); i>0; i--)
            {
                v2.pop_back();
            }
            //cout << "taille : " << v2.size() << endl;   //test
        }

        while (fichier >> word && word!=333)
        {
            while (fichier >> word && word!=666)
            {
                tab.push_back(word);
            }
            cout << endl << "Aretes : " << endl;
            cout << "Depart : " << tab[0] << endl;
            cout << "Arrive : " << tab[1] << endl;
            cout << "Indice : " << tab[2] << endl;
            cout << endl;

            edg1[tab[2]] = Edge(tab[0],tab[1]);
            cout << "etape2" << endl;

            tab.pop_back();
            tab.pop_back();
            tab.pop_back();
        }

        fichier.close();
    }

    graphe->setedge(edg1);
    graphe->setvert(ver1);
}
