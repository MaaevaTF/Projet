#ifndef SOUS-P_H_INCLUDED
#define SOUS-P_H_INCLUDED
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "graph.h"


using namespace std;

void menu (BITMAP* ecran, BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter, int v);

void choix (BITMAP* ecran,BITMAP* Choice ,BITMAP* Eau,BITMAP* Foret, BITMAP* Savanne,BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter);

void creationgraph(int cond);

void sauvegarde(Graph g,string name);


#endif // SOUS-P_H_INCLUDED
