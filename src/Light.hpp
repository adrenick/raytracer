/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef LIGHT_H
#define LIGHT_H

#include "ray.hpp"

class Light {
	
public:
	glm::vec3 location;
	glm::vec3 color;

	bool isAreaLight;
	glm::vec3 axis1;
	glm::vec3 axis2;
	int rows;
	int columns;

	glm::vec3 getSample(int i, int j);

	void print();

		Light(glm::vec3 l, glm::vec3 c)
		{
			location = l;
			color = c;
			rows = 1;
			columns = 1;
		}
		Light()
		{
			location = glm::vec3(0., 0., 0.);
			color = glm::vec3(1., 1., 1.);
			rows = 1;
			columns = 1;
		}

};
#endif
