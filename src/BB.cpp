/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "BB.hpp"
#include <iostream>
using namespace std;

glm::vec3 BB::computeCenter() {
	
	// glm::vec3 center = glm::vec3((max.x+min.x)/2.f, (max.y+min.y)/2.f, (max.z+min.z)/2.f);
	
	// return glm::vec3(glm::inverse(itransforms)*glm::vec4(center, 0.f));

	return (max + min)/2.f;
}

// BB BB::getBoundingBox() {
	
// 	BB box;

// 	box.Reset(min);
// 	box.AddPoint(max);
// 	box.transformBox(inverse(itransforms));

// 	return box;
// }

float BB::intersect(const ray & r)
{
	//float tgmin = -std::numeric_limits<float>::max();
 	//float tgmax = std::numeric_limits<float>::max();

  	float txmin = (min.x - r.origin.x)/r.direction.x;
 	float txmax = (max.x - r.origin.x)/r.direction.x;

 	float tymin = (min.y - r.origin.y)/r.direction.y;
 	float tymax = (max.y - r.origin.y)/r.direction.y;

 	float tzmin = (min.z - r.origin.z)/r.direction.z;
 	float tzmax = (max.z - r.origin.z)/r.direction.z;

 	if (txmin > txmax) {
 		std::swap(txmin, txmax);
 	}
 	if (tymin > tymax) {
 		std::swap(tymin, tymax);
 	}
 	if (tzmin > tzmax) {
 		std::swap(tzmin, tzmax);
 	}
	if (r.direction.x == 0) {
		if ((r.origin.x < min.x) || (r.origin.x > max.x)) {
			return -1;
		} else {
			cerr << "*******" << endl;
			txmin = -std::numeric_limits<float>::max();
			txmax = std::numeric_limits<float>::max();
		}
	}
	if (r.direction.y == 0) {
		if ((r.origin.y < min.y) || (r.origin.y > max.y)) {
			return -1;
		} else {
			cerr << "*******" << endl;
			tymin = -std::numeric_limits<float>::max();
			tymax = std::numeric_limits<float>::max();
		}

	}
	if (r.direction.z == 0) {
		if ((r.origin.z < min.z) || (r.origin.z > max.z)) {
			return -1;
		} else {
			cerr << "*******" << endl;
			tzmin = -std::numeric_limits<float>::max();
			tzmax = std::numeric_limits<float>::max();
		}
	}


 	float smallestMax = glm::min(glm::min(txmax, tymax), tzmax);
 	float largestMin = glm::max(glm::max(txmin, tymin), tzmin);

 	if ((smallestMax < largestMin) || (smallestMax < 0)) {
 		return -1;
 	}

 	if (largestMin > 0) {
 		return largestMin;
 	} else {
 		return smallestMax;
 	}
} 


// void BB::print()
// {
// 	cout << "- Min: {" << min.x << " " << min.y << " " << min.z << "}" << endl;
// 	cout << "- Max: {" << max.x << " " << max.y << " " << max.z << "}" << endl;
// 	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << " " << filter << "}" << endl;
// 	cout << "- Material: \n  - Ambient: " << ambient << "\n  - Diffuse: " << diffuse << endl;
// 	cout << "  - Specular: " << specular << "\n  - Roughness: " << roughness << endl;
// 	cout << "  - Reflection: " << reflection << endl;
// 	cout << "  - Refraction: " << refraction << endl;
// 	cout << "  - IOR: " << ior << endl;
// 	cout << endl;
// }

// glm::vec3 BB::computeNormal(glm::vec3 p) {

// 	glm::vec4 normal;

