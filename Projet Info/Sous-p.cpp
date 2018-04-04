#include "Sous-p.h"
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>

///Sous-programme du menu principale
void menu (BITMAP* ecran, BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter, int v)
{

    if (v==0)
    {
        while (v==0)
        {

            blit(Menu,ecran,0,0,0,0,800,600);

            if (mouse_x>=242 && mouse_x<=559 && mouse_y>=250 && mouse_y<=349)
            {
                blit(Reseaux,ecran,0,0,0,0,800,600);
                if (mouse_b==1)
                {
                    v=1;
                    rest(300);
                }
            }

            if (mouse_x>=242 && mouse_x<=559 && mouse_y>=113 && mouse_y<=212)
            {
                blit(Informations,ecran,0,0,0,0,800,600);
                if (mouse_b==1)
                {
                    v=2;
                    rest(150);
                }
            }


            if (mouse_x>=242 && mouse_x<=559 && mouse_y>=386 && mouse_y<=485)
            {
                blit(Quitter,ecran,0,0,0,0,800,600);
                if (mouse_b==1)
                {
                    v=3;
                    rest(150);
                }
            }

            blit(ecran,screen,0,0,0,0,800,600);
            clear(ecran);
        }
        if (v==1)
        {
            BITMAP* Blanc=load_bitmap("Blanc.bmp",NULL); ///BitMap pour affichage des informations
            LireInformations(ecran,Blanc);
        }



        if (v==3)
        {
            allegro_exit();
            exit(EXIT_FAILURE);

        }
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

void LireInformations(BITMAP* ecran, BITMAP* Blanc)
{
    ecran=create_bitmap(1600,1200); //Déclaration des bitmap affichage
    blit(Blanc,ecran,0,0,0,0,800,600); //BitMap blanc sur lequel on écrit les règles
    Lirefichier("Info.txt");
}
