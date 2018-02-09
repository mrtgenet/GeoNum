#include "tangentPlane.h"

// ------------------------------------------------------------------------------------
// Re-definition de l'operateur << (friend)

std::ostream& operator<<(std::ostream& os, const tangentPlane& plane){
	os << "Tangent Plane " << plane.get_id() << " : " << std::endl;
	os << "Centre : " << plane.get_center()[0] << " " << plane.get_center()[1] << " " << plane.get_center()[2] << std::endl;
	os << "Normale : " << plane.get_normal()[0] << " " << plane.get_normal()[1] << " " << plane.get_normal()[2] << std::endl;

	return os;
}

// ------------------------------------------------------------------------------------
// MACRO

int tangentPlane::NBR_OF_TANGENTPLANES = 0;

// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

tangentPlane::tangentPlane(glm::vec3 center, glm::vec3 normal) :
	_id(tangentPlane::NBR_OF_TANGENTPLANES),
	_center(center),
	_normal(normal)
{
	tangentPlane::NBR_OF_TANGENTPLANES += 1;
}

// ------------------------------------------------------------------------------------
// ACCESSEURS

// id Getter
int tangentPlane::get_id() const{
	return _id;
}

// center Getter
const glm::vec3 &tangentPlane::get_center() const{
	return _center;
}

glm::vec3 &tangentPlane::get_center(){
	return _center;
}

// normal Getter

const glm::vec3 &tangentPlane::get_normal() const{
	return _normal;
}

glm::vec3 &tangentPlane::get_normal(){
	return _normal;
}

// ------------------------------------------------------------------------------------
// CALCULUS

float tangentPlane::signed_distance(const glm::vec3& x){
	float dist = std::numeric_limits<float>::infinity();

	glm::vec3 avg(x[0] - this->get_center()[0],
								x[1] - this->get_center()[1],
								x[2] - this-> get_center()[2]);

	dist = glm::dot(avg,this->get_normal());


	if(dist == std::numeric_limits<float>::infinity()){
		fprintf(stderr,"signed distance calculus error at id : %d \n", this->get_id());
	}

	return dist;
}
