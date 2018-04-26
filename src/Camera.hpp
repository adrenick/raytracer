/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"

class Camera {
	public:
		glm::vec3 location;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 look_at;

		void print();

		Camera(glm::vec3 l, glm::vec3 u, glm::vec3 r, glm::vec3 la)
		{
			location = l;
			up = u;
			right = r;
			look_at = la;
		}
		Camera()
		{
			location = glm::vec3(0., 0., 0.);
			up = glm::vec3(0., 0., 0.);
			right = glm::vec3(0., 0., 0.);
			look_at = glm::vec3(0., 0., 0.);

		}
};
#endif
