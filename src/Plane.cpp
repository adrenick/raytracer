/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Plane.hpp"
using namespace std;
#include <iostream>

float Plane::intersect(const ray & r)
{
	float top = distance-dot(r.origin, normal);
	float bottom = dot(r.direction, normal);

	//float solution = -1;
	if (bottom == 0){
		//cout << "no intersection" << endl;
		return -1;
	} else {
		//cout << "intersection" << endl;
		return top/bottom;
		//cout << solution << endl;
	}

	//return solution;
}

void Plane::print(void)
{
	cout << "- Type: Plane" << endl;
	cout << "- Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
	cout << "- Distance: " << distance << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
	cout << endl;
}

