/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "raycast.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;
using namespace glm;


ray * raycast::createRay(Camera * camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0;

	vec3 origin = camera->location;
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));

	ray * r = new ray(origin, dir);

	return r;
}

void raycast::doRaycast(vector <SceneObject *> & scene, Camera * camera, int width, int height)
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

void raycast::pixelRay(Camera * camera, int width, int height, int x, int y)
{
	ray * r = createRay(camera, width, height, x, y);

	printPixelRay(x, y, r);
}

//void raycast::firstHit(ray r, vector <SceneObject *> scene, Camera * & camera, int width, int height, int x, int y)
float raycast::firstHit(ray * r, vector <SceneObject *> scene, bool print)
{

	//ray * r = createRay(camera, width, height, x, y);
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


	if (print){
		//printPixelRay(x, y, r);

		if (closestHit == -1){
			cout << "No Hit" << endl;
		} else {
			cout << "T = " << closestHit << endl;
			cout << "Object Type: " << scene[closestObjIndex]->type << endl;
			cout << "Color: " << scene[closestObjIndex]->color.x << " " << scene[closestObjIndex]->color.y << " " << scene[closestObjIndex]->color.z << endl;

		} 
	}

	return closestHit;
}

void raycast::pixelColor(vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, int width, int height, int x, int y)
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
		computeColor(origin+closestHit*dir, scene, closestObjIndex, camera, lights, true);
		/*std::cout << std::fixed << std::setprecision(4);
		cout << "Color: " << color.x << " " << color.y << " " << color.z << endl;
		std::cout << std::fixed << std::setprecision(4);*/

	} 
}

vec3 raycast::computeColor(vec3 hit, vector <SceneObject *> scene, int objIndex, Camera * camera, vector <Light *> lights, bool print)
{
	vec3 color = scene[objIndex]->color * scene[objIndex]->ambient;
	vec3 v = normalize(camera->location - hit);

	for (int i = 0; i < lights.size(); i++){
		
		vec3 l = normalize(lights[i]->location - hit);
		ray * lRay = new ray(hit, l);

		float lightHit = firstHit(lRay, scene, false);
		//bool shadow;
		
		/*if (lightHit < length(lights[i]->location - hit)){
			//shadow = true;
			cout << "shadow" << endl;
		} else {*/
			color += lights[i]->color*SceneObject::computeDiffuse(scene[objIndex], hit, l);
			//color += lights[i]->color*compute_specular(scene[objIndex], hit, normalize(dot(l, v)));
		//}
	}

	if (print) {
		uint r = round(clamp(color.x, 0.f, 1.f) * 255.f);
		uint g = round(clamp(color.y, 0.f, 1.f) * 255.f);
		uint b = round(clamp(color.z, 0.f, 1.f) * 255.f);
		cout << "Color: " << r << " " << g << " " << b << " " << endl;
	}

	color = vec3(clamp(color.x, 0.f, 1.f), clamp(color.y, 0.f, 1.f), clamp(color.z, 0.f, 1.f));

	return color;
}




