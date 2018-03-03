#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <map>
#include <list>

#include <glm/geometric.hpp>
#include <eigen3/Eigen/Eigenvalues>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include <pcl/point_cloud.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <vector>

#include "vertex.h"
#include "face.h"
#include "tangentPlane.h"

// Definitions pour le Minimum Spanning Tree
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
            boost::no_property, boost::property<boost::edge_weight_t, float>> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor GEdge;
typedef boost::graph_traits<Graph>::vertex_descriptor GVertex;
typedef std::pair<int, int> GE;

/**
 * @brief Representation d'un maillage par un ensemble de faces et un ensemble de
 *        sommets mis en relation par des demi-aretes
 */
class Mesh
{
private: /// Donnees privees
    /**
     * @brief Ensemble des sommets indexes par leur identifiant unique
     */
    std::map<int, Vertex*> _vertices;

    /**
     * @brief Ensemble de plans tangents pour approximer la surface en chaque sommet
     */
    std::map<int, TangentPlane*> _tan_planes;

    /**
     * @brief Ensemble des faces indexees par leur identifiant unique
     */
    std::map<int, Face*> _faces;

public: /// Constructeurs
    /**
     * @brief Constructeur par defaut, initialise un objet vide
     */
    Mesh();

    /**
     * @brief Destructeur, libere la memoire allouee pour les sommets et les faces
     *        (libere indirectement la memoire allouee pour les demi-aretes, voir
     *        le destructeur de la classe Face)
     */
    ~Mesh();

private: /// Methodes privees de creation du mesh
    /**
     * @brief Ajoute un nouveau sommet au maillage
     * @param x Coordonnee en X
     * @param y Coordonnee en Y
     * @param z Coordonnee en Z
     * @return Retourne l'identifiant du sommet construit si succes, -1 sinon
     */
    int _add_vertex(float x, float y, float z);

    /**
     * @brief Ajoute une nouvelle face au maillage
     * @param n Nombre de sommets de la face
     * @param indices Tableau des indices des sommets
     * @param links Map des demi-aretes indexees par leur source ET leur destination
     *        (voir Mesh::_link_halfedges), modifiee par effet de bord
     * @return Retourne l'identifiant de la face construite si succes, -1 sinon
     */
    int _add_face(int n, const int* indices,
                  std::map<std::pair<int, int>, HalfEdge*>& links);

    /**
     * @brief Complete la representation Half-Edge en attribuant une demi-arete
     *        incidente a chaque sommet et en attribuant a chaque demi-arete la
     *        demi-arete tete-beche correspondante
     * @param links Map des demi-aretes indexees par leur source et leur destination,
     *        permettant de completer la representation en un temps logarithmique par
     *        nombre de demi-aretes
     */
    void _link_halfedges(const std::map<std::pair<int, int>, HalfEdge*>& links);

private: /// Methodes privees de lecture/ecriture de fichier OFF
    /**
     * @brief Lis l'en-tete d'un fichier OFF et stocke son contenu dans un container
     * @param path Chemin vers le fichier
     * @param stream Reference vers le container pour stocker le contenu du fichier
     * @return true si succes, false sinon
     */
    bool _read_OFF_header(const char* path, std::stringstream& stream);

public: /// Methodes import/export format OFF
    /**
     * @brief Importe un modele represente par un fichier OFF et cree le maillage
     *        correspondant
     * @param path Chemin vers le fichier OFF
     * @return true si succes, false sinon
     */
    bool import(const char* path);

    /**
     * @brief Exporte le maillage courant au format OFF
     * @param path Chemin vers le fichier OFF a ecrire
     * @return true si succes, false sinon
     */
    bool export_as(const char* path) const;

public: /// Misc
    /**
     * @brief Ajoute les voisins d'un sommet au vecteur de sommet donne
     * @param vert_index Identifiant du sommet
     * @param out Vecteur de sommets, modifie par effet de bord
     * @return true si succes, false sinon
     */
    bool push_vertex_neighbours(int vert_index, std::vector<Vertex*>& out) const;

private: /// Methodes privees pour la generation de mesh a partir d'un nuage de point
    /**
     * @brief Cherche les k plus proches voisins d'un sommet v
     * @param k Nombre de voisins a chercher
     * @param v Adresse du sommet
     * @return Liste des k coordonnees des voisins de v
     */
    std::list<glm::vec3> k_neighbourhood(int k, Vertex* v);

    std::list<int> tan_plane_k_neighbourhood(int k, TangentPlane* tp);

    /**
     * @brief Cherche les k plus proches voisins d'un sommet v en utilisant PCL (O(nlog(n))
     * @param k Nombre de voisins a chercher
     * @param v Adresse du sommet
     * @return Liste des k coordonnees des voisins de v
     */
    std::list<glm::vec3> k_neighbourhoodPCL(int k, Vertex* v);

    /**
     * @brief Cherche les k plus proches plans voisins d'un plan tangent tp en utilisant PCL (O(nlog(n))
     * @param k Nombre de voisins a chercher
     * @param tp Adresse du plan tangent
     * @return Liste des k indices des voisins de tp
     */
    std::vector<int> tan_plane_k_neighbourhoodPCL(int k, TangentPlane* tp);


public:
    /**
     * @brief Construit les plans tangent pour chaque point
     * @return -1 en cas d'echec, 0 sinon
     */
    int __build_planes();

    int __orient_planes_normals();

};

#endif // MESH_H
