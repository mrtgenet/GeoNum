Lambrecht Louis
Genet Martin
 M1 ISI 2017-2018
 
# Géométrie Numérique
## Rapport de projet
Reconstruction de surface à partir de points non organisés
Basé sur l'article de Hugues Hoppe, Tony DeRose, Tom Duchamp, John McDonald et Werner Stuetzle
### Utilisation
Il est possible d'avoir à installer quelques librairies que nous avons utilisés :
PointCloud, libproj4, eigen, boost, OpenGL Mathematics
```sh
$ sudo apt-get install libpcl-dev
$ sudo apt-get install libproj4-dev
$ sudo apt-get install libglm-dev
$ sudo apt-get install libboost-dev
```

Il se peut également qu'il faille ensuite créer un lien :
```sh
$ sudo ln -s /usr/lib/x86_64-linux-gnu/libvtkCommonCore-6.2.so /usr/lib/libvtkproj4.so
```

Compiler le programme
```sh
$ make
```

ou bien utiliser QtCreator avec le CMakeLists.txt

### Implémentation

Pour représenter un point, on utilisera OpenGL Mathematics et notamment ```glm::vec3```

Un maillage est représenté par un ensemble de faces et un ensemble de sommets mis en relation par des demi-arêtes, structures pour lesquelles on a respectivement les classes **Face**, **Vertex** et **HalfEdge**. La classe **Mesh** consiste donc essentiellement en deux ``` std::map ``` pour stocker les faces et les sommets (on génère les demi-arêtes correspondantes à la volée). Cette structure permet de charger et de sauvegarder des maillages au format OFF.

Pour la reconstruction de maillage à partir d'un nuage de points, la classe  **TangentPlane** nous servira à approximer la surface en chaque sommet. Le **Mesh** comportera donc les objets suivant : 
```cpp
std::map<int, Vertex*> _vertices;
std::map<int, TangentPlane*> _tan_planes;
std:map<int, Face*> _faces;
``` 
Les **plans tangents** sont sont construits dans la classe **Mesh** en calculant les k plus proches voisins de chaque point. Pour cela, on utilise un *KdTree*, qui est une structure de donnée qui permet d'orgniser des points dans un espace à *k* dimensions. On utilise la librairie PointCloud, qui nous permet de le faire avec une complexité en ```O(nlog(n))``` : http://pointclouds.org/documentation/tutorials/kdtree_search.php. A partir du voisinage d'un point *t*, on peut donc représenter le plan tangent *Tp(t)* par le barycentre des k voisins de *t* et le vecteur normal au plan obtenu en calculant les vecteurs propres de la matrice de covariance des k voisins, ce qui est fait via un ```EigenSolver``` de la librairie Eigen. Un objet **TangentPlane** consiste donc essentiellement deux attributs :
```cpp
glm::vec3 _center;
glm::vec3 _normal;
``` 

Ces données permettent facilement d'implémenter la distance signée utilisée dans le papier de recherche, ainsi que le calcul de l'indice exprimant à quel point deux plans sont parallèles, pour orienter les normales de manière consistante.

### Résultats


### Discussions
