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

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    ///D�claration des bitmaps
    BITMAP* ecran=create_bitmap(1024,768); //Bitmap d'affichage
    BITMAP* Menu=load_bitmap("Menu.bmp",NULL); //Bitmaps du menu
    BITMAP* Informations=load_bitmap("Informations.bmp",NULL); //Bitmap d'acc�s aux informations explicatives
    BITMAP* Reseaux=load_bitmap("Reseaux.bmp",NULL); //Bitmap pour acc�der � nos trois r�seaux
    BITMAP* Quitter=load_bitmap("Quitter.bmp",NULL); //Bitmap pour quitter

    int fin=0; // Variable pour le menu
    menu(ecran,Menu,Reseaux,Informations,Quitter,fin);

   // grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