// 	if (glm::epsilonEqual(p.x, min.x, 0.001f)) {
// 		normal =  glm::vec4(-1, 0, 0, 0);
// 	}
// 	else if (glm::epsilonEqual(p.x, max.x, 0.001f)) {
// 		normal =  glm::vec4(1, 0, 0, 0);
// 	}
// 	else if (glm::epsilonEqual(p.y, min.y, 0.001f)) {
// 		normal =  glm::vec4(0, -1, 0, 0);
// 	}
// 	else if (glm::epsilonEqual(p.y, max.y, 0.001f)) {
// 		normal = glm::vec4(0, 1, 0, 0);
// 	}
// 	else if (glm::epsilonEqual(p.z, min.z, 0.001f)) {
// 		normal = glm::vec4(0, 0, -1, 0);
// 	}
// 	else if (glm::epsilonEqual(p.z, max.z, 0.001f)) {
// 		normal = glm::vec4(0, 0, 1, 0);
// 	} else {
// 		std::cerr << "cannot compute box normal" << std::endl;
// 		cout << "point: " << p.x << " " << p.y << " " << p.z << endl;
// 		normal = glm::vec4(0, 0, 0, 0);
// 	}

// 	return glm::normalize(glm::vec3((glm::transpose(itransforms))*normal));

// }

void BB::Reset(glm::vec3 p) {
	min = max = p;
}
	
void BB::AddPoint(glm::vec3 p) {
	min.x = glm::min(min.x, p.x);
	min.y = glm::min(min.y, p.y);
	min.z = glm::min(min.z, p.z);

	max.x = glm::max(max.x, p.x);
	max.y = glm::max(max.y, p.y);
	max.z = glm::max(max.z, p.z);
}

void BB::AddBox(BB other) {
	AddPoint(other.min);
	AddPoint(other.max);
}

void BB::transformBox(glm::mat4 tforms) {
	glm::vec4 p1 = glm::vec4(min, 1.0f);
	glm::vec4 p2 = glm::vec4(max, 1.0f);  //front top right
	glm::vec4 p3 = glm::vec4(min.x, max.y, min.z, 1.0f); //back top left
	glm::vec4 p4 = glm::vec4(max.x, max.y, min.z, 1.0f); //back top right
	glm::vec4 p5 = glm::vec4(min.x, max.y, max.z, 1.0f); //front top left
	glm::vec4 p6 = glm::vec4(min.x, min.y, max.z, 1.0f); //front bottom left
	glm::vec4 p7 = glm::vec4(max.x, min.y, max.z, 1.0f); //front bottom right
	glm::vec4 p8 = glm::vec4(max.x, min.y, min.z, 1.0f); //back bottom right

	p1 = (tforms) * p1;
	p2 = (tforms) * p2;
	p3 = (tforms) * p3;
	p4 = (tforms) * p4;
	p5 = (tforms) * p5;
	p6 = (tforms) * p6;
	p7 = (tforms) * p7;
	p8 = (tforms) * p8;

	Reset(glm::vec3(p1));
	AddPoint(glm::vec3(p2));
	AddPoint(glm::vec3(p3));
	AddPoint(glm::vec3(p4));
	AddPoint(glm::vec3(p5));
	AddPoint(glm::vec3(p6));
	AddPoint(glm::vec3(p7));
	AddPoint(glm::vec3(p8));

}

// BB BB::calculateBBox(std::vector <SceneObject *> objs) {
// 	BB total= BB();
		
// 	for (uint i = 0; i < objs.size(); i++) {
// 		total.AddBox(objs[i]->getBoundingBox());
// 		// Box box = Box();
			
// 		// if (objs[i]->type == "Triangle") {
// 		// 	Triangle * obj = dynamic_cast<Triangle *> (objs[i]);

// 		// 	box.Reset(obj->A);
// 		// 	box.AddPoint(obj->B);
// 		// 	box.AddPoint(obj->C);

// 		// 	box.transformBox(obj->itransforms);

// 		// 	total.AddBox(box);
// 		// } else if (objs[i]->type == "Sphere"){
// 		// 	Sphere * obj = dynamic_cast<Sphere *> (objs[i]);

// 		// 	box.Reset(obj->origin - (obj->radius));
// 		// 	box.AddPoint(obj->origin + (obj->radius));

// 		// 	box.transformBox(obj->itransforms);

// 		// 	total.AddBox(box);
// 		// } else if (objs[i]->type == "Box") {
// 		// 	Box * obj = dynamic_cast<Box *> (objs[i]);

// 		// 	box = *obj;

// 		// 	box.transformBox(obj->itransforms);

// 		// 	total.AddBox(box);
// 		// } else {
// 		// 	std::cerr << "snakes on a plane" << std::endl;
// 		// }
// 	}

// 	return total;
// }