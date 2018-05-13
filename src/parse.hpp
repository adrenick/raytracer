/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "Plane.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Triangle.hpp"
#include "Light.hpp"

class Parse
{

public:

	Parse() {}

	static glm::vec3 ParseVector(std::stringstream & Stream);

	static SceneObject * ParseSphere(std::stringstream & Stream);

	static SceneObject * ParsePlane(std::stringstream & Stream);

	static SceneObject * ParseTriangle(std::stringstream & Stream);

	static Camera * ParseCamera(std::stringstream & Stream);

	static Light * ParseLight(std::stringstream & Stream);

	static float ParseAmbient(std::stringstream & Stream);

	static float ParseDiffuse(std::stringstream & Stream);

	static float ParseSpecular(std::stringstream & Stream);

	static float ParseRoughness(std::stringstream & Stream);

	static float ParseReflection(std::stringstream & Stream);

	static float ParseRefraction(std::stringstream & Stream);

	static glm::vec4 ParseColor(std::stringstream & Stream);

	static float ParseIOR(std::stringstream & Stream);

	static void ParseFinish(std::stringstream & Stream, float & a, float & d, float & s, float & r, float & ior, float & ref, float & refrac);

	static void parseString(std::stringstream & stream, std::vector <SceneObject *> & scene, Camera * & camera, std::vector <Light *> & lights);

	static void parseFile(std::string filename, std::vector <SceneObject *> &scene, Camera * & camera, std::vector <Light *> & lights);
};
