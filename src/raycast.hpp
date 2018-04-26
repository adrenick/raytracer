/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Camera.hpp"
#include "SceneObject.hpp"
#include <vector>

class raycast {

public:

	raycast() {}

	static ray * createRay(Camera * camera, int width, int height, int x, int y);

	static void doRaycast(std::vector <SceneObject *> & scene, Camera * camera, int width, int height);

	static void printPixelRay(int x, int y, ray * & r);

	static void pixelRay(Camera * camera, int width, int height, int x, int y);

	//static void firstHit(std::vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y);
	static float firstHit(ray * r, std::vector <SceneObject *> scene, bool print);

	static void pixelColor(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, int width, int height, int x, int y);

	static glm::vec3 computeColor(glm::vec3 hit, std::vector <SceneObject *> scene, int objIndex, Camera * camera, std::vector <Light *> lights, bool print, ray * c);

	static void render(std::vector <SceneObject *> & scene, Camera * camera, std::vector <Light *> lights, int width, int height);
};
