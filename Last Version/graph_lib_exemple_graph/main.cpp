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
    /*Initialisation d'Allegro
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
    show_mouse(screen);*/


    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    ///Déclaration des bitmaps
    BITMAP* ecran=create_bitmap(1600,1200); //Bitmap d'affichage
    BITMAP* Menu=load_bitmap("Menu.bmp",NULL); //Bitmaps du menu
    BITMAP* Informations=load_bitmap("Informations.bmp",NULL); //Bitmap d'accès aux informations explicatives
    BITMAP* Reseaux=load_bitmap("Reseaux.bmp",NULL); //Bitmap pour accéder à nos trois réseaux
    BITMAP* Quitter=load_bitmap("Quitter.bmp",NULL); //Bitmap pour quitter

    int fin=0; // Variable pour le menu
    menu(ecran,Menu,Reseaux,Informations,Quitter,fin);


    /* Un exemple de graphe
    Graph g;
    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();*/

    return 0;
}
END_OF_MAIN();


