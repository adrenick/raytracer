/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "Box.hpp"
#include "SceneObject.hpp"

class BVH_Node 
{
	

public:
	BB volume;
	std::vector <BVH_Node *> children;
	std::vector <SceneObject *> objects;

	BVH_Node(std::vector<SceneObject *> & objects);

	void printTree(const std::string & name);

	void buildTree(int axis);

	static BB calculateBBox(std::vector <SceneObject *> objs);

	void sortObjectsOnAxis(int axis);
};

#endif