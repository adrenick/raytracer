/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "BB.hpp"
#include <iostream>
using namespace std;

glm::vec3 BB::computeCenter() {
	
	return (max + min)/2.f;
}

float BB::intersect(const ray & r)
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
