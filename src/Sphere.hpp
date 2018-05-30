/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.hpp"

class Sphere : public SceneObject
{
public:

	glm::vec3 origin;
	float radius;

	float intersect(const ray & r);

	glm::vec3 computeCenter();

	void print();

	glm::vec3 computeNormal(glm::vec3 p);

		Sphere(glm::vec3 o, float r, glm::vec3 c)
		{
			origin = o;
			radius = r;
			color = c;
			itransforms = glm::mat4(1.0f);
		}
		Sphere()
		{
			origin = glm::vec3(0., 0., 0.);
			radius = 0.;
			color = glm::vec3(1., 1., 1.);
			itransforms = glm::mat4(1.0f);
		}	
};


#endif
