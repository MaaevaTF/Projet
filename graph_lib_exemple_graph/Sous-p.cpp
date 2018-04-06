#include "Sous-p.h"
#include <iostream>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "grman/grman.h"
#include "graph.h"




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
            if(mouse_b&1)
            {
                v = 1 ;
            }
        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=250 && mouse_y<=349)
        {
            blit(Reseaux,ecran,0,0,0,0,800,600); //on affiche la bitmap des réseaux
            if (mouse_b&1) //si on clique sur le bouton gauche
            {
                BITMAP* Info=load_bitmap("Info.bmp",NULL); //Chargement bitmap pour affichage des informations
                blit(Info,ecran,0,0,0,0,800,600); //Affichage du bitmap explicatif de nos réseaux
                v=2;
            }
        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=386 && mouse_y<=485)
        {
            blit(Quitter,ecran,0,0,0,0,800,600); //on affiche la bitmap pour quitter
            if(mouse_b&1)
            {
                BITMAP* Bye=load_bitmap("Bye.bmp",NULL); //Chargement bitmap pour affichage des informations
                blit(Bye,ecran,0,0,0,0,800,600); //Affichage du bitmap explicatif de nos réseaux
                v=3;
            }
        }

        blit(ecran,screen,0,0,0,0,800,600);
        //clear(ecran);

        if(v==1)
        {
            ///Chargement de chaque bitmap
            BITMAP* Eau = load_bitmap("Eau.bmp", NULL);
            BITMAP* Foret = load_bitmap("Foret.bmp", NULL);
            BITMAP* Savane = load_bitmap("Savane.bmp", NULL);
            BITMAP* Choice = load_bitmap("Choice.bmp", NULL);
            choix(ecran,Choice,Eau,Foret,Savane,Menu,Informations,Reseaux,Quitter);
        }

        if(v==2)
        {
            rest(10000); //temporisation pour pouvoir lire les infos explicatifs des réseaux
            v=0; //remettre v à zéro nous permet de rester dans le boucle
        }

        if (v==3)
        {
            rest(2000); //temporisation avant de sotir du programme
            allegro_exit(); //sortie du programme
            exit(EXIT_FAILURE);
        }

        if (mouse_b&2) //On sort de la boucle grace au clique droit
            fin = 1 ;
    }
}

void choix (BITMAP* ecran, BITMAP* Choice, BITMAP* Eau,BITMAP* Foret, BITMAP* Savane,BITMAP* Menu,BITMAP* Informations, BITMAP* Reseaux, BITMAP* Quitter) //sous-p du choix du réseau à afficher
{
    bool fin = true; //booléen pour rester dans la boucle
    int v = 0 ; //en fonction de la valeur de v, on sait quel graphe charger
    int cond ;
    while (fin) //tant qu'on est dans la boucle
    {

        blit(Choice,ecran,0,0,0,0,800,600); //on affiche le bitmap de choix du réseau
        rest(100);
        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=113 && mouse_y<=212) //en fonction de la position de la souris
        {
            blit(Eau,ecran,0,0,0,0,800,600); //on affiche le bitmap pour le cycle de l'eau
            if (mouse_b&1)
            {
                 v = 1 ; //pour retourner au choix des graphes en fonction du echap
               cond = 1 ;
            }

        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=250 && mouse_y<=349)
        {
            blit(Savane,ecran,0,0,0,0,800,600);  //on affiche le bitmap pour le réseau de la savane
            if (mouse_b&1)
            {
                 v = 1 ;
               cond = 2 ;
            }
        }

        if (mouse_x>=242 && mouse_x<=559 && mouse_y>=386 && mouse_y<=485)
        {
            blit(Foret,ecran,0,0,0,0,800,600);  //on affiche le bitmap pour les chaines alimentaires
            if (mouse_b&1)
            {
                 v = 1 ;
               cond = 3;
            }

        }

        blit(ecran,screen,0,0,0,0,800,600);

        if (v==1)
        {
           //rest(1000);
            creationgraph(cond);
            v=0 ; //on revient au choix des graphes
        }
        //clear(ecran);

        if(mouse_b&2) //si on clique droit on quitte l'application
        fin = false;

        if(key[KEY_SPACE])
        {
            menu(ecran,Menu,Informations,Reseaux,Quitter,v);
        }
    }
}

void creationgraph(int cond)
{
    std::string name;
    int eidx;
    /*
    //A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");*/

    /// Un exemple de graphe
    Graph g;
    switch(cond)
    {
        case 1 : name = "eau.txt";
        //case 1 : name = "test.txt"; //////////////////////////////////////
        break;

        case 2 : name = "savane.txt";
        break;

        case 3 : name = "foret.txt";
        break;

        default :
            break ;
    }

    g.make_example(name);


    ///Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update(); ///CEST ICI QUON SAUVEGARDE ET QUON SUPPRIME !!!!!

        if(key[KEY_RIGHT])
        {
            g.ajoutS();
        }

        if(key[KEY_LEFT])
        {
            g.ajoutA();
        }

        if(key[KEY_UP])
        {
            std::cout << "Indice du sommet à supprimer ?" << std::endl ;
            std::cin >> eidx ;
            g.deleteS(eidx);
        }




        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        sauvegarde(g,name);
    }



   // grman::fermer_allegro();
}

void sauvegarde(Graph g,string name)
{
    std::ofstream fichier(name.c_str(),std::ios::out | std::ios::trunc);
    std::string picName;
        if(fichier){
            fichier << g.m_ordre <<std::endl;
            fichier << g.m_nbr<<std::endl;
            int i=0;
            for(auto &elt : g.m_vertices){
        fichier << i <<" ";
         fichier << elt.second.m_value<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
        picName=elt.second.m_interface->m_img.get_pic_name();
        picName.erase(picName.size()-4,4);
         fichier <<picName + ".jpg"<<std::endl;
         i++;
    }
    i=0;
        for(auto &elt : g.m_edges){
            fichier << i <<" ";
            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight<<std::endl;
            i++;
        }
        i=0;
        fichier.close();
        //std::cout<<"Sauvegarde done";
        }

}

