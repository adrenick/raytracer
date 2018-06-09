/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef BB_H
#define BB_H

// #include "SceneObject.hpp"
#include "ray.hpp"

class BB
{
public:

	glm::vec3 min;
	glm::vec3 max;

	float intersect(const ray & r);

	void print();

	glm::vec3 computeCenter();

	void Reset(glm::vec3 p);
	
	void AddPoint(glm::vec3 p);

	void AddBox(BB other);

	void transformBox(glm::mat4 tforms);

		BB(glm::vec3 mi, glm::vec3 ma)
		{
			min = mi;
			max = ma;
		}

		BB()
		{
			min = glm::vec3(std::numeric_limits<float>::max());
			max = glm::vec3(-std::numeric_limits<float>::max());
		}	
};

#endif