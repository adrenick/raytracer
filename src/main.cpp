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

	if (exec == "raycast"){
		if (argc != 5){
			cerr << "Usage: ./raytrace raycast <input_filename> <width> <height>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::doRaycast(scene, camera, atoi(argv[3]), atoi(argv[4]));
	} else if (exec == "sceneinfo") {
		if (argc != 3){
			cerr << "Usage: ./raytrace sceneinfo <input_filename>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		SceneObject::printScene(scene, camera, lights);
	} else if (exec == "pixelray") {
		if (argc != 7){
			cerr << "Usage: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::pixelRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else if (exec == "firsthit") {
		if (argc != 7){
			cerr << "Usage: ./raytrace firsthit <input_filename> <width> <height> <x> <y>" << endl;
			return -1;

		}
		Parse::parseFile(argv[2], scene, camera, lights);

		ray * pRay = raycast::createRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		raycast::firstHit(pRay, scene, true, -1);


	} else if (exec == "render") {
		if (argc < 5 || argc > 6) {
			cerr << "Usage: ./raytrace render <input_filename> <width> <height> [-altbrdf]" << endl;
			return -1;
		}
		bool altbrdf = false;
		bool beers = false;
		bool fresnel = false;
		int ssN = 0;
		if (argc == 6){
			string opt = argv[5];
			if (opt == "-altbrdf"){
				altbrdf = true;
			} else if (opt == "-fresnel") {
				fresnel = true;
			} else if (opt == "-beers") {
				beers = true;
			} else {
				int pos = opt.find("ss=");
				if (pos != std::string::npos){
					ssN = (opt[4]) - '0';
				} else {
					cerr << "Unrecognized option: " << opt << endl;
					return -1;
				}
			}
		}
		
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::render(scene, camera, lights, atoi(argv[3]), atoi(argv[4]), altbrdf, beers, fresnel, ssN);

	} else if (exec == "pixelcolor"){
		if (argc < 7 || argc > 8){
			cerr << "Usage: ./raytrace pixelcolor <input_filename> <width> <height> <x> <y> [-altbrdf]" << endl;
			return -1;
		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::pixelColor(scene, camera, lights, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else if (exec == "printrays") {
		if (argc < 6) {
			cerr << "Usage: ./raytrace printrays <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}
		Parse::parseFile(argv[2], scene, camera, lights);
		cout << "Pixel: [" << argv[5] << ", " << argv[6] << "]" << endl;
		cout << "----\n   Iteration type: Primary" << endl;
		ray * r = raycast::createRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
		float f;
		vec3 color = raycast::getColorForRay(r, scene, camera, lights, false, 0, true, false, false, f);
		cout << "Color: (" << (uint)round(color.x*255) << ", " << (uint)round(color.y*255) << ", " << (uint)round(color.z*255) << ")" << endl;
	} else {
		cerr << "Unexpected usage" << endl;
		return -1;
	}

	return 0;
}
