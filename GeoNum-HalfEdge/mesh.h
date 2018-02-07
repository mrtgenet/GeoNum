#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "vertex.h"
#include "face.h"


class Mesh
{
private: /// Donnees privees
    std::map<int, Vertex*> _vertices;

    std::map<int, Face*> _faces;

//    std::map<std::pair<int, int>, HalfEdge*>* _links;

public: /// Constructeurs
    Mesh();

    ~Mesh();

private: /// Methodes privees de creation du mesh
    int _add_vertex(float x, float y, float z);

    int _add_face(int n, const int* indices,
                  std::map<std::pair<int, int>, HalfEdge*>& links);

    void _link_halfedges(std::map<std::pair<int, int>, HalfEdge*>& links);

private: /// Methodes privees de lecture/ecriture de fichier OFF
    bool _read_OFF_header(const char* path, std::stringstream& stream);

public: /// Methodes import/export format OFF
    bool import(const char* path);

    bool export_as(const char* path) const;

public: /// Misc
    bool push_vertex_neighbours(int vert_index, std::vector<Vertex*>& out);
};

#endif // MESH_H
