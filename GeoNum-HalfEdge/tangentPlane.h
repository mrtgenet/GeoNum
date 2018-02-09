#ifndef TANGENT_PLANE_H
#define TANGENT_PLANE_H

#include <iostream>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>


/**
* @brief Représentation d'un plan tangeant par un point et un vecteur normal
*        Chaque point du nuage aura un plan tangent
*/

class tangentPlane
{
	friend std::ostream& operator<<(std::ostream& os, const tangentPlane& plane);

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
	* @brief Constructeur par défaut, initialise le centre et le vecteur normal
	* @param center Centre du plan tangent
	* @param normal Vecteur normal du plan tangent
	*/
	tangentPlane(glm::vec3 center, glm::vec3 normal);

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

};

#endif
