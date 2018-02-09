#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>

#include "halfedge.h"
#include "vertex.h"

// Preproc
class HalfEdge;
class Vertex;

/**
 * @brief Representation d'une face par son nombre de sommets,
 *        une demi-arete incidente, et un identifiant unique
 */
class Face
{
    /// Operateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Face& f);

private: /// Macro
    /**
     * @brief Nombre total de faces construites
     */
    static int NBR_OF_FACES;

private: /// Donnees privees
    /**
     * @brief Identifiant unique compris entre 0 (inclu) et NBR_OF_FACES (exclu)
     */
    int _id;

    /**
     * @brief Nombre de sommets de la face
     */
    unsigned int _nbr_of_vert;

    /**
     * @brief Pointeur vers une demi-arete incidente a la face
     */
    HalfEdge* _i_edge;

public: /// Constructeurs
    /**
     * @brief Constructeur par defaut, genere les demi-aretes entre chaque sommet dans
     *        le sens direct
     * @param v Vecteur des sommets de la face
     */
    Face(const std::vector<Vertex*>& v);

    /**
     * @brief Destructeur, libere la memoire allouee pour les demi-aretes entre chaque
     *        sommet dans le sens direct
     */
    ~Face();

public: /// Accesseurs
    /**
     * @brief Getter pour l'identifiant
     * @return Retourne l'identifiant de la face
     */
    int get_id() const;

    /**
     * @brief Taille (nombre de sommets) de la face
     * @return Retourne le nombre de sommets de la face
     */
    unsigned int size() const;

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
     * @param edge Pointeur vers une demi-arete incidente a la face
     */
    void set_i_edge(HalfEdge* edge);

public: /// Misc
    /**
     * @brief Calcule de la normale de la face
     * @return Retourne le vecteur unitaire normal de la face
     */
    glm::vec3 normal() const;

    /**
     * @brief Calcule le barycentre de la face
     * @return Retourne un vecteur des coordonnees 3D du barycentre de la face
     */
    glm::vec3 centroid() const;
};

#endif // FACE_H
