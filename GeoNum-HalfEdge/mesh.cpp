#include "mesh.h"

#include <vector>
#include <algorithm>


// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

Mesh::Mesh() :
    _vertices(),
    _faces()
{}

Mesh::~Mesh() {
    // Liberation de la memoire pour les faces
    for (auto it = _faces.begin(); it != _faces.end(); ++it) {
        if (it->second != nullptr) {
            /* Libere en chaine la memoire allouee pour chacune des demi-aretes
             * pour chaque sommet (dans le sens direct), voir face.cpp */
            delete it->second;
        }
    }
    // Liberation de la memoire pour les sommets
    for (auto it = _vertices.begin(); it != _vertices.end(); ++it) {
        if (it->second != nullptr) {
            delete it->second;
        }
    }
}


// ------------------------------------------------------------------------------------
// METHODES PRIVEES DE CREATION DU MESH

int Mesh::_add_vertex(float x, float y, float z) {
    Vertex* v = new Vertex(x, y, z);
    auto ret = _vertices.insert(std::pair<int, Vertex*>(v->get_id(), v));
    if (ret.second == false) {
        std::cerr << "Vertex duplicated!" << std::endl;
        delete v;
        return -1;
    }
    return v->get_id();
}

int Mesh::_add_face(int n, const int* indices,
                    std::map<std::pair<int, int>, HalfEdge*>& links)
{
    if (n < 0) {
        std::cerr << "Invalid number of vertices" << std::endl;
        return -1;
    }

    std::vector<Vertex*> v;
    for (int i = 0; i < n; i++) {
        v.push_back(_vertices[indices[i]]);
    }

    Face* f = new Face(v);
    auto ret = _faces.insert(std::pair<int, Face*>(f->get_id(), f));
    if (ret.second == false) {
        std::cerr << "Face duplicated!" << std::endl;
        delete f;
        return -1;
    }

    HalfEdge* ie = f->edge_ptr();
    HalfEdge* scan = ie;
    // Parcours des demi-aretes jusqu'a revenir sur la demi-arete incidente
    do {
        int source_id = scan->source()->get_id();
        int target_id = scan->next()->source()->get_id();
        // Enregistrement de la demi-arete dans la map links (voir mesh.h)
        auto ret = links.insert(
                    std::pair<std::pair<int, int>, HalfEdge*>(
                        std::pair<int, int>(source_id, target_id), scan));
        if (ret.second == false) {
            std::cerr << "Edge duplicated!" << std::endl;
            return -1;
        }

        scan = scan->next();
    } while (scan != ie);

    return f->get_id();
}

void Mesh::_link_halfedges(const std::map<std::pair<int, int>, HalfEdge*>& links) {
    // Pour chaque face
    for (auto it = _faces.begin(); it != _faces.end(); ++it) {
        // Parcours des demi-aretes a partir de la demi-arete incidente
        HalfEdge* ie = it->second->edge_ptr();
        HalfEdge* scan = ie;
        do {
            // Mettre a jour la demi-arete incidente du sommet
            scan->source()->set_i_edge(scan);
            // Recherche de la demi-arete inverse
            int source_id = scan->source()->get_id();
            int target_id = scan->next()->source()->get_id();
            auto it = links.find(std::pair<int, int>(target_id, source_id));
            if (it != links.end()) {
                // Mise a jour de la tete-beche
                scan->set_inverse(it->second);
            }
            else {
                std::cout << "!!! Missing Halfedge !!!" << std::endl;
            }

            scan = scan->next();
        } while (scan != ie);
    }
}


// ------------------------------------------------------------------------------------
// METHODES IMPORT/EXPORT FORMAT OFF

bool Mesh::_read_OFF_header(const char* path, std::stringstream& stream) {
    std::ifstream is;
    // Ouverture du fichier
    is.open(path);
    if ( (is.rdstate() & std::ifstream::failbit ) != 0 ) {
        std::cerr << "Error opening " << path << std::endl;
        return false;
    }
    // Calcul de la taille du fichier
    int length = -1;
    is.seekg(0, is.end);
    length = is.tellg();
    is.seekg(0, is.beg);
    if (length == -1) {
        std::cerr << "Error computing buffer size" << std::endl;
        return false;
    }
    char* buffer = new char[length];
    // Lecture et chargement dans un buffer
    is.read(buffer, length);
    if(!is) {
        std::cerr << "Error reading " << path << std::endl;
        is.close();
        delete[] buffer;
        return false;
    }
    // Fermeture du fichier
    is.close();
    // Chargement du buffer dans le stringstream
    stream.str(buffer);
    // Suppression du buffer
    delete[] buffer;

    std::string str;
    // Verification de la signature OFF
    std::getline(stream, str);
    if (str != "OFF") {
        std::cerr << "Invalid file signature" << std::endl;
        return false;
    }
    // Elimination des commentaires
    int pos;
    do {
        pos = stream.tellg();
        std::getline(stream, str);
    } while (str[0] == '#');
    stream.seekg(pos);

    return true;
}


// ------------------------------------------------------------------------------------
// METHODES IMPORT/EXPORT FORMAT OFF

bool Mesh::import(const char* path) {
    std::cout << "Import :" << std::endl;
    std::stringstream stream;
    if (!_read_OFF_header(path, stream)) {
        std::cerr << "Error reading OFF header" << std::endl;
        return false;
    }

    int v, f, e;
    stream >> v;
    stream >> f;
    stream >> e;

    if (v < 3 || f < 1) {
        std::cerr << "Inconsistant model" << std::endl;
        return false;
    }

    // Generation des sommets
    float x, y, z;
    for (int i = 0; i < v; i++) {
        stream >> x;
        stream >> y;
        stream >> z;
        int check = _add_vertex(x, y, z);
        if (check != i) {
            std::cerr << "Error generating vertex nbr " << i
                      << " : got " << check << std::endl;
            return false;
        }
    }

    std::map<std::pair<int, int>, HalfEdge*> links;

    // Generation des faces
    for (int i = 0; i < f; i++) {
        int n;
        stream >> n;
        if (n < 3) {
            std::cerr << "Inconsistant model" << std::endl;
            return false;
        }

        int indices[n];
        for (int j = 0; j < n; j++) {
            stream >> indices[j];
        }

        int check = _add_face(n, indices, links);
        if (check != i) {
            std::cerr << "Error generating face nbr " << i
                      << " : got " << check << std::endl;
            return false;
        }
    }

    // Demi-aretes tete-beches
    _link_halfedges(links);

    std::cout << "OFF file successfully imported." << std::endl;

    // Debug
    std::cout << std::endl;
    for (auto it : _faces) {
        std::cout << *(it.second) << std::endl;
        glm::vec3 n = it.second->normal();
        std::cout << "n(" << n[0] << ", " << n[1] << ", " << n[2] << ")" << std::endl;
    }
    std::cout << std::endl;
    for (auto it : _vertices) {
        std::cout << *(it.second) << std::endl;
    }
    std::cout << std::endl;

    return true;
}

bool Mesh::export_as(const char* path) const {
    std::ofstream of;
    of.open(path);
    if ((of.rdstate() & std::ofstream::failbit ) != 0) {
        std::cerr << "Error opening " << path << std::endl;
        return false;
    }
    // TODO
    of.close();
    return true;
}


// ------------------------------------------------------------------------------------
// MISC

bool Mesh::push_vertex_neighbours(int vert_index, std::vector<Vertex*>& out) {
    auto ret = _vertices.find(vert_index);
    if (ret == _vertices.end()) {
        return false;
    }
    ret->second->push_neighbours(out);

    return true;
}
