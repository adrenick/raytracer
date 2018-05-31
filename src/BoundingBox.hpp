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

	void transformBox (BoundingBox box, glm::mat4 itforms) {
		glm::vec4 p1 = glm::vec4(box.min, 1.0f);
		glm::vec4 p2 = glm::vec4(box.max, 1.0f);  //front top right
		glm::vec4 p3 = glm::vec4(box.min.x, box.max.y, box.min.z, 1.0f); //back top left
		glm::vec4 p4 = glm::vec4(box.max.x, box.max.y, box.min.z, 1.0f); //back top right
		glm::vec4 p5 = glm::vec4(box.min.x, box.max.y, box.max.z, 1.0f); //front top left
		glm::vec4 p6 = glm::vec4(box.min.x, box.min.y, box.max.z, 1.0f); //front bottom left
		glm::vec4 p7 = glm::vec4(box.max.x, box.min.y, box.max.z, 1.0f); //front bottom right
		glm::vec4 p8 = glm::vec4(box.max.x, box.min.y, box.min.z, 1.0f); //back bottom right
	}

	static BoundingBox * calculateBBox(std::vector <SceneObject *> objs) {
		BoundingBox * total = new BoundingBox();
		
		for (uint i = 0; i < objs.size(); i++) {
			BoundingBox box = BoundingBox();
			
			if (objs[i]->type == "Sphere"){
				Sphere * obj = dynamic_cast<Sphere *> (objs[i]);
				box.Reset(obj->origin - glm::vec3(obj->radius));
				box.AddPoint(obj->origin + glm::vec3(obj->radius));
				//total->AddBox(transformBox(box, obj->itransforms));
				total->AddBox(box);
			} else if (objs[i]->type == "Triangle") {
				Triangle * obj = dynamic_cast<Triangle *> (objs[i]);
				box.Reset(obj->A);
				box.AddPoint(obj->B);
				box.AddPoint(obj->C);
				total->AddBox(box);
			} else if (objs[i]->type == "Box") {
				Box * obj = dynamic_cast<Box *> (objs[i]);
				box.Reset(obj->min);
				box.AddPoint(obj->max);
				total->AddBox(box);
			} else {
				std::cerr << "snakes on a plane" << std::endl;
			}
		}

		return total;

	}

};