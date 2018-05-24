/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include <iostream>
#include "Camera.hpp"

class ray
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

	ray(glm::vec3 o, glm::vec3 d) 
	{
		origin = o;
		direction = d;
	}
	ray ()
	{
		origin = glm::vec3(0);
		direction = glm::vec3(0);
	}
};

#endif
