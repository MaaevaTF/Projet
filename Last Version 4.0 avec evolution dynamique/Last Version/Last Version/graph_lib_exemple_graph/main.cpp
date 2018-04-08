#include "grman/grman.h"
#include <iostream>

#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "Sous-p.h"
#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    ///Déclaration des bitmaps
    BITMAP* ecran=create_bitmap(1024,768); //Bitmap d'affichage
    BITMAP* Menu=load_bitmap("Menu.bmp",NULL); //Bitmaps du menu
    BITMAP* Informations=load_bitmap("Informations.bmp",NULL); //Bitmap d'accès aux informations explicatives
    BITMAP* Reseaux=load_bitmap("Reseaux.bmp",NULL); //Bitmap pour accéder à nos trois réseaux
    BITMAP* Quitter=load_bitmap("Quitter.bmp",NULL); //Bitmap pour quitter

    int fin=0; // Variable pour le menu
    menu(ecran,Menu,Reseaux,Informations,Quitter,fin);

   // grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


