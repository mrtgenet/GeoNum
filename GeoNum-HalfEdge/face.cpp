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

unsigned long Face::NBR_OF_FACES = 0;


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

Face::Face(const std::vector<Vertex*>& v):
    _id(Face::NBR_OF_FACES),
    _nbr_of_vert(v.size())
{
    Face::NBR_OF_FACES += 1;

    auto it = v.begin();
    // Creation de la demi-arete incidente
    _i_edge = new HalfEdge(*it, this);
    ++it;
    HalfEdge* tmp_edge = nullptr;
    HalfEdge* prec = _i_edge;
    // Creation des demi-aretes entre chaque sommet (dans le sens direct)
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
    // Liberation de l'espace memoire pour toutes les demi-aretes dans le sens direct
    while (tmp != _i_edge) {
        HalfEdge* del = tmp;
        tmp = tmp->next();
        delete del;
    }
    delete _i_edge;
}


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

unsigned long Face::get_id() const {
    return _id;
}

unsigned int Face::size() const {
    return _nbr_of_vert;
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


// ------------------------------------------------------------------------------------
// MISC

glm::vec3 Face::normal() const {
    glm::vec3 n;
    HalfEdge* left = _i_edge->next();
    HalfEdge* right = left->next();
    // Cas simple : face triangulaire
    if (_nbr_of_vert == 3) {
        glm::vec3 u = left->source()->coordinates()
                - _i_edge->source()->coordinates();
        glm::vec3 v = right->source()->coordinates()
                - _i_edge->source()->coordinates();
        n = glm::normalize(glm::cross(u, v));
    }
    // Moyenne des normales
    else {
        std::vector<glm::vec3> normals;
        // Parcours des triangles composant la face pour calculer leur normale
        do {
            glm::vec3 u = left->source()->coordinates()
                    - _i_edge->source()->coordinates();
            glm::vec3 v = right->source()->coordinates()
                    - _i_edge->source()->coordinates();
            normals.push_back(glm::normalize(glm::cross(u, v)));
            left = left->next();
            right = right->next();
        } while (right != _i_edge);
        // Moyenne des normales
        int k = normals.size();
        for (auto it : normals) {
            n += it;
        }
        n *= 1.f / (float) k;
    }
    return n;
}
