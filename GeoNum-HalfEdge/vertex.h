#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <iostream>

#include "halfedge.h"

// Preproc
class HalfEdge;

class Vertex
{
private: /// Macro
    static int NBR_OF_VERT;

private: /// Donnees privees
    int _id;

    std::vector<float> _coord;

    HalfEdge* _i_edge;

public: /// Constructeurs
    Vertex(const std::initializer_list<float>& l);

public: /// Accesseurs
    int get_id() const;

    const std::vector<float>& coordinates() const;

    std::vector<float>& coordinates();

    const HalfEdge* edge_ptr() const;

    HalfEdge* edge_ptr();

    void set_i_edge(HalfEdge* edge);
};

#endif // VERTEX_H
