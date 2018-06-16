/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Light.hpp"
#include <iostream>
using namespace std;

void Light::print()
{
	cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;

	if (isAreaLight) {
		cout << "- Axis 1: {" << axis1.x << " " << axis1.y << " " << axis1.z << "}" << endl;
		cout << "- Axis 2: {" << axis2.x << " " << axis2.y << " " << axis2.z << "}" << endl;
		cout << "- Rows: " << rows << endl;
		cout << "- Columns: " << columns << endl;
	}

	cout << endl;
}

glm::vec3 Light::getSample(int i, int j)
{
	if (rows == 1 && columns == 1) {
		return location;
	} else {
		return (location - axis1 / 2.f - axis2 / 2.f) + (float)i * (axis1 / (float)rows) + (float)j * (axis2 / (float)columns);
	}
}
