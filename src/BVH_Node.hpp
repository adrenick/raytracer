/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

//#include "BoundingBox.hpp"
#include "Box.hpp"
#include "SceneObject.hpp"


class BVH_Node 
{
	

public:
	Box volume;
	std::vector <BVH_Node> children;
	std::vector <SceneObject *> objects;

	// BVH_Node() {
	// 	children = NULL;
	// 	objects = NULL;
	// }

	void printTree() {
		if (children.empty()) {
			std::cout << "leaf: " << objects[0]->type << std::endl;

		} else {
			std::cout << "left: " << " min: " << volume.min.x << " " << volume.min.y << " " << volume.min.z << " max: " << volume.max.x << " " << volume.max.y << " " << volume.max.z << std::endl;
			children[0].printTree();
			std::cout<< "right: " << " min: " << volume.min.x << " " << volume.min.y << " " << volume.min.z << " max: " << volume.max.x << " " << volume.max.y << " " << volume.max.z << std::endl;
			children[1].printTree(); 
		}
	}

	static BVH_Node buildTree(std::vector <SceneObject *> objs, int axis) {

		BVH_Node newNode = BVH_Node();
		
		if (objs.size() <= 1) {
			newNode.objects = objs;
			//newNode.volume = Box::calculateBBox(objs);
			return newNode;
		}

		sortObjectsOnAxis(objs, axis);

		newNode.children.push_back(buildTree(left_half(objs), (axis+1)%3));
		newNode.children.push_back(buildTree(right_half(objs), (axis+1)%3));

		newNode.volume = Box::calculateBBox(objs);

		return newNode;
	}

	static void sortObjectsOnAxis(std::vector <SceneObject *> objs, int axis) {
		
		if (axis == 0){
			auto compare = [] (SceneObject * o1, SceneObject * o2) {
				glm::vec3 center1 = o1->computeCenter();
				glm::vec3 center2 = o2->computeCenter();
				return (center1.x < center2.x);
			};
			std::sort(objs.begin(), objs.end(), compare);
		} else if (axis == 1) {
			auto compare = [] (SceneObject * o1, SceneObject * o2) {
				glm::vec3 center1 = o1->computeCenter();
				glm::vec3 center2 = o2->computeCenter();
				return (center1.y < center2.y);
			};
			std::sort(objs.begin(), objs.end(), compare);
		} else {
			auto compare = [] (SceneObject * o1, SceneObject * o2) {
				glm::vec3 center1 = o1->computeCenter();
				glm::vec3 center2 = o2->computeCenter();
				return (center1.z < center2.z);
			};
			std::sort(objs.begin(), objs.end(), compare);
		}

	}

	static std::vector <SceneObject *> left_half(std::vector <SceneObject *> objs) {
		int half = objs.size()/2;
		std::vector <SceneObject *> left;

		for (uint i = 0; i < half; i++) {
			left.push_back(objs[i]);
		}

		return left;
	}

	static std::vector <SceneObject *> right_half(std::vector <SceneObject *> objs) {
		int half = objs.size()/2;
		std::vector <SceneObject *> right;

		for (uint i = half; i < objs.size(); i++) {
			right.push_back(objs[i]);
		}

		return right;
	}

};