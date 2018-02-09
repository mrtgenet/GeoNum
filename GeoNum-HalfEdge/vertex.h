#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <glm/vec3.hpp>
#include <iostream>

#include "halfedge.h"

// Preproc
class HalfEdge;

/**
 * @brief Representation d'un sommet par ses coordonnees, une demi-arete incidente et
 *        un identifiant unique
 */
class Vertex
{
    /// Operateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Vertex& v);

private: /// Macro
    /**
     * @brief Nombre total de sommets construits
     */
    static int NBR_OF_VERT;

private: /// Donnees privees
    /**
     * @brief Identifiant unique compris entre 0 (inclu) et NBR_OF_VERT (exclu)
     */
    int _id;

    /**
     * @brief Vecteur des coordonnees 3D du sommet
     */
    glm::vec3 _coord;

    /**
     * @brief Pointeur vers une demi-arete incidente au sommet
     */
    HalfEdge* _i_edge;

public: /// Constructeurs
    /**
     * @brief Constructeur par defaut, initialise les coordonnees du sommet
     * @param x Coordonnee en X
     * @param y Coordonnee en Y
     * @param z Coordonnee en Z
     */
    Vertex(float x, float y, float z);

public: /// Accesseurs
    /**
     * @brief Getter pour l'identifiant
     * @return Retourne l'identifiant du sommet
     */
    int get_id() const;

    /**
     * @brief Getter en lecture seule pour les coordonnees
     * @return Retourne une reference des coordonnees en lecture seule
     */
    const glm::vec3& coordinates() const;

    /**
     * @brief Getter en lecture/ecriture pour les coordonnees
     * @return Retourne une reference des coordonnees en lecture/ecriture
     */
    glm::vec3& coordinates();

    /**
     * @brief Getter const pour la demi-arete incidente
     * @return Retourne un pointeur const vers la demi-arete incidente
     */
    const HalfEdge* edge_ptr() const;

    /**
     * @brief Getter pour la demi-arete incidente
     * @return Retourne un pointeur vers la demi-arete incidente
     */
    HalfEdge* edge_ptr();

    /**
     * @brief Setter pour la demi-arete incidente
     * @param edge Pointeur vers une demi-arete incidente au sommet
     */
    void set_i_edge(HalfEdge* edge);

public: /// Misc
    /**
     * @brief Ajoute les voisins directs du sommet au vecteur en parametre
     * @param out Vecteur de pointeurs de sommets, modifie par effet de bord
     */
    void push_neighbours(std::vector<Vertex*>& out);
};

#endif // VERTEX_H
