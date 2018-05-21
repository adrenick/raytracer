/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "SceneObject.hpp"

using namespace glm;

void SceneObject::printScene(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights)
{

	std::cout << "Camera: " << std::endl;
	(camera)->print();
	std::cout << "\n --- \n\n" << std::endl;

	std::cout << lights.size() << " light(s)\n" << std::endl;
	for (uint i = 0; i < lights.size(); i++){
		std::cout << "Light[" << i << "]:" << std::endl;
		(lights[i])->print();
	}
	std::cout << "\n --- \n\n" << std::endl;

	std::cout << scene.size() << " object(s)\n" << std::endl;
	for (uint i = 0; i < scene.size(); i++){
		std::cout << "Object[" << i << "]:" << std::endl;
		std::cout << "- Type: " << scene[i]->type << std::endl;

		scene[i]->print();
	}

}

