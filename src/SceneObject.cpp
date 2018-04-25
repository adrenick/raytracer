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

	}

glm::vec3 SceneObject::computeDiffuse(SceneObject * obj, vec3 hit, vec3 l){
	
	vec3 n = obj->computeNormal(hit);
	//vec3 h = normalize(l + v);

	return (obj->diffuse)*(obj->color)*dot(n, l);

}

/*static vec3 SceneObject::computeSpecular(SceneObject * obj, vec3 hit, vec3 h){
	
	vec3 n = obj->computeNormal(hit);
	
	return obj->specular*dot(n, l);
	

}*/