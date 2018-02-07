#include "vertex.h"


// ------------------------------------------------------------------------------------
// Re-definition de l'operateur << (friend)

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << "Vertex " << v.get_id() << ":" << std::endl;
    for (auto it : v.coordinates()) {
        os << it << " ";
    }

    return os;
}

// ------------------------------------------------------------------------------------
// MACRO

int Vertex::NBR_OF_VERT = 0;


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

Vertex::Vertex(const std::initializer_list<float> &l) :
    _id(Vertex::NBR_OF_VERT),
    _coord(l)
{
    Vertex::NBR_OF_VERT += 1;
}


// ------------------------------------------------------------------------------------
// ACCESSEURS

int Vertex::get_id() const {
    return _id;
}

const std::vector<float>& Vertex::coordinates() const {
    return _coord;
}

std::vector<float>& Vertex::coordinates() {
    return _coord;
}

const HalfEdge* Vertex::edge_ptr() const {
    return _i_edge;
}

HalfEdge* Vertex::edge_ptr() {
    return _i_edge;
}

void Vertex::set_i_edge(HalfEdge* edge) {
    _i_edge = edge;
}

