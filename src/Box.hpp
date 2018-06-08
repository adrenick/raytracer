/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef BOX_H
#define BOX_H

#include "SceneObject.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "BB.hpp"

class Box : public SceneObject
{
public:

	glm::vec3 min;
	glm::vec3 max;

	float intersect(const ray & r);

	void print();

	glm::vec3 computeNormal(glm::vec3 p);

	BB getBoundingBox();

		Box(glm::vec3 mi, glm::vec3 ma, glm::vec3 c)
		{
			min = mi;
			max = ma;
			color = c;
			itransforms = glm::mat4(1.0f);
			transforms = glm::mat4(1.0f);
		}
		Box()
		{

			min = glm::vec3(std::numeric_limits<float>::max());
			max = glm::vec3(-std::numeric_limits<float>::max());

			color = glm::vec3(1., 1., 1.);
			itransforms = glm::mat4(1.0f);
			transforms = glm::mat4(1.0f);
		}	
};

#endif