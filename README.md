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


### Implémentation
Pour représenter un point, on utilisera OpenGL Mathematics et notamment ```glm::vec3```

Un maillage est représenté par un ensemble de faces et un ensemble de sommets mis en relation par des demi-arêtes.
On a donc un objet **face**, un objet **halfedge** et un objet **vertex**. Ensuite, l'objet  **tangentPlane** nous servira à approximer la surface en chaque sommet. Le **mesh** sera constitué de ces objets avec en utilisant ``` std::map ```
```cpp
std::map<int, Vertex*> _vertices;
std::map<int, TangentPlane*> _tan_planes;
std:map<int, Face*> _faces;
``` 
Les **plans tangents** sont représentés par un point qui est son centre et un vecteur normal.
```cpp
glm::vec3 _center;
glm::vec3 _normal;
``` 
Chaque point aura un plan tangent *t*. Pour calculer ce plan, il faut trouver les k plus proches voisins de *t*. Pour cela, on utilise un *KdTree*, qui est une structure de donné qui permet d'orgniser des points dans un espace à *k* dimensions. On utilise la librairie PointCloud, qui nous permet de le faire avec une complexité en ```O(nlog(n))``` : http://pointclouds.org/documentation/tutorials/kdtree_search.php



### Résultats
