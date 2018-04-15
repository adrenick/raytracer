/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "raycast.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;
using namespace glm;


ray * raycast::createRay(Camera * & camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0;

	vec3 origin = camera->location;
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));

	ray * r = new ray(origin, dir);

	return r;
}

void raycast::doRaycast(string filename, vector <SceneObject *> & scene, Camera * & camera, int width, int height)
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
				red = (unsigned int) std::round(scene[closestObjIndex]->color.x * 255.f);
				green = (unsigned int) std::round(scene[closestObjIndex]->color.y * 255.f);
				blue = (unsigned int) std::round(scene[closestObjIndex]->color.z * 255.f);
			} 

	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
	    }
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;

}

void raycast::printPixelRay(int x, int y, ray * & r)
{
	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r->origin.x << " " << r->origin.y << " " << r->origin.z;
	cout << "} -> {";
	cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << std::endl;
}

void raycast::pixelRay(Camera * & camera, int width, int height, int x, int y)
{
	ray * r = createRay(camera, width, height, x, y);

	printPixelRay(x, y, r);
}

void raycast::firstHit(vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y)
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
		cout << "Object Type: " << scene[closestObjIndex]->type << endl;
		/*auto sptr = dynamic_cast<Sphere*>(scene[closestObjIndex]);
		auto pptr = dynamic_cast<Plane*>(scene[closestObjIndex]);

		if (sptr != nullptr){
			cout << "Sphere" << endl;
			cout << "Color: " << sptr->color.x << " " << sptr->color.y << " " << sptr->color.z << endl;
		} else if (pptr != nullptr){
			cout << "Plane" << endl;
			cout << "Color: " << pptr->color.x << " " << pptr->color.y << " " << pptr->color.z << endl;
		}*/
		cout << "Color: " << scene[closestObjIndex]->color.x << " " << scene[closestObjIndex]->color.y << " " << scene[closestObjIndex]->color.z << endl;

	} 
}
