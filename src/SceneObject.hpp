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
	//SceneObject() {}
	//virtual ~SceneObject() {}
	float ambient;
	float diffuse;
	std::string type;

	virtual float intersect(const ray & r) = 0;

	virtual void print() = 0;
		//virtual ~SceneObject() {};
};

#endif
