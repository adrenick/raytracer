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

	// void calcGminmax(float & min, float & max, float & gmin, float & gmax);

	// glm::vec3 computeNormal(glm::vec3 p);

	void Reset(glm::vec3 p);
	
	void AddPoint(glm::vec3 p);

	void AddBox(BB other);

	void transformBox(glm::mat4 tforms);

	//static BB calculateBBox(std::vector <SceneObject *> objs);

		BB(glm::vec3 mi, glm::vec3 ma)
		{
			min = mi;
			max = ma;
			// color = c;
			// itransforms = glm::mat4(1.0f);
		}
		BB()
		{

			min = glm::vec3(std::numeric_limits<float>::max());
			max = glm::vec3(-std::numeric_limits<float>::max());

			// color = glm::vec3(1., 1., 1.);
			// itransforms = glm::mat4(1.0f);
		}	
};

#endif