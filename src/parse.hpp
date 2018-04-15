/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include <string>
#include <sstream>

#include "Plane.hpp"
#include "Sphere.hpp"
#include "camera.hpp"
#include "Light.hpp"

class Parse
{

public:

	Parse() {}

	static glm::vec3 ParseVector(std::stringstream & Stream);

	static SceneObject * ParseSphere(std::stringstream & Stream);

	static SceneObject * ParsePlane(std::stringstream & Stream);

	static Camera * ParseCamera(std::stringstream & Stream);

	static Light * ParseLight(std::stringstream & Stream);

	static float ParseAmbient(std::stringstream & Stream);

	static float ParseDiffuse(std::stringstream & Stream);

};
