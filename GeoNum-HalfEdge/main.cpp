#include <stdio.h>  /* FILENAME_MAX */
// #define WINDOWS  /* uncomment this line for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>

#include "tangentPlane.h"
#include "mesh.h"

using namespace std;

std::string get_current_dir() {
  char buff[FILENAME_MAX];
  GetCurrentDir(buff, FILENAME_MAX);
  std::string current_dir(buff);
  return current_dir;
}

int main()
{
    std::string PATH = get_current_dir();
    PATH = PATH + "/../";
    cout << PATH << std::endl;
    std::string cube = PATH + "cube.off";

    Mesh mesh;
    mesh.import(cube.c_str());
    mesh.export_as((PATH + "out.off").c_str());

    std::vector<Vertex*> v;
    mesh.push_vertex_neighbours(4, v);
    // Resultat attendu : 7(0, 0, 1), 0(1, 1, 1), 5(1, 0, 0)
    std::cout << "Vertex 4 neighbours :" << std::endl;
    for (auto it : v) {
        std::cout << (*it) << std::endl;
    }
    std::cout << std::endl;

    mesh.__build_planes();

    return 0;
}

