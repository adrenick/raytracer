/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "ray.hpp"

class Light {
	
public:
	glm::vec3 location;
	glm::vec3 color;

	void print(void);

		Light(glm::vec3 l, glm::vec3 c)
		{
			location = l;
			color = c;
		}
		Light()
		{
			location = glm::vec3(0., 0., 0.);
			color = glm::vec3(1., 1., 1.);
		}

};