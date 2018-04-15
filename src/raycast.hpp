/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Camera.hpp"
#include "SceneObject.hpp"
#include <vector>

class raycast {

public:

	raycast() {}

	static ray * createRay(Camera * & camera, int width, int height, int x, int y);

	static void doRaycast(std::string filename, std::vector <SceneObject *> & scene, Camera * & camera, int width, int height);

	static void printPixelRay(int x, int y, ray * & r);

	static void pixelRay(Camera * & camera, int width, int height, int x, int y);

	static void firstHit(std::vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y);
};