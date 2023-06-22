#include "glmPrintUtils.hpp"

std::ostream &operator<<(std::ostream &o, glm::vec3 &v)
{
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (o);
}
std::ostream &operator<<(std::ostream &o, glm::vec4 &v)
{
	o << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return (o);
}