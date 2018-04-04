#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "Sous-p.h"



using namespace std;

int main()
{
    ///Initialisation d'Allegro
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    ///Déclaration des bitmaps
    BITMAP* ecran=create_bitmap(1600,1200); //Bitmap d'affichage
    BITMAP* Menu=load_bitmap("Menu.bmp",NULL); //Bitmaps du menu
    BITMAP* Informations=load_bitmap("Informations.bmp",NULL); //Bitmap d'accès aux informations explicatives
    BITMAP* Reseaux=load_bitmap("Reseaux.bmp",NULL); //Bitmap pour accéder à nos trois réseaux
    BITMAP* Quitter=load_bitmap("Quitter.bmp",NULL); //Bitmap pour quitter

    int fin=0; // Variable pour le menu
    menu(ecran,Menu,Reseaux,Informations,Quitter,fin);

    return 0;
}
END_OF_MAIN();
