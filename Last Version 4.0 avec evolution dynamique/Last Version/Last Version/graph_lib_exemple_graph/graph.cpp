#include "graph.h"
#include <fstream>
#include <stack>
#include "allegro.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}

/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}

/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}

/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}

/***************************************************
                    GRAPH
****************************************************/

GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///Creation boutons
    m_tool_box.add_child(m_supprimer);
    m_supprimer.add_child(m_supprimertxt);
    m_supprimer.set_dim(80,80);
    m_supprimer.set_posx(0);
    m_supprimer.set_posy(300);
    m_supprimer.set_bg_color(CYANSOMBRE);
    m_supprimertxt.set_message(" SUPPRIMER ");

    m_tool_box.add_child(m_sauvegarder);
    m_sauvegarder.add_child(m_sauvegardertxt);
    m_sauvegarder.set_dim(80,80);
    m_sauvegarder.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_sauvegarder.set_bg_color(CYANSOMBRE);
    m_sauvegardertxt.set_message(" SAUVEGARDER ");

    m_tool_box.add_child(m_ajouterS);
    m_ajouterS.add_child(m_ajouterStxt);
    m_ajouterS.set_dim(80,80);
    m_ajouterS.set_posx(0);
    m_ajouterS.set_posy(100);
    m_ajouterS.set_bg_color(CYANSOMBRE);
    m_ajouterStxt.set_message("AJOUT SOMMET");

    m_tool_box.add_child(m_ajouterA);
    m_ajouterA.add_child(m_ajouterAtxt);
    m_ajouterA.set_dim(80,80);
    m_ajouterA.set_posx(0);
    m_ajouterA.set_posy(200);
    m_ajouterA.set_bg_color(CYANSOMBRE);
    m_ajouterAtxt.set_message("AJOUT ARC");

    m_tool_box.add_child(m_connexe);
    m_connexe.add_child(m_connexetxt);
    m_connexe.set_dim(80,80);
    m_connexe.set_posx(0);
    m_connexe.set_posy(400);
    m_connexe.set_bg_color(CYANSOMBRE);
    m_connexetxt.set_message("CONNEXITE");

    m_tool_box.add_child(m_clavier);
    m_clavier.add_child(m_claviertxt);
    m_clavier.set_dim(80,80);
    m_clavier.set_posx(0);
    m_clavier.set_posy(500);
    m_clavier.set_bg_color(CYANSOMBRE);
    m_claviertxt.set_message("CLAVIER");

    m_tool_box.add_child(m_quitter);
    m_quitter.add_child(m_quittertxt);
    m_quitter.set_dim(80,80);
    m_quitter.set_posx(0);
    m_quitter.set_posy(600);
    m_quitter.set_bg_color(CYANSOMBRE);
    m_quittertxt.set_message("QUITTER");

}

void Graph::make_example(std::string name)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    std::ifstream fichier(name.c_str());

    int k,m,n,q,r,s;
    double l,t;
    std::string o;
    int so,a,b;

    if(fichier)
    {
        fichier >> so;
        fichier >> a;
        m_ordre=so;
        m_nbr=a;
        b = a + so;
        for(int i=0; i<b; i++)
        {
            if(i<so)
            {
                fichier >> k;
                fichier >> l;
                fichier >> m;
                fichier >> n;
                fichier >> o;

                add_interfaced_vertex(k, l, m, n, o);
            }
            else
            {
                fichier >> q;
                fichier >> r;
                fichier >> s;
                fichier >> t;

                add_interfaced_edge(q, r, s, t);
            }
        }
    }

    fichier.close();


}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    // Graph g ;
    // std::string name ;
    int eidx ;
    if(m_interface->m_supprimer.clicked())
        deleteS(eidx);
    if(m_interface->m_sauvegarder.clicked())
         std::cout << "Graphe sauvegarde !" << std::endl ;
         //sauvegarde(g, name);
    if(m_interface->m_ajouterS.clicked())
        ajoutS();
    if(m_interface->m_ajouterA.clicked())
        ajoutA();
    if(m_interface->m_connexe.clicked())
        connexite();

    if(m_interface->m_clavier.clicked())
        afficherClavier();

    if(m_interface->m_quitter.clicked())
        afficherBye();
       // EvolutionDynamique();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

///Sous-p d'affichage de nos bitmap
void Graph::afficherBye()
{
    BITMAP* ecran=create_bitmap(1024,768);
    BITMAP* Bye = load_bitmap("Bye.bmp",NULL);
    clear_bitmap(ecran);
    while(!key[KEY_ESC])
    {
        blit(Bye, ecran, 0, 0,0,0, 1024, 768);
        blit(ecran,screen,0,0,0,0,1024,768);
        rest(2000);
        allegro_exit(); //sortie du programme
        exit(EXIT_FAILURE);
    }

}

void Graph::afficherClavier()
{
    BITMAP* ecran=create_bitmap(1024,768);
    BITMAP* Clavier = load_bitmap("Clavier.bmp", NULL);
    clear_bitmap(ecran);
    while(!key[KEY_DOWN])
    {
        blit(Clavier, ecran, 0, 0,0,0, 1024,768);
        blit(ecran,screen,0,0,0,0,1024,768);
    }
}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

