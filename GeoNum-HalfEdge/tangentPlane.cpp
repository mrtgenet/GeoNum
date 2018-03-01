#include "tangentPlane.h"

// ------------------------------------------------------------------------------------
// Re-definition de l'operateur << (friend)

std::ostream& operator<<(std::ostream& os, const TangentPlane& plane){
	os << "Tangent Plane " << plane.get_id() << " : " << std::endl;
	os << "Centre : " << plane.get_center()[0] << " " << plane.get_center()[1] << " " << plane.get_center()[2] << std::endl;
	os << "Normale : " << plane.get_normal()[0] << " " << plane.get_normal()[1] << " " << plane.get_normal()[2] << std::endl;

	return os;
}

// ------------------------------------------------------------------------------------
// MACRO

int TangentPlane::NBR_OF_TANGENTPLANES = 0;

// ------------------------------------------------------------------------------------
// CONSTRUCTEURS

TangentPlane::TangentPlane(const std::list<glm::vec3>& vertices) :
    _id(TangentPlane::NBR_OF_TANGENTPLANES)
{
    TangentPlane::NBR_OF_TANGENTPLANES += 1;
    _center = __centroid(vertices);
    _normal = __normal(vertices, _center);
}

// ------------------------------------------------------------------------------------
// METHODES PRIVEES POUR LE CONSTRUCTEUR

glm::vec3 TangentPlane::__centroid(const std::list<glm::vec3>& vertices) const {
    glm::vec3 c;
    for (auto it : vertices) {
        c += it;
    }
    return (1.f/vertices.size())*c;
}

glm::vec3 TangentPlane::__normal(const std::list<glm::vec3>& vertices,
                               const glm::vec3& o) const
{
    glm::mat3 CV(0, 0, 0, 0, 0, 0, 0, 0, 0);
    // Matrice de covariance
    for (auto it : vertices) {
        glm::vec3 u = it - o;
        CV += glm::outerProduct(u, u);
    }

    Eigen::Matrix3f ECV;
    ECV <<  CV[0][0], CV[1][0], CV[2][0],
            CV[0][1], CV[1][1], CV[2][1],
            CV[0][2], CV[1][2], CV[2][2];

    Eigen::EigenSolver<Eigen::Matrix3f> sol(ECV);
    // Note : Comme la matrice de covariance est necessairement symétrique,
    // les valeurs/vecteurs propres n'ont pas de partie imaginaire

    return glm::vec3(
            sol.eigenvectors().col(1)[0].real(),
            sol.eigenvectors().col(1)[1].real(),
            sol.eigenvectors().col(1)[2].real());
}

// ------------------------------------------------------------------------------------
// ACCESSEURS

// id Getter
int TangentPlane::get_id() const{
	return _id;
}

// center Getter
const glm::vec3 &TangentPlane::get_center() const{
	return _center;
}

glm::vec3 &TangentPlane::get_center(){
	return _center;
}

// normal Getter

const glm::vec3 &TangentPlane::get_normal() const{
	return _normal;
}

glm::vec3 &TangentPlane::get_normal(){
	return _normal;
}

// ------------------------------------------------------------------------------------
// CALCULUS

float TangentPlane::signed_distance(const glm::vec3& x){
    return glm::dot(x - _center, _normal);
}

float TangentPlane::operator^(const TangentPlane& tp) const {
    return 1.f - std::fabs(glm::dot(_normal, tp.get_normal()));
}
