#ifndef SOUS-P_H_INCLUDED
#define SOUS-P_H_INCLUDED
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>


using namespace std;

void menu (BITMAP* ecran, BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter, int v);

void choix (BITMAP* ecran,BITMAP* Choice ,BITMAP* Eau,BITMAP* Foret, BITMAP* Savanne);

void creationgraph(int cond);


#endif // SOUS-P_H_INCLUDED
