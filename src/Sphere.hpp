/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "SceneObject.hpp"

//#include "ray.hpp"

class Sphere : public SceneObject
{
public:

	glm::vec3 origin;
	float radius;
	glm::vec3 color;

	float intersect(const ray & r);

	void print(void);

		Sphere(glm::vec3 o, float r, glm::vec3 c)
		{
			origin = o;
			radius = r;
			color = c;
		}
		Sphere()
		{
			origin = glm::vec3(0., 0., 0.);
			radius = 0.;
			color = glm::vec3(1., 1., 1.);
		}

		
};

