/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Sphere.hpp"
#include <iostream>
using namespace std;

float Sphere::intersect(const ray & r)
{
	float A = dot(r.direction, r.direction);
	float B = 2*dot((r.origin-origin), r.direction);
	float C = (dot((r.origin-origin), (r.origin-origin)) - pow(radius, 2));

	float disc = sqrt(pow(B, 2)-4*A*C);

	if (disc > 0){
		if ((-B-disc)/(2*A) < 0){
			return (-B+disc)/(2*A);
		} else {
			return (-B-disc)/(2*A);
		}
	} else if (disc < 0) {
		return -1;
	} else if (disc == 0){
		return -B/(2*A);
	}
	return -1;

} 

void Sphere::print(void)
{
	cout << "- Center: {" << origin.x << " " << origin.y << " " << origin.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
	cout << "- Material: \n  -Ambient: " << ambient << "\n  -Diffuse: " << diffuse << endl;
	cout << endl;
}
