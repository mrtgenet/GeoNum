#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <iostream>

#include "vertex.h"
#include "face.h"

// Preproc
class Vertex;
class Face;

/**
 * @brief Representation des demi-aretes par un sommet source, un face incidente,
 *        la demi-arete suivante dans le sens direct, et la demi-arete tete-beche
 */
class HalfEdge
{
private: /// Donnees privees
    /**
     * @brief Pointeur vers le sommet source
     */
    Vertex* _source;

    /**
     * @brief Pointeur vers une face incidente
     */
    Face* _face;

    /**
     * @brief Pointeur vers la demi-arete suivante dans le sens direct
     */
    HalfEdge* _next;

    /**
     * @brief Pointeur vers la demi-arete tete-beche
     */
    HalfEdge* _inverse;

public: /// Constructeurs
    /**
     * @brief Constructeur par defaut, initialise le sommet source et la face incidente
     * @param source Pointeur vers le sommet source
     * @param face Pointeur vers une face incidente
     */
    HalfEdge(Vertex* source, Face* face);

public: /// Accesseurs
    /**
     * @brief Getter const pour le sommet source
     * @return Retourne un pointeur const vers le sommet source
     */
    const Vertex* source() const;

    /**
     * @brief Getter pour le sommet source
     * @return Retourne un pointeur vers le sommet source
     */
    Vertex* source();

    /**
     * @brief Getter const pour la face incidente
     * @return Retourne un pointeur const vers la face incidente
     */
    const Face* face() const;

    /**
     * @brief Getter pour la face incidente
     * @return Retourne un pointeur vers la face incidente
     */
    Face* face();

    /**
     * @brief Getter const pour la demi-arete suivante dans le sens direct
     * @return Retourne un pointeur const vers la demi-arete suivante dans
     *         le sens direct
     */
    const HalfEdge* next() const;

    /**
     * @brief Getter pour la demi-arete suivante dans le sens direct
     * @return Retourne un pointeur vers la demi-arete suivante dans le sens direct
     */
    HalfEdge* next();

    /**
     * @brief Setter pour la demi-arete suivante dans le sens direct
     * @param next Pointeur vers la demi-arete suivante
     */
    void set_next(HalfEdge* next);

    /**
     * @brief Getter const pour la demi-arete tete-beche
     * @return Retourne un pointeur const vers la demi-arete tete-beche
     */
    const HalfEdge* inverse() const;

    /**
     * @brief Getter pour la demi-arete tete-beche
     * @return Retourne un pointeur vers la demi-arete tete-beche
     */
    HalfEdge* inverse();

    /**
     * @brief Setter pour la demi-arete tete-beche
     * @param inverse Pointeur vers la demi-arete tete-beche
     */
    void set_inverse(HalfEdge* inverse);
};

#endif // HALFEDGE_H
