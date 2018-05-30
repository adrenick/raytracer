/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "SceneObject.hpp"
#include <algorithm>

class Box : public SceneObject
{
public:

	glm::vec3 min;
	glm::vec3 max;

	float intersect(const ray & r);

	void print();

	void calcGminmax(float & min, float & max, float & gmin, float & gmax);

	glm::vec3 computeNormal(glm::vec3 p);

		Box(glm::vec3 mi, glm::vec3 ma, glm::vec3 c)
		{
			min = mi;
			max = ma;
			color = c;
			itransforms = glm::mat4(1.0f);
		}
		Box()
		{
			min = glm::vec3(0., 0., 0.);
			max = glm::vec3(0., 0., 0.);
			color = glm::vec3(1., 1., 1.);
			itransforms = glm::mat4(1.0f);
		}	
};