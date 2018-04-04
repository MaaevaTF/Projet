#include "Sous-p.h"
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>


///Sous-programme du menu principale
void menu (BITMAP* ecran, BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter, int fin)
{

    fin = 0; // variable de la boucle
    int v = 0 ; //valeur utilisée pour temporisation
    while (!fin && v==0) //tant qu'on est dans la boucle intérative
    {
        blit(Menu,ecran,0,0,0,0,800,600); //on affiche le menu qui est l'écran principale

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=113 && mouse_y<=212) //si la souris se trouvent dans cette zone
        {
            blit(Informations,ecran,0,0,0,0,800,600); //on affiche la bitmap des infos
        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=250 && mouse_y<=349)
        {
            blit(Reseaux,ecran,0,0,0,0,800,600); //on affiche la bitmap des réseaux
            if (mouse_b&1) //si on clique sur le bouton gauche
            {
                BITMAP* Info=load_bitmap("Info.bmp",NULL); //Chargement bitmap pour affichage des informations
                blit(Info,ecran,0,0,0,0,800,600); //Affichage du bitmap explicatif de nos réseaux
                v=1;
            }
        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=386 && mouse_y<=485)
        {
            blit(Quitter,ecran,0,0,0,0,800,600); //on affiche la bitmap pour quitter
            if(mouse_b&1)
            {
                BITMAP* Bye=load_bitmap("Bye.bmp",NULL); //Chargement bitmap pour affichage des informations
                blit(Bye,ecran,0,0,0,0,800,600); //Affichage du bitmap explicatif de nos réseaux
                v=2;
            }
        }

      //  blit(ecran,screen,0,0,0,0,800,600);
        //clear(ecran);

        if(v==1)
        {
            rest(10000);
            v=0;
        }

        if (v==2)
        {
            rest(2000); //temporisation avant de sotir du programme
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        if (mouse_b&2) //On sort de la boucle
            fin = 1 ;
    }
}

///Sous-programme relatifs au fichier
void writeFile(const std::string& path,std::vector<std::string>::iterator it)
{
    // Ouverture fichier en mode "w"
    // pour le mode append, utiliser std::ios::app
    std::ofstream ofs(path.c_str(), std::ios::app);
    if (ofs)
    {
        // Ecriture dans le fichier
        ofs << *it << std::endl;
        ofs.close(); // fermeture du flux
    }
}

void Lirefichier(const std::string& path)
{
    std::ifstream ifs(path.c_str());
    if (ifs) // test si le fichier est bien ouvert
    {
        std::string line;
        while (std::getline(ifs, line)) // lecture ligne par ligne
        {

            std::cout << line << std::endl;
        }
        std::cout << "Reading " << path << " => OK" << std::endl;
        ifs.close(); // fermeture du flux
    }
    else // en cas d'erreur...
    {
        std::cout << "Cannot read " << path << std::endl;
    }
}

