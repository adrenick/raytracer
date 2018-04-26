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
	cout << endl;
}
