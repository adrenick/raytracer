/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class ray
{
public:
	ray() {}
	glm::vec3 origin;
	glm::vec3 direction;

};

#endif