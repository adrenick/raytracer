/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "parse.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace glm;

void printScene(vector <SceneObject *> scene, Camera * & camera);
void parseFile(string filename, vector <SceneObject *> & scene, Camera * & camera);

int main(int argc, char *argv[])
{
	stringstream s;
	vec3 v;
	vector <SceneObject *> scene;
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
	} else if (exec.compare("sceneinfo") == 0) {
		if (argc != 3){
			cerr << "Usage: ./raytrace sceneinfo <input_filename>" << endl;
			return 0;

		}
		parseFile(argv[2], scene, camera);
		printScene(scene, camera);
	} else if (exec.compare("pixelray") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
	} else if (exec.compare("firsthit") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace raycast <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
	} else {
		cerr << "Unexpected usage" << endl;
		return 0;
	}

	/*s.str("<-3.0, 1.0, 2.0>");
	v = Parse::ParseVector(s);
	cout << v.x << " " << v.y << " " << v.z << endl;

	s.str("{ <-5, 3, 0>, 1.1 pigment { color rgb <0.12, 0.34, 0.56>} finish {ambient 0.2 diffuse 0.4}}");
	
	s.ignore(3, '{');
	scene.push_back(Parse::ParseSphere(s));

	s.str("{<1, 0, 0>, -5 pigment {color rgb <0.15, 0.2, 0.8>} finish {ambient 0.4 diffuse 0.8}}");
	
	s.ignore(3, '{');
	scene.push_back(Parse::ParsePlane(s));*/

	//printScene(scene);

	return 0;
}

void parseString(std::stringstream & stream, vector <SceneObject *> & scene, Camera * & camera)
{
	std::string token;
	std::string trash;
	//token << contents;

	while(!stream.eof())
	{
		//token << stream;
		stream >> token;
		//cout << token << endl;

		if (token.compare("sphere") == 0){
			//cout << "** TOKEN SPHERE**" << endl;
			stream.ignore(3, '{');
			scene.push_back(Parse::ParseSphere(stream));
		} else if (token.compare("plane") == 0){
			//cout << "** TOKEN PLANE**" << endl;
			stream.ignore(3, '{');
			scene.push_back(Parse::ParsePlane(stream));
		} //else if (token.find("\\") == nopos) {
		else if (token.substr(0, 2) == "//") { //NOT THROWING OUT COMMENTS
			//cout << "FOUND COMMENT" << endl;
			getline(stream, trash);
		} else if (token.compare("camera") == 0){
			stream.ignore(3, '{');
			camera = Parse::ParseCamera(stream);
		}
	}
	//printScene(scene);
}

void parseFile(string filename, vector <SceneObject *> &scene, Camera * & camera)
{
	//cout << "hello" << endl;
	stringstream s;

	ifstream ifs(filename);
	string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	//cout << content << endl;

	s.str(content);

	parseString(s, scene, camera);

}

void printScene(vector <SceneObject *> scene, Camera * & camera)
{
	//cout << "printScene" << endl;

	cout << "Camera: " << endl;
	(camera)->print();
	cout << "\n --- \n\n" << endl;

	cout << "1 light(s)\n" << endl;
	cout << "\n --- \n\n" << endl;

	cout << scene.size() << " object(s)\n" << endl;
	for (int i = 0; i < scene.size(); i++){
		cout << "Object[" << i << "]:" << endl;
		auto sptr = dynamic_cast<Sphere*>(scene[i]);
		auto pptr = dynamic_cast<Plane*>(scene[i]);
		if (sptr != nullptr){
			(sptr)->print();
		} else if (pptr != nullptr){
			(pptr)->print();
		}
	}

}
