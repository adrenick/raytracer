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
		//if (scene[i]->itransforms != glm::mat4(1)) {
		std::cout << "- InvTransform:\n";
			mat4 M = scene[i]->itransforms;
		std::cout << "                " << M[0][0] << " " << M[1][0] << " " << M[2][0] << " " << M[3][0] << "\n";
		std::cout << "                " << M[0][1] << " " << M[1][1] << " " << M[2][1] << " " << M[3][1] << "\n";
		std::cout << "                " << M[0][2] << " " << M[1][2] << " " << M[2][2] << " " << M[3][2] << "\n";
		std::cout << "                " << M[0][3] << " " << M[1][3] << " " << M[2][3] << " " << M[3][3] << "\n";

		// 	printf("\tvec4(%2.9f, %2.9f, %2.9f, %2.9f)\n", static_cast<double>(M[0][0]), static_cast<double>(M[0][1]), static_cast<double>(M[0][2]), static_cast<double>(M[0][3]));
		// 	printf("\tvec4(%2.9f, %2.9f, %2.9f, %2.9f)\n", static_cast<double>(M[1][0]), static_cast<double>(M[1][1]), static_cast<double>(M[1][2]), static_cast<double>(M[1][3]));
		// 	printf("\tvec4(%2.9f, %2.9f, %2.9f, %2.9f)\n", static_cast<double>(M[2][0]), static_cast<double>(M[2][1]), static_cast<double>(M[2][2]), static_cast<double>(M[2][3]));
		// 	printf("\tvec4(%2.9f, %2.9f, %2.9f, %2.9f))\n\n", static_cast<double>(M[3][0]), static_cast<double>(M[3][1]), static_cast<double>(M[3][2]), static_cast<double>(M[3][3]));
		// 
		//}

		scene[i]->print();
	}

}

