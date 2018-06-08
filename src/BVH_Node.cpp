/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "BVH_Node.hpp"

BVH_Node::BVH_Node(std::vector<SceneObject *> & objects)
{
	this->objects = objects;
	this->volume = calculateBBox(objects);
}

void BVH_Node::printTree() {
	if (children.empty()) {
		std::cout << "leaf: " << objects[0]->type << " min: " << volume.min.x << " " << volume.min.y << " " << volume.min.z << " max: " << volume.max.x << " " << volume.max.y << " " << volume.max.z << std::endl;

	} else {
		std::cout << "left: " << " min: " << volume.min.x << " " << volume.min.y << " " << volume.min.z << " max: " << volume.max.x << " " << volume.max.y << " " << volume.max.z << std::endl;
		children[0]->printTree();
		std::cout<< "right: " << " min: " << volume.min.x << " " << volume.min.y << " " << volume.min.z << " max: " << volume.max.x << " " << volume.max.y << " " << volume.max.z << std::endl;
		children[1]->printTree(); 
	}
}

void BVH_Node::buildTree(int axis) {

	if (objects.size() <= 1){
		return;
	}

	sortObjectsOnAxis(axis);

	std::vector< SceneObject *> left = std::vector< SceneObject *>(objects.begin(), objects.begin() + objects.size() / 2);

	children.push_back(new BVH_Node(left));

	std::vector< SceneObject *> right = std::vector< SceneObject *>(objects.begin() + objects.size() / 2, objects.end());

	children.push_back(new BVH_Node(right));

	objects.clear();

	for (uint i = 0; i < children.size(); i++){
		children[i]->buildTree((axis + 1) % 3);
	}



		// BVH_Node * newNode = new BVH_Node();
		
		// if (objs.size() <= 1) {
		// 	newNode->objects = objs;
		// 	newNode->volume = calculateBBox(objs);
		// 	return newNode;
		// }

		// std::vector <SceneObject *> sortedObjs = objs;
		// sortObjectsOnAxis(sortedObjs, axis);

		// // std::size_t const half = objs.size()/2;
		// // std::vector<SceneObject *> left(objs.begin(), objs.begin() + half);
		// // std::vector<SceneObject *> right(objs.begin() + half, objs.end());

		// // newNode.children.push_back(buildTree(left, (axis+1)%3));
		// // newNode.children.push_back(buildTree(right, (axis+1)%3));



		// newNode->children.push_back(buildTree(left_half(sortedObjs), (axis+1)%3));
		// newNode->children.push_back(buildTree(right_half(sortedObjs), (axis+1)%3));

		// newNode->volume = calculateBBox(objs);

		// return newNode;
}

BB BVH_Node::calculateBBox(std::vector <SceneObject *> objs) {

	BB total= BB();
		
	for (uint i = 0; i < objs.size(); i++) {
		total.AddBox(objs[i]->boundingBox);
			// Box box = Box();
				
			// if (objs[i]->type == "Triangle") {
			// 	Triangle * obj = dynamic_cast<Triangle *> (objs[i]);

			// 	box.Reset(obj->A);
			// 	box.AddPoint(obj->B);
			// 	box.AddPoint(obj->C);

			// 	box.transformBox(obj->itransforms);

			// 	total.AddBox(box);
			// } else if (objs[i]->type == "Sphere"){
			// 	Sphere * obj = dynamic_cast<Sphere *> (objs[i]);

			// 	box.Reset(obj->origin - (obj->radius));
			// 	box.AddPoint(obj->origin + (obj->radius));

			// 	box.transformBox(obj->itransforms);

			// 	total.AddBox(box);
			// } else if (objs[i]->type == "Box") {
			// 	Box * obj = dynamic_cast<Box *> (objs[i]);

			// 	box = *obj;

			// 	box.transformBox(obj->itransforms);

			// 	total.AddBox(box);
			// } else {
			// 	std::cerr << "snakes on a plane" << std::endl;
			// }
	}

	return total;
}
	

void BVH_Node::sortObjectsOnAxis(int axis) {
		
	if (axis == 0){
		auto compare = [] (SceneObject * o1, SceneObject * o2) {
			glm::vec3 center1 = o1->boundingBox.computeCenter();
			glm::vec3 center2 = o2->boundingBox.computeCenter();
			return (center1.x < center2.x);
		};
		std::sort(objects.begin(), objects.end(), compare);
	} else if (axis == 1) {
		auto compare = [] (SceneObject * o1, SceneObject * o2) {
			glm::vec3 center1 = o1->boundingBox.computeCenter();
			glm::vec3 center2 = o2->boundingBox.computeCenter();
			return (center1.y < center2.y);
		};
		std::sort(objects.begin(), objects.end(), compare);
	} else {
		auto compare = [] (SceneObject * o1, SceneObject * o2) {
			glm::vec3 center1 = o1->boundingBox.computeCenter();
			glm::vec3 center2 = o2->boundingBox.computeCenter();
			return (center1.z < center2.z);
		};
		std::sort(objects.begin(), objects.end(), compare);
	}

}

// static std::vector <SceneObject *> left_half(std::vector <SceneObject *> objs) {
// 	int half = objs.size()/2;
// 	std::vector <SceneObject *> left;

// 	for (uint i = 0; i < half; i++) {
// 		left.push_back(objs[i]);
// 	}

// 	return left;
// }

// 	static std::vector <SceneObject *> right_half(std::vector <SceneObject *> objs) {
// 		int half = objs.size()/2;
// 		std::vector <SceneObject *> right;

// 		for (uint i = half; i < objs.size(); i++) {
// 			right.push_back(objs[i]);
// 		}

// 		return right;
// 	}

