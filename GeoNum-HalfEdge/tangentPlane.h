#ifndef TANGENT_PLANE_H
#define TANGENT_PLANE_H

#include <iostream>
#include <vector>
#include <list>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>
#include <eigen3/Eigen/Eigenvalues>


/**
* @brief Représentation d'un plan tangeant par un point et un vecteur normal
*        Chaque point du nuage aura un plan tangent
*/

class TangentPlane
{
    friend std::ostream& operator<<(std::ostream& os, const TangentPlane& plane);

private: // Macro
    /**
    * @brief Nombre total de plan tangent construits
    */
    static int NBR_OF_TANGENTPLANES;

private: //Données privées
    /**
    * @brief identifiant unique compris entre 0 (inclu) et NBR_OF_TANGENTPLANES (exclu)
    */
    int _id;

    /**
    * @brief Centre du plan tangent
    */
    glm::vec3 _center;

    /**
    * @brief Vecteur normal au plan tangent
    */
    glm::vec3 _normal;

public: // Constructeurs
    /**
     * @brief Constructeur par defaut, cree le centre et la normale au plan a partir
     *        d'une liste de sommets
     * @param vertices Liste de sommets definissant le plan
     */
    TangentPlane(const std::list<glm::vec3>& vertices);

private: // Methodes privees pour le constructeur
    /**
     * @brief Calcule le barycentre d'une liste de sommets
     * @param vertices Liste de sommets definis par leurs coordonnees
     * @return Coordonnees 3D du barycentre
     */
    glm::vec3 __centroid(const std::list<glm::vec3>& vertices) const;

    /**
     * @brief Calcule la normale au plan defini par une liste de sommets
     * @param vertices Liste de sommets definis par leurs coordonnees
     * @return Coordonnees 3D de la normale au plan
     */
    glm::vec3 __normal(const std::list<glm::vec3>& vertices, const glm::vec3& o) const;

public: // Accesseurs
    /**
    * @brief Getter pour l'identifiant
    * @return Retourne l'identifiant du plan tangent
    */
    int get_id() const;

    /**
    * @brief Getter en lecture seule pour le centre
    * @return Retourne une reference du centre en lecture seule
    */
    const glm::vec3& get_center() const;

    /**
    * @brief Getter en lecture/ecriture pour le centre
    * @return Retourne une reference du centre en lecture/ecriture
    */
    glm::vec3& get_center();

    /**
    * @brief Getter en lecture seule pour la normale au plan
    * @return Retourne une reference de la normale en lecture seule
    */
    const glm::vec3& get_normal() const;

    /**
    * @brief Getter en lecture/ecriture pour la normale au plan
    * @return Retourne une reference de la normale en plan en lecture/ecriture
    */
    glm::vec3& get_normal();


public: // Calculus
    /**
    * @brief Calcul de la distance signée entre un point et le plan tangent
    * @param x Le point avec lequel on veut calculer la distance au plan tangent
    * @return Retourne un flottant représentant la distance entre x et le plan tangent
    */
    float signed_distance(const glm::vec3& x);

    /**
     * @brief Operateur ^ : mesure a quel point de plans tangent sont paralleles
     * @param tp Second plan tangent
     * @return Valeur proche de 0 si les plans sont presque paralleles
     */
    float operator^(const TangentPlane& tp) const;
};

#endif
