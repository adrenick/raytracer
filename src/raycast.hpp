/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Camera.hpp"
#include "SceneObject.hpp"
#include "BVH_Node.hpp"
#include <vector>

class raycast {

public:

	raycast() {}

	static ray * createRay(Camera * camera, int width, int height, int x, int y);

	static ray * createSuperSampledRay(Camera * camera, int width, int height, int x, int y, int m, int n, int ssN);

	static void doRaycast(std::vector <SceneObject *> & scene, Camera * camera, int width, int height);

	static void printPixelRay(int x, int y, ray * & r);

	static void pixelRay(Camera * camera, int width, int height, int x, int y);

	static float firstHit(ray * r, std::vector <SceneObject *> scene, bool print, int index);

	static void pixelColor(std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, int width, int height, int x, int y);

	static glm::vec3 computeColor(glm::vec3 hit, std::vector <SceneObject *> scene, int objIndex, glm::vec3 normal, Camera * camera, std::vector <Light *> lights, bool print, ray * c,  bool altbrdf, glm::vec3 & a, glm::vec3 & d, glm::vec3 & s);

	static SceneObject * getIntersect(ray * r, std::vector <SceneObject *> scene, float & closestHit, int & closestObjIndex, ray & tRay, bool sds);

	static float recurseDownTree(ray * r, BVH_Node * tree, SceneObject * obj);

	static glm::vec3 getColorForRay(ray * r, std::vector <SceneObject *> scene, Camera * camera, std::vector <Light *> lights, bool altbrdf, int numRecurse, bool print, bool fresnel, bool beers, bool sds, float & distanceHit);

	static void render(std::vector <SceneObject *> & scene, Camera * camera, std::vector <Light *> lights, int width, int height, bool altbrdf, bool beers, bool fresnel, bool sds, int ssN);

	static float schlicks_approx(float n, glm::vec3 normal, glm::vec3 d);

	static float calcG(glm::vec3 x, glm::vec3 h, glm::vec3 n, float r);

	static float calcD(glm::vec3 n, glm::vec3 h, float alpha);
};
