/* 	Alexa Drenick
	CSC 473
	Raytracer Project */
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ray.hpp"


class SceneObject
{

public:
	//SceneObject() {}
	//virtual ~SceneObject() {}
	float ambient;
	float diffuse;

	virtual float intersect(const ray & r) = 0;
		//virtual ~SceneObject() {};
};

#endif
