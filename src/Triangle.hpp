/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "SceneObject.hpp"

class Triangle : public SceneObject
{
public:

	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 C;

	float intersect(const ray & r);

	void print();

	glm::vec3 computeNormal(glm::vec3 p);

		Triangle(glm::vec3 pa, glm::vec3 pb, glm::vec3 pc, glm::vec3 c)
		{
			A = pa;
			B = pb;
			C = pc;

			color = c;

			itransforms = glm::mat4(1.0f);
		}

		Triangle()
		{
			A = glm::vec3(0., 0., 0.);
			B = glm::vec3(0., 0., 0.);
			C = glm::vec3(0., 0., 0.);

			color = glm::vec3(1., 1., 1.);

			itransforms = glm::mat4(1.0f);
		}
};
