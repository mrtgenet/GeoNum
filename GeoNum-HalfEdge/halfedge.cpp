#include "halfedge.h"


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

HalfEdge::HalfEdge(Vertex *source, Face *face) :
    _source(source),
    _face(face)
{

}

HalfEdge::~HalfEdge() {
    HalfEdge* tmp = _next;
    while (_next != nullptr) {
        _next = _next->next();
        delete tmp;
        tmp = _next;
    }
}

// ------------------------------------------------------------------------------------
// ACCESSEURS

const Vertex* HalfEdge::source() const {
    return _source;
}

const Face* HalfEdge::face() const {
    return _face;
}

const HalfEdge* HalfEdge::next() const {
    return _next;
}

HalfEdge* HalfEdge::next() {
    return _next;
}

void HalfEdge::set_next(HalfEdge* next) {
    _next = next;
}

const HalfEdge* HalfEdge::inverse() const {
    return _inverse;
}

HalfEdge* HalfEdge::inverse() {
    return _inverse;
}

void HalfEdge::set_inverse(HalfEdge* inverse) {
    _inverse = inverse;
}
