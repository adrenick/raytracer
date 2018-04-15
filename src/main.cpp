/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "parse.hpp"
#include "raycast.hpp"

#include <iostream>
//#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace glm;

void printScene(vector <SceneObject *> scene, Camera * & camera, vector <Light *> & lights);
//void parseFile(string filename, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights);

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
			return 0;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::doRaycast(argv[2], scene, camera, atoi(argv[3]), atoi(argv[4]));
	} else if (exec.compare("sceneinfo") == 0) {
		if (argc != 3){
			cerr << "Usage: ./raytrace sceneinfo <input_filename>" << endl;
			return 0;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		printScene(scene, camera, lights);
	} else if (exec.compare("pixelray") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::pixelRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else if (exec.compare("firsthit") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace raycast <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
		Parse::parseFile(argv[2], scene, camera, lights);
		raycast::firstHit(scene, camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else {
		cerr << "Unexpected usage" << endl;
		return 0;
	}

	return 0;
}

/*void parseString(std::stringstream & stream, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights)
{
	std::string token;
	std::string trash;

	while(!stream.eof())
	{
		stream >> token;

		if (token.compare("sphere") == 0){
			stream.ignore(3, '{');
			scene.push_back(Parse::ParseSphere(stream));
		} else if (token.compare("plane") == 0){
			stream.ignore(3, '{');
			scene.push_back(Parse::ParsePlane(stream));
		} 
		else if (token.substr(0, 2) == "//") { 
			getline(stream, trash);
		} else if (token.compare("camera") == 0){
			stream.ignore(3, '{');
			camera = Parse::ParseCamera(stream);
		} else if (token.compare("light_source") == 0){
			stream.ignore(3, '{');
			lights.push_back(Parse::ParseLight(stream));
		}
	}
}

void parseFile(string filename, vector <SceneObject *> &scene, Camera * & camera, vector <Light *> & lights)
{
	stringstream s;

	ifstream ifs(filename);

	if (!ifs){
		cerr << "File not found " << endl;
		exit(-1);
	}

	string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

	s.str(content);

	parseString(s, scene, camera, lights);

}*/

void printScene(vector <SceneObject *> scene, Camera * & camera, vector <Light *> & lights)
{

	cout << "Camera: " << endl;
	(camera)->print();
	cout << "\n --- \n\n" << endl;

	cout << lights.size() << " light(s)\n" << endl;
	for (int i = 0; i < lights.size(); i++){
		cout << "Light[" << i << "]:" << endl;
		(lights[i])->print();
	}
	cout << "\n --- \n\n" << endl;

	cout << scene.size() << " object(s)\n" << endl;
	for (int i = 0; i < scene.size(); i++){
		cout << "Object[" << i << "]:" << endl;
		cout << "- Type: " << scene[i]->type << endl;

		scene[i]->print();
	}

}