/// eidx index of edge to remove
void Graph::test_remove_edge(int eidx)
{
    /// r�f�rence vers le Edge � enlever
    Edge &remed=m_edges.at(eidx);

    /// test : on a bien des �l�ments interfac�s
    if (m_interface && remed.m_interface)
    {
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    m_edges.erase( eidx );

    m_nbr--;

}

void Graph::ajoutS()
{
    std::string img;
    int a;
    std::cout << "Nom du sommet a ajouter : " << std::endl;
    std::cin >> img;
    a = m_vertices.size();
    add_interfaced_vertex(a,0,0,0,img,a);
    m_ordre++;
}

void Graph::ajoutA()
{
    int dep;
    int ar;
    int a;
    std::cout << "Indice du sommet de depart : " << std::endl;
    std::cin >> dep;
    std::cout << "Indice du sommet d'arrive : " << std::endl;
    std::cin >> ar;
    a = m_edges.size();
    add_interfaced_edge(a,dep,ar,50);
    m_nbr++;
}

void Graph::deleteS(int eidx)
{
    int num ;
    std::cout << "Indice du sommet � supprimer ?" << std::endl ;
    std::cin >> eidx ;
    for(int i(0); i<m_vertices[eidx].m_in.size(); i++)
    {
        std::cout << std::endl << m_vertices[eidx].m_in[i] << std::endl;
    }
    for(int i(0); i<m_vertices[eidx].m_out.size(); i++)
    {
        std::cout << std::endl << m_vertices[eidx].m_out[i] << std::endl;
    }

    for(int i = 0; i<m_vertices.find(eidx)->second.m_out.size(); ++i)
    {
        test_remove_edge(m_vertices.find(eidx)->second.m_out[i]);
    }
    for(int i = 0; i<m_vertices.find(eidx)->second.m_in.size(); ++i)
    {
        test_remove_edge(m_vertices.find(eidx)->second.m_in[i]);
    }
    Vertex &remed=m_vertices.at(eidx);
    for(auto& elem : m_vertices)
    {
        m_vertices.find(eidx)->second.m_out.size();
        if (m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );
        }
        //m_ordre--;
    }
    m_ordre--;
    m_vertices.erase(eidx);
}

void Graph::sauvegarde(Graph g,std::string name)
{
    std::ofstream fichier(name.c_str(),std::ios::out | std::ios::trunc);
    std::string picName;
    if(fichier)
    {
        fichier << g.m_ordre <<std::endl;
        fichier << g.m_nbr<<std::endl;
        int i=0;
        for(auto &elt : g.m_vertices)
        {
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
        for(auto &elt : g.m_edges)
        {
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

///Sous-programme pour les connexit�s
void Graph::connexite()
{
    ///D�clarations des variables
    std::vector<Vertex> Copy ; //on cr�e un vecteur copie dans le lequel on va met les sommets adjacents appartenant � la composante connexe
    std::stack<int> pile; //on cr�er notre pile qui symbolise les composantes connexes
    int m = 0, i = 0, a;
    std::vector<bool> SommetMarques; //bool�en permettant de savoir si on a deja tester un sommet
    std::vector<std::vector<int>> SommetAdjacent; //vecteur de vecteur d'entier

    for(auto& elem : m_vertices) //boucle parcourant la liste des sommets
        Copy.push_back(elem.second); //on ajoute les indices des sommets au vecteur appel� copie


    for(auto& elem : Copy) //boucle parcourant le vecteur copie
    {
        SommetMarques.push_back(false);
        SommetAdjacent.push_back(std::vector<int>());

        for(auto& elem1 : elem.m_in)
            SommetAdjacent.back().push_back(m_edges.at(elem1).m_from);

        for(auto& elem2 : elem.m_out)
            SommetAdjacent.back().push_back(m_edges.at(elem2).m_to);
    }

    SommetMarques[m] = true; //On marque un sommet donc le bol�an prd la valeur vraie
    pile.push(m); //on ajoute ce sommet � la pile (composante connexe)

    while(i < Copy.size()) //tant qu'on a pas fini de parcourir le vecteur copie
    {
        std::cout << "Les composantes connexes sont :" << std::endl;
        while(!pile.empty()) //tant que la pile n'est pas vide
        {
            m=pile.top(); //le premier sommet marqu� se trouve en haut de la pile
            pile.pop(); //on ajoute des sommets dans la pile

            for (a=0; a<SommetAdjacent[m].size(); ++a)
            {
                if (!SommetMarques.at(SommetAdjacent[m][a])) //si le sommet marqu� n'est pas adjacent � un certain sommet
                {
                    SommetMarques[SommetAdjacent[m][a]] = true;
                    pile.push(SommetAdjacent[m][a]); //on ajoute celui si � la pile donc � la composante connexe
                }
            }
            std::cout << m << std::endl; //on affiche l'indice des sommets de la composante connexe
        }

        i = 0; //on r�initialise i � zero
        while(i < Copy.size() && SommetMarques[i]) //tant que i est inf�rieur � la taille du vecteur copie et au nb de sommest marqu�s
            i++; //i est incr�ment�

        if(SommetMarques[i]) //si on retombe sur un sommet sur lequel on est deja pass�
            break; //alors la composante est finie

        else
        {
            SommetMarques[i] = true;
            pile.push(i); //sinon celui-ci est ajout� � la composante
        }
    }
}

///Sous-programme d'�volution dynamique
void Graph::EvolutionDynamique()
{
    double K = 0 ;

    for(int h = 0 ;h<m_vertices[h].m_in.size(); h++)
    {
        for(int j = 0; j<m_edges.size() ; j++)
        {
            for(int i=0 ; i < m_edges.size() ; i++)
            {
                if(m_vertices[h].m_in[j])
                    {
                        K+= m_edges[i].m_weight*m_vertices[m_edges[i].m_from].m_value/200;
                        std::cout << K << std::endl  ;
                    }
            }
        }

        if(K!=0)
        {
            m_vertices[h].m_value = m_vertices[h].m_value + 0.005*m_vertices[h].m_value*(1-m_vertices[h].m_value/K);
            std::cout <<m_vertices[h].m_value << std::endl ;
        }
        if(m_vertices[h].m_value<0)
            m_vertices[h].m_value = 0 ;
    }
}
