#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>

#include "halfedge.h"
#include "vertex.h"

// Preproc
class HalfEdge;
class Vertex;

/**
 * @brief Representation d'une face par une demi-arete incidente
 */
class Face
{
    /// Operateur d'affichage
    friend std::ostream& operator<<(std::ostream& os, const Face& f);

private: /// Macro
    /**
     * @brief Nombre total de faces construites
     */
    static unsigned long NBR_OF_FACES;

private: /// Donnees privees
    /**
     * @brief Identifiant unique compris entre 0 (inclu) et NBR_OF_FACES (exclu)
     */
    unsigned long _id;

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
    unsigned long get_id() const;

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
    /* TODO : Calcul du centroid (barycentre) de la face (polynome simple)
     *  - ramener au plan z = cste (matrice de transfo M)
     *  - Aire A = 1/2 * Sum[0, n-1](x[i]*y[i+1] - x[i+1]*y[i])
     *  - Cx = 1/(6*A) * Sum[0, n-1]((x[i]+x[i+1])*(x[i]*y[i+1] - x[i+1]*y[i])
     *  - Cy = 1/(6*A) * Sum[0, n-1]((y[i]+y[i+1])*(x[i]*y[i+1] - x[i+1]*y[i])
     *  - transormation inverse de M
     * Cas d'une face triangulaire : C = 1/3 * (A + B + C)
     * Besoin de calculer la normale, puis rotation de la normale pour avoir (0, 0, 1)
     */
};

#endif // FACE_H
