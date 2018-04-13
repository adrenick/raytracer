/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include <string>
#include <sstream>

//#include "SceneObject.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "camera.hpp"

//#include "ray.hpp"

/*struct vec3
{
	float x, y, z;
};*/

class Parse
{

public:

	Parse() {}

	//static glm::vec3 Vector(std::stringstream & Stream);
	static glm::vec3 ParseVector(std::stringstream & Stream);

	static SceneObject * ParseSphere(std::stringstream & Stream);

	static SceneObject * ParsePlane(std::stringstream & Stream);

	static Camera * ParseCamera(std::stringstream & Stream);

};
