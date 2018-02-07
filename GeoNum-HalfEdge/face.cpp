#include "face.h"


// ------------------------------------------------------------------------------------
// Re-definition de l'operateur << (friend)

std::ostream& operator<<(std::ostream& os, const Face& f) {
    os << "Face " << f.get_id() << ":" << std::endl;
    const HalfEdge* tmp = f.edge_ptr();
    do {
        os << tmp->source()->get_id() << " ";
        tmp = tmp->next();
    } while (tmp != f.edge_ptr());

    return os;
}


// ------------------------------------------------------------------------------------
// MACRO

int Face::NBR_OF_FACES = 0;


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

Face::Face(const std::vector<Vertex*>& v):
    _id(Face::NBR_OF_FACES)
{
    Face::NBR_OF_FACES += 1;

    auto it = v.begin();
    _i_edge = new HalfEdge(*it, this);
    ++it;
    HalfEdge* tmp_edge = nullptr;
    HalfEdge* prec = _i_edge;

    while (it != v.end()) {
        tmp_edge = new HalfEdge(*it, this);
        prec->set_next(tmp_edge);
        tmp_edge = nullptr;
        prec = prec->next();
        ++it;
    }
    prec->set_next(_i_edge);

    // DEBUG
//    std::cout << "Face : " << _i_edge->face()->get_id() << std::endl;
//    tmp_edge = _i_edge;
//    do {
//        std::cout << tmp_edge->source()->get_id() << " -> "
//                  << tmp_edge->next()->source()->get_id() << "\n";
//        tmp_edge = tmp_edge->next();
//    } while (tmp_edge != _i_edge);
//    std::cout << std::endl;
}

Face::~Face() {
    HalfEdge* tmp = _i_edge->next();
    while (tmp != _i_edge) {
        HalfEdge* del = tmp;
        tmp = tmp->next();
        delete del;
    }
    delete _i_edge;
}


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

int Face::get_id() const {
    return _id;
}

const HalfEdge* Face::edge_ptr() const {
    return _i_edge;
}

HalfEdge* Face::edge_ptr() {
    return _i_edge;
}

void Face::set_i_edge(HalfEdge* edge) {
    _i_edge = edge;
}
