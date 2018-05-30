/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "SceneObject.hpp"

class Plane : public SceneObject
{
public:

	glm::vec3 normal;
	float distance;

	float intersect(const ray & r);

	glm::vec3 computeNormal(glm::vec3 p);

	glm::vec3 computeCenter();

	void print();

		Plane(glm::vec3 n, float d, glm::vec3 c)
		{
			normal = n;
			distance = d;
			color = c;
			itransforms = glm::mat4(1.0f);
		}
		Plane()
		{
			normal = glm::vec3(0., 0., 0.);
			distance = 0.;
			color = glm::vec3(1., 1., 1.);
			itransforms = glm::mat4(1.0f);
		}	
};
