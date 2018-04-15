/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#include "parse.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace glm;

void printScene(vector <SceneObject *> scene, Camera * & camera, vector <Light *> & lights);
void pixelRay(Camera * & camera, int width, int height, int x, int y);
void parseFile(string filename, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights);
void firstHit(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y);
void raycast(string filename, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights, int width, int height);

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
		parseFile(argv[2], scene, camera, lights);
		raycast(argv[2], scene, camera, lights, atoi(argv[3]), atoi(argv[4]));
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
		pixelRay(camera, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
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

	return 0;
}

ray * createRay(Camera * & camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0;

	vec3 origin = camera->location;
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));

	ray * r = new ray(origin, dir);

	return r;
}

void raycast(string filename, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights, int width, int height)
{
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int y = 0; y < size.y; ++ y)
	{
	    for (int x = 0; x < size.x; ++ x)
	    {
	    	unsigned int red, green, blue = 0;

			ray * r = createRay(camera, width, height, x, y);
			vec3 origin = r->origin;
			vec3 dir = r->direction;

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
				red = (unsigned int) std::round(0.0 * 255.f);
				green = (unsigned int) std::round(0.0 * 255.f);
				blue = (unsigned int) std::round(0.0 * 255.f);
			} else {
				auto sptr = dynamic_cast<Sphere*>(scene[closestObjIndex]);
				auto pptr = dynamic_cast<Plane*>(scene[closestObjIndex]);
				if (sptr != nullptr){
					red = (unsigned int) std::round(sptr->color.x * 255.f);
					green = (unsigned int) std::round(sptr->color.y * 255.f);
					blue = (unsigned int) std::round(sptr->color.z * 255.f);
				} else if (pptr != nullptr){
					red = (unsigned int) std::round(pptr->color.x * 255.f);
					green = (unsigned int) std::round(pptr->color.y * 255.f);
					blue = (unsigned int) std::round(pptr->color.z * 255.f);
				} else {
					red = (unsigned int) std::round(0.0 * 255.f);
					green = (unsigned int) std::round(0.0 * 255.f);
					blue = (unsigned int) std::round(0.0 * 255.f);
				}

			} 

	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
	    }
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;

}

void printPixelRay(int x, int y, ray * & r)
{
	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->origin.x << " " << r->origin.y << " " << r->origin.z;
	cout << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << std::endl;
}

void pixelRay(Camera * & camera, int width, int height, int x, int y)
{
	ray * r = createRay(camera, width, height, x, y);

	printPixelRay(x, y, r);
}

void firstHit(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y)
{

	ray * r = createRay(camera, width, height, x, y);
	vec3 origin = r->origin;
	vec3 dir = r->direction;

	printPixelRay(x, y, r);

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

}

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
