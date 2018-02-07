#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <iostream>

#include "vertex.h"
#include "face.h"

// Preproc
class Vertex;
class Face;

class HalfEdge
{
private: /// Donnees privees
    Vertex* _source;

    Face* _face;

    HalfEdge* _next;

    HalfEdge* _inverse;

public: /// Constructeurs
    HalfEdge(Vertex* source, Face* face);

    ~HalfEdge();

public: /// Accesseurs
    const Vertex* source() const;

    const Face* face() const;

    const HalfEdge* next() const;

    HalfEdge* next();

    void set_next(HalfEdge* next);

    const HalfEdge* inverse() const;

    HalfEdge* inverse();

    void set_inverse(HalfEdge* inverse);
};

#endif // HALFEDGE_H
