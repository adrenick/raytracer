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

void printScene(vector <SceneObject *> scene, Camera * & camera, vector <Light *> & lights);
void pixelRay(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y);
void parseFile(string filename, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights);
void firstHit(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y);

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
	} else if (exec.compare("sceneinfo") == 0) {
		if (argc != 3){
			cerr << "Usage: ./raytrace sceneinfo <input_filename>" << endl;
			return 0;

		}
		parseFile(argv[2], scene, camera, lights);
		printScene(scene, camera, lights);
	} else if (exec.compare("pixelray") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
		parseFile(argv[2], scene, camera, lights);
		pixelRay(scene, camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
	} else if (exec.compare("firsthit") == 0) {
		if (argc != 7){
			cerr << "Usage: ./raytrace raycast <input_filename> <width> <height> <x> <y>" << endl;
			return 0;

		}
		parseFile(argv[2], scene, camera, lights);
		firstHit(scene, camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
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

void pixelRay(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0; //IS THIS RIGHT

	//vec3 origin = vec3((float)Us, (float)Vs, Ws); //what is z of ray origin
	vec3 origin = camera->location;
	//vec3 dir = dot(Us, camera->right)+dot(Vs, camera->up)+dot(Ws, camera->look_at);
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));
	

	//vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * camera->look_at));

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << origin.x << " " << origin.y << " " << origin.z;
	cout << "} -> {";
	cout << dir.x << " " << dir.y << " " << dir.z << "}" << endl;
}

void firstHit(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0; //IS THIS RIGHT

	//vec3 origin = vec3((float)Us, (float)Vs, Ws); //what is z of ray origin
	vec3 origin = camera->location;
	//vec3 dir = dot(Us, camera->right)+dot(Vs, camera->up)+dot(Ws, camera->look_at);
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));
	//vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * camera->look_at));

	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << origin.x << " " << origin.y << " " << origin.z;
	cout << "} -> {";
	cout << dir.x << " " << dir.y << " " << dir.z << "}" << endl;

	float closestHit = -1;
	float closestObjIndex = -1;
	for (int i = 0; i < scene.size(); i++){
		float hit = scene[i]->intersect(ray(origin, dir));
		if ((hit > 0) && (closestHit == -1)){
			closestHit = hit;
			closestObjIndex = i;
		}
		if ((hit > 0) && (hit < closestHit)){
			closestHit = hit;
			closestObjIndex = i;
		}
	}

	if (closestHit == -1){
		cout << "No Hit" << endl;
	} else {
		cout << "T = " << closestHit << endl;
		cout << "Object Type: ";
		auto sptr = dynamic_cast<Sphere*>(scene[closestObjIndex]);
		auto pptr = dynamic_cast<Plane*>(scene[closestObjIndex]);
		if (sptr != nullptr){
			cout << "Sphere" << endl;
			cout << "Color: " << sptr->color.x << " " << sptr->color.y << " " << sptr->color.z << endl;
		} else if (pptr != nullptr){
			cout << "Plane" << endl;
			cout << "Color: " << pptr->color.x << " " << pptr->color.y << " " << pptr->color.z << endl;
		}

	} 
}

void parseString(std::stringstream & stream, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights)
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
		} else if (token.compare("light_source") == 0){
			//cout << "LIGHT FOUND" << endl;
			stream.ignore(3, '{');
			lights.push_back(Parse::ParseLight(stream));
		}
	}
	//printScene(scene);
}

void parseFile(string filename, vector <SceneObject *> &scene, Camera * & camera, vector <Light *> & lights)
{
	//cout << "hello" << endl;
	stringstream s;

	ifstream ifs(filename);

	if (!ifs){
		cerr << "File not found " << endl;
		exit(-1);
	}

	string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	//cout << content << endl;

	s.str(content);

	parseString(s, scene, camera, lights);

}

void printScene(vector <SceneObject *> scene, Camera * & camera, vector <Light *> & lights)
{
	//cout << "printScene" << endl;

	cout << "Camera: " << endl;
	(camera)->print();
	cout << "\n --- \n\n" << endl;

	cout << lights.size() << " light(s)\n" << endl;
	for (int i = 0; i < lights.size(); i++){
		cout << "Object[" << i << "]:" << endl;
		(lights[i])->print();
	}
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
