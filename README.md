Lambrecht Louis
Genet Martin
 M1 ISI 2017-2018
 
# Géométrie Numérique

## Rapport de projet

Reconstruction de surface à partir de points non organisés
Basé sur l'article de Hugues Hoppe, Tony DeRose, Tom Duchamp, John McDonald et Werner Stuetzle

**Etat actuel :** Implémentation jusqu'a l'orientation des normales aux plans tangents.

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
std::map<int, Face*> _faces;
``` 
Les **plans tangents** sont sont construits dans la classe **Mesh** en calculant les k plus proches voisins de chaque point. Pour cela, on utilise un *KdTree*, qui est une structure de donnée qui permet d'orgniser des points dans un espace à *k* dimensions. On utilise la librairie PointCloud, qui nous permet de le faire avec une complexité en ```O(nlog(n))``` : http://pointclouds.org/documentation/tutorials/kdtree_search.php. A partir du voisinage d'un point *t*, on peut donc représenter le plan tangent *Tp(t)* par le barycentre des k voisins de *t* et le vecteur normal au plan obtenu en calculant les vecteurs propres de la matrice de covariance des k voisins, ce qui est fait via un ```EigenSolver``` de la librairie Eigen. Un objet **TangentPlane** consiste donc essentiellement deux attributs :
```cpp
glm::vec3 _center;
glm::vec3 _normal;
``` 

Ces données permettent facilement d'implémenter la distance signée utilisée dans le papier de recherche, ainsi que le calcul de l'indice exprimant à quel point deux plans sont parallèles, pour orienter les normales de manière consistante.

### Résultats

Test mémoire (valgrind) :
```
==3377== 
==3377== HEAP SUMMARY:
==3377==     in use at exit: 72,712 bytes in 2 blocks
==3377==   total heap usage: 516 allocs, 514 frees, 215,526 bytes allocated
==3377== 
==3377== LEAK SUMMARY:
==3377==    definitely lost: 0 bytes in 0 blocks
==3377==    indirectly lost: 0 bytes in 0 blocks
==3377==      possibly lost: 0 bytes in 0 blocks
==3377==    still reachable: 72,712 bytes in 2 blocks
==3377==         suppressed: 0 bytes in 0 blocks
==3377== Rerun with --leak-check=full to see details of leaked memory
==3377== 
==3377== For counts of detected and suppressed errors, rerun with: -v
==3377== Use --track-origins=yes to see where uninitialised values come from
==3377== ERROR SUMMARY: 121 errors from 9 contexts (suppressed: 0 from 0)
```

Résultat de l'exécution (importation de cube.off, calcul des k-voisins, création des plans tangents)
```
Import :
OFF file successfully imported.

Face 0:
0 1 2 3 
n(0, 1, 0)
c(0.5, 1, 0.5)
Face 1:
7 4 0 3 
n(0, 0, 1)
c(0.5, 0.5, 1)
Face 2:
4 5 1 0 
n(1, 0, 0)
c(1, 0.5, 0.5)
Face 3:
5 6 2 1 
n(0, 0, -1)
c(0.5, 0.5, 0)
Face 4:
3 2 6 7 
n(-1, 0, 0)
c(0, 0.5, 0.5)
Face 5:
6 5 4 7 
n(0, -1, 0)
c(0.5, 0, 0.5)

Vertex 0:
1 1 1
Vertex 1:
1 1 0
Vertex 2:
0 1 0
Vertex 3:
0 1 1
Vertex 4:
1 0 1
Vertex 5:
1 0 0
Vertex 6:
0 0 0
Vertex 7:
0 0 1

Vertex 4 neighbours :
Vertex 7:
0 0 1
Vertex 0:
1 1 1
Vertex 5:
1 0 0

Tangent Plane 0 : 
Centre : 0.666667 0.666667 0.666667
Normale : -0.57735 -0.57735 -0.57735

Tangent Plane 1 : 
Centre : 0.666667 0.666667 0.333333
Normale : -0.57735 -0.57735 0.57735

Tangent Plane 2 : 
Centre : 0.333333 0.666667 0.333333
Normale : 0.57735 -0.57735 0.57735

Tangent Plane 3 : 
Centre : 0.333333 0.666667 0.666667
Normale : 0.57735 -0.57735 -0.57735

Tangent Plane 4 : 
Centre : 0.666667 0.333333 0.666667
Normale : 0.57735 -0.57735 0.57735

Tangent Plane 5 : 
Centre : 0.666667 0.333333 0.333333
Normale : 0.57735 -0.57735 -0.57735

Tangent Plane 6 : 
Centre : 0.333333 0.333333 0.333333
Normale : -0.57735 -0.57735 -0.57735

Tangent Plane 7 : 
Centre : 0.333333 0.333333 0.666667
Normale : -0.57735 -0.57735 0.57735
```

Calcul du temps d'exécution pour un fichier de 2132 points :
```
OFF file successfully imported.
Mesh import execution time : 0.041439 s
Tangent planes construction execution time : 2.90667 s
```

### Discussions

L’avantage de cette méthode consiste dans le fait qu’aucune information supplémentaire sur la structure de la surface à reconstituer n’est nécessaire : on peut reconstruire un maillage à partir du nuage de points brut. On peut donc utiliser cette approche là où d’autres sont impraticables.

Mais on voit sur les exemples qui mettent en oeuvre cette méthode qu’elle présente des problèmes à certains endroits clés (par exemple les oreilles du chat). On peut expliquer cela par le fait que s’il n’y a pas suffisamment de points aux arêtes vives, l’approximation des plans tangents ne permettra pas la représentation effective de la forme à reconstituer. Pour palier à ce problème, on pourrait augmenter l’échantillonnage, mais alors une quantité excessive de points serait alors inutiles car se trouvant dans des zones relativement lisses. 

On peut donc imaginer une pré-étape qui permettrait de repérer ces arêtes vives et donc de corriger ce problème, par exemple en les subdivisant pour ajouter des points, mais ce serait une tâche très complexe n’ayant comme unique information qu’un nuage de point.

L’inconvénient majeur de cette technique réside donc dans le fait que l’on a justement pas d’information spécifiquement pour les arêtes vives avec le nuage de point brut. 
