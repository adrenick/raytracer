/* 	Alexa Drenick
	CSC 473
	Raytracer Project */
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ray.hpp"
#include <string>


class SceneObject
{

public:

	float ambient;
	float diffuse;
	std::string type;
	glm::vec3 color;

	virtual float intersect(const ray & r) = 0;

	virtual void print() = 0;

};

#endif
