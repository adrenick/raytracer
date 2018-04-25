/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ray.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include <string>
#include <vector>
#include <iostream>

class SceneObject
{

public:

	float ambient;
	float diffuse;
	std::string type;
	glm::vec3 color;

	virtual float intersect(const ray & r) = 0;

	virtual void print() = 0;

	virtual glm::vec3 computeNormal(glm::vec3 hit) = 0;

	static void printScene(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights);
	/*{

		std::cout << "Camera: " << std::endl;
		(camera)->print();
		std::cout << "\n --- \n\n" << std::endl;

		std::cout << lights.size() << " light(s)\n" << std::endl;
		for (int i = 0; i < lights.size(); i++){
			std::cout << "Light[" << i << "]:" << std::endl;
			(lights[i])->print();
		}
		std::cout << "\n --- \n\n" << std::endl;

		std::cout << scene.size() << " object(s)\n" << std::endl;
		for (int i = 0; i < scene.size(); i++){
			std::cout << "Object[" << i << "]:" << std::endl;
			std::cout << "- Type: " << scene[i]->type << std::endl;

			scene[i]->print();
		}

	}*/

	static glm::vec3 computeDiffuse(SceneObject * obj, glm::vec3 hit, glm::vec3 l);

};

#endif
