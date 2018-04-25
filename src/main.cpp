/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "parse.hpp"
#include "raycast.hpp"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace glm;

int main(int argc, char *argv[])
{
	stringstream s;
	vec3 v;
	vector <SceneObject *> scene;
	vector <Light *> lights;
	Camera * camera;

	std::cout << std::fixed << std::setprecision(4);

	if (argc < 2){
		cerr << "Unexpected usage" << endl;
		return 0;
	}

	string exec = argv[1];

	if (exec.compare("raycast") == 0){
		if (argc != 5){
			cerr << "Usage: ./raytrace raycast <input_filename> <width> <height>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::doRaycast(scene, camera, atoi(argv[3]), atoi(argv[4]));
	} else if (exec.compare("sceneinfo") == 0) {
		if (argc != 3){
			cerr << "Usage: ./raytrace sceneinfo <input_filename>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		SceneObject::printScene(scene, camera, lights);
	} else if (exec.compare("pixelray") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::pixelRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else if (exec.compare("firsthit") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace firsthit <input_filename> <width> <height> <x> <y>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);

		ray * pRay = raycast::createRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		raycast::printPixelRay(stoi(argv[3]), stoi(argv[4]), pRay);
		//raycast::firstHit(scene, camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		raycast::firstHit(pRay, scene, true);


	} else if (exec == "render") {
		if (argc < 5 || argc > 6) {
			cerr << "Usage: ./raytrace render <input_filename> <width> <height> [-altbrdf]" << endl;
			return -1;
		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::render(scene, camera, lights, atoi(argv[3]), atoi(argv[4]));

	} else if (exec == "pixelcolor"){
		if (argc < 7 || argc > 8){
			cerr << "Usage: ./raytrace pixelcolor <input_filename> <width> <height> <x> <y> [-altbrdf]" << endl;
			return -1;
		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::pixelColor(scene, camera, lights, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else {
		cerr << "Unexpected usage" << endl;
		return -1;
	}

	return 0;
}
