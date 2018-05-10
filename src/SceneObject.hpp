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
	float specular;
	float roughness;
	float ior;
	float reflection;
	float refraction;

	std::string type;
	glm::vec3 color;

	virtual float intersect(const ray & r) = 0;

	virtual void print() = 0;

	virtual glm::vec3 computeNormal(glm::vec3 hit) = 0;

	static void printScene(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights);

};

#endif
