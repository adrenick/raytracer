/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Box.hpp"


class BoundingBox 
{
	
public:
	glm::vec3 min, max;
	
	BoundingBox() {

		min = glm::vec3(std::numeric_limits<float>::max());
		max = glm::vec3(std::numeric_limits<float>::min());
	}

	BoundingBox(glm::vec3 mi, glm::vec3 ma) {
		min = mi;
		max = ma;
	}

	void Reset(glm::vec3 p) {
		min = max = p;
	}
	
	void AddPoint(glm::vec3 p) {
		min.x = glm::min(min.x, p.x);
		min.y = glm::min(min.y, p.y);
		min.z = glm::min(min.z, p.z);

		max.x = glm::max(max.x, p.x);
		max.y = glm::max(max.y, p.y);
		max.z = glm::max(max.z, p.z);
	}

	void AddBox (BoundingBox other) {
		AddPoint(other.min);
		AddPoint(other.max);
	}

	static BoundingBox * calculateBBox(std::vector <SceneObject *> objs) {
		BoundingBox * total = new BoundingBox();
		
		for (uint i = 0; i < objs.size(); i++) {
			BoundingBox box = BoundingBox();
			
			if (objs[i]->type == "Sphere"){
				Sphere * obj = dynamic_cast<Sphere *> (objs[i]);
				box.Reset(obj->origin - glm::vec3(obj->radius));
				box.AddPoint(obj->origin + glm::vec3(obj->radius));
			} else if (objs[i]->type == "Triangle") {
				Triangle * obj = dynamic_cast<Triangle *> (objs[i]);
				box.Reset(obj->A);
				box.AddPoint(obj->B);
				box.AddPoint(obj->C);
			} else if (objs[i]->type == "Box") {
				Box * obj = dynamic_cast<Box *> (objs[i]);
				box.Reset(obj->min);
				box.AddPoint(obj->max);
			} else {
				std::cerr << "snakes on a plane" << std::endl;
			}
		}

		return total;

	}

};