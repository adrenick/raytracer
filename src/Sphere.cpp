/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Sphere.hpp"
using namespace std;
#include <iostream>

float Sphere::intersect(const ray & r)
{
	return 0.0;
}

void Sphere::print(void)
{
	cout << "- Type: Sphere" << endl;
	cout << "- Center: {" << origin.x << " " << origin.y << " " << origin.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
	cout << endl;
}