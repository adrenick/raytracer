/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Camera.hpp"
#include <iostream>
using namespace std;

void Camera::print()
{
	cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << endl;
	cout << "- Up: {" << up.x << " " << up.y << " " << up.z << "}" << endl;
	cout << "- Right: {" << right.x << " " << right.y << " " << right.z << "}" << endl;
	cout << "- Look at: {" << look_at.x << " " << look_at.y << " " << look_at.z << "}" << endl;
	cout << endl;
}
