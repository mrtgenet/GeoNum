#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>

#include "halfedge.h"
#include "vertex.h"

// Preproc
class HalfEdge;
class Vertex;

class Face
{
private: /// Macro
    static int NBR_OF_FACES;

private: /// Donnees privees
    int _id;

    HalfEdge* _i_edge;

public: /// Constructeurs
    Face(const std::vector<Vertex*>& v);

    ~Face();

public: /// Accesseurs
    int get_id() const;

    const HalfEdge* edge_ptr() const;

    HalfEdge* edge_ptr();

    void set_i_edge(HalfEdge* edge);
};

#endif // FACE_H
