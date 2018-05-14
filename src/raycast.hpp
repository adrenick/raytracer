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

	static float firstHit(ray * r, std::vector <SceneObject *> scene, bool print, int index);

	static void pixelColor(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, int width, int height, int x, int y);

	static glm::vec3 computeColor(glm::vec3 hit, std::vector <SceneObject *> scene, int objIndex, glm::vec3 normal, Camera * camera, std::vector <Light *> lights, bool print, ray * c,  bool altbrdf, glm::vec3 & a, glm::vec3 & d, glm::vec3 & s);

	static glm::vec3 getColorForRay(ray * r, std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, bool altbrdf, int numRecurse, bool print);

	static glm::vec3 printRays(ray * r, std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, bool altbrdf, int numRecurse);

	static void getAmbDiffSpec(glm::vec3 hit, std::vector <SceneObject *> scene, int objIndex, glm::vec3 normal, Camera * camera, std::vector <Light *> lights, ray * c, glm::vec3 & a, glm::vec3 & d, glm::vec3 & s);

	static void render(std::vector <SceneObject *> & scene, Camera * camera, std::vector <Light *> lights, int width, int height, bool altbrdf);

	static float calcG(glm::vec3 x, glm::vec3 h, glm::vec3 n, float r);

	static float calcD(glm::vec3 n, glm::vec3 h, float alpha);
};
