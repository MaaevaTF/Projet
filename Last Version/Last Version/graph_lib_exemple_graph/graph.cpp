#include "graph.h"
#include <fstream>
#include "stack"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
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

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
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
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
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

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
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
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge);  */
        /* m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );


    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

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
    for(int i(0);i<m_vertices[eidx].m_in.size();i++)
    {
        std::cout << std::endl << m_vertices[eidx].m_in[i] << std::endl;
    }
    for(int i(0);i<m_vertices[eidx].m_out.size();i++)
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

bool Graph::connexe()
{
    if(m_vertices.empty()) return false;

    std::vector<Vertex> copie;
    std::stack<int> pile;
    int s = 0;
    unsigned i = 0;
    std::vector<bool> marques;
    std::vector<std::vector<int>> adjacent;
    bool tmp(false);

    for(auto it : m_vertices)
    {
        copie.push_back(it.second);
        for(auto it2 : it.second.m_out)
            std::cout << it2 << " ";
    }

    for(auto it : copie)
    {
        marques.push_back(false);
        adjacent.push_back(std::vector<int>());
        tmp = false;
        for(auto it2 : it.m_in)
        {
            adjacent.back().push_back(m_edges.at(it2).m_from);
        }

        for(auto it2 : it.m_out)
        {
//            if(!adjacent.empty())
//            {
//                for(auto it3 : adjacent.back())
//                {
//                    bool k = m_edges.at(it3).m_from == m_edges.at(it2).m_from;
//                    if( (m_edges.at(it3).m_from == m_edges.at(it2).m_from && m_edges.at(it3).m_to == m_edges.at(it2).m_to) ||
//                       (m_edges.at(it3).m_from == m_edges.at(it2).m_to && m_edges.at(it3).m_to == m_edges.at(it2).m_from) )
//                    {
//                        tmp = true;
//                    }
//                }
//            }
//            if(!tmp)
                adjacent.back().push_back(m_edges.at(it2).m_to);
        }
    }

    for(auto it : adjacent)
    {
        for(auto it2 : it)
        {
            std::cout << it2 << " ";
        }
        std::cout << std::endl;
    }

    marques[s] = true;
    pile.push(s);

    while(i < copie.size())
    {
        std::cout << "Composantes connexes :" << std::endl;
        while(!pile.empty())
        {
            s=pile.top();
            pile.pop();

            for (unsigned a=0; a<adjacent[s].size(); ++a)
            {
                if (!marques.at(adjacent[s][a]))
                {
                    marques[adjacent[s][a]] = true;
                    pile.push(adjacent[s][a]);
                }
            }
            std::cout << s << std::endl;
        }
        std::cout << std::endl;

        i = 0;
        while(i < copie.size() && marques[i])
        {
            i++;
        }

        if(marques[i])
        {
            break;
        }
        else
        {
            marques[i] = true;
            pile.push(i);
        }
    }
    return false;
}



