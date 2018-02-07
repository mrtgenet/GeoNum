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

    return 0;
}

