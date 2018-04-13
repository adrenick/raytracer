/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Sphere.hpp"
using namespace std;
#include <iostream>

float Sphere::intersect(const ray & r)
{
	float A = dot(r.direction, r.direction);
	float B = 2*dot((r.origin-origin), r.direction);
	float C = (dot((r.origin-origin), (r.origin-origin)) - pow(radius, 2));

	float disc = sqrt(pow(B, 2)-4*A*C);
	//float solution = -1;

	if (disc > 0){
		//cout << "2 solutions" << endl;
		if ((-B-disc)/(2*A) < 0){
			return (-B+disc)/(2*A);
		} else {
			return (-B-disc)/(2*A);
		}

		//cout << (-B+disc)/(2*A) << endl;
		//cout << (-B-disc)/(2*A) << endl;
		//solution = max((-B+disc)/(2*A), (-B-disc)/(2*A));
		//cout << solution << endl;
	} else if (disc < 0) {
		//cout << "no solutions" << endl;
		return -1;
	} else {
		//cout << "1 solution" << endl;
		//solution = -B/(2*A);
		return -B/(2*A);
		//cout << solution << endl;
	}

	//return -1;
}

void Sphere::print(void)
{
	cout << "- Type: Sphere" << endl;
	cout << "- Center: {" << origin.x << " " << origin.y << " " << origin.z << "}" << endl;
	cout << "- Radius: " << radius << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
	cout << endl;
}