#include "vertex.h"


// ------------------------------------------------------------------------------------
// Re-definition de l'operateur << (friend)

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << "Vertex " << v.get_id() << ":" << std::endl;
    os << v.coordinates()[0] << " " << v.coordinates()[1] << " " << v.coordinates()[2];

    return os;
}

// ------------------------------------------------------------------------------------
// MACRO

int Vertex::NBR_OF_VERT = 0;


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

Vertex::Vertex(float x, float y, float z) :
    _id(Vertex::NBR_OF_VERT),
    _coord(x, y, z)
{
    Vertex::NBR_OF_VERT += 1;
}


// ------------------------------------------------------------------------------------
// ACCESSEURS

int Vertex::get_id() const {
    return _id;
}

const float Vertex::getX() const{
    return _coord.x;
}

const float Vertex::getY() const{
    return _coord.y;
}

const float Vertex::getZ() const{
    return _coord.z;
}

float Vertex::getX(){
    return _coord.x;
}

float Vertex::getY(){
    return _coord.y;
}

float Vertex::getZ(){
    return _coord.z;
}

const glm::vec3 &Vertex::coordinates() const {
    return _coord;
}

glm::vec3 &Vertex::coordinates() {
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


// ------------------------------------------------------------------------------------
// MISC

void Vertex::push_neighbours(std::vector<Vertex*>& out) {
    HalfEdge* tmp = _i_edge;
    // Parcours des demi-aretes autour du sommet courant jusqu'a revenir sur _i_edge
    do {
        tmp = tmp->inverse();
        out.push_back(tmp->source());
        tmp = tmp->next();
    } while (tmp != _i_edge);
}
