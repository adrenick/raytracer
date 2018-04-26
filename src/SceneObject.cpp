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

glm::vec3 SceneObject::computeDiffuse(SceneObject * obj, vec3 hit, vec3 l, vec3 n){
	
	//vec3 n = obj->computeNormal(hit);
	//vec3 h = normalize(l + v);

	//return (obj->diffuse)*dot(n, l);
	return (obj->diffuse)*(obj->color)*dot(n, l);

}

glm::vec3 SceneObject::computeSpecular(SceneObject * obj, vec3 hit, vec3 h, vec3 n){

	
	//std::cout << obj->specular << std::endl;
	if (obj->specular == 0.f){
		//std::cout << "specular = 0" << std::endl;
		//std::cout << obj->specular << std::endl;
		return vec3(0, 0, 0);
		//return 0;
	} else {
		vec3 spec = (obj->specular)*(obj->color)*pow(dot(h, n), pow(obj->roughness, 2.f));
		//vec3 spec = (obj->specular)*(obj->color)*pow(dot(h, n), (1/obj->roughness));
		//vec3 spec = (obj->specular)*(obj->color)*pow(dot(h, n), obj->roughness);
		//std::cout << spec.x << ", " << spec.y << ", " << spec.z << std::endl;
		//float spec = (obj->specular)*pow(dot(h, n), (1/obj->roughness));
		return spec;
	}
}

/*static vec3 SceneObject::computeSpecular(SceneObject * obj, vec3 hit, vec3 h){
	
	vec3 n = obj->computeNormal(hit);
	
	return obj->specular*dot(n, l);
	

}*/