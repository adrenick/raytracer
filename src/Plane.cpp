/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Plane.hpp"
using namespace std;
#include <iostream>

float Plane::intersect(const ray & r)
{
	//cout << "intersect in plane" << endl;

	float top = distance-dot(r.origin, normal);
	float bottom = dot(r.direction, normal);

	if (bottom == 0){
		return -1;
	} else {
		return top/bottom;
	}
	
}

void Plane::print()
{
	cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
	cout << "- Distance: " << distance << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
	cout << "- Material: \n  - Ambient: " << ambient << "\n  - Diffuse: " << diffuse << endl;
	cout << "  - Reflection: " << reflection << endl;
	cout << endl;
}

glm::vec3 Plane::computeNormal(glm::vec3 p) {
	return normal;
}
