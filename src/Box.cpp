/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Box.hpp"
#include <iostream>
using namespace std;

BB Box::getBoundingBox() {
	
	BB box;

	box.Reset(min);
	box.AddPoint(max);
	box.transformBox(transforms);

	return box;
}

float Box::intersect(const ray & r)
{

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


void Box::print()
{
	cout << "- Min: {" << min.x << " " << min.y << " " << min.z << "}" << endl;
	cout << "- Max: {" << max.x << " " << max.y << " " << max.z << "}" << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << " " << filter << "}" << endl;
	cout << "- Material: \n  - Ambient: " << ambient << "\n  - Diffuse: " << diffuse << endl;
	cout << "  - Specular: " << specular << "\n  - Roughness: " << roughness << endl;
	cout << "  - Reflection: " << reflection << endl;
	cout << "  - Refraction: " << refraction << endl;
	cout << "  - IOR: " << ior << endl;
	cout << endl;
}

glm::vec3 Box::computeNormal(glm::vec3 p) {

	glm::vec4 normal;

	if (glm::epsilonEqual(p.x, min.x, 0.001f)) {
		normal =  glm::vec4(-1, 0, 0, 0);
	}
	else if (glm::epsilonEqual(p.x, max.x, 0.001f)) {
		normal =  glm::vec4(1, 0, 0, 0);
	}
	else if (glm::epsilonEqual(p.y, min.y, 0.001f)) {
		normal =  glm::vec4(0, -1, 0, 0);
	}
	else if (glm::epsilonEqual(p.y, max.y, 0.001f)) {
		normal = glm::vec4(0, 1, 0, 0);
	}
	else if (glm::epsilonEqual(p.z, min.z, 0.001f)) {
		normal = glm::vec4(0, 0, -1, 0);
	}
	else if (glm::epsilonEqual(p.z, max.z, 0.001f)) {
		normal = glm::vec4(0, 0, 1, 0);
	} else {
		std::cerr << "cannot compute box normal" << std::endl;
		cout << "point: " << p.x << " " << p.y << " " << p.z << endl;
		normal = glm::vec4(0, 0, 0, 0);
	}

	return glm::normalize(glm::vec3((glm::transpose(itransforms))*normal));

}
