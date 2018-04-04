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

void writeFile(const std::string& path,std::vector<std::string>::iterator it);

void Lirefichier(const std::string& path);

void LireInformations(BITMAP* ecran, BITMAP* Blanc);


#endif // SOUS-P_H_INCLUDED
