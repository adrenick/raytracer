/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Box.hpp"
#include <iostream>
using namespace std;

glm::vec3 Box::computeCenter() {
	return glm::vec3((max.x-min.x)/2.f, (max.y-min.y)/2.f, (max.z-min.z)/2.f);
}

float Box::intersect(const ray & r)
{

	float tgmin = std::numeric_limits<float>::min();
	float tgmax = std::numeric_limits<float>::max();

	float dx = r.direction.x;
	float dy = r.direction.y;
	float dz = r.direction.z;

	float txmin = (min.x - r.origin.x)/dx;
	float txmax = (max.x - r.origin.x)/dx;

	float tymin = (min.y - r.origin.y)/dy;
	float tymax = (max.y - r.origin.y)/dy;

	float tzmin = (min.z - r.origin.z)/dz;
	float tzmax = (max.z - r.origin.z)/dz;

	calcGminmax(txmin, txmax, tgmin, tgmax);
	calcGminmax(tymin, tymax, tgmin, tgmax);
	calcGminmax(tzmin, tzmax, tgmin, tgmax);

	if (dx == 0) {
		if ((r.origin.x < txmin) || (r.origin.x > txmax)) {
			return -1;
		}
	}
	if (dy == 0) {
		if ((r.origin.y < tymin) || (r.origin.y > tymax)) {
			return -1;
		}
	}
	if (dz == 0) {
		if ((r.origin.z < tzmin) || (r.origin.z > tzmax)) {
			return -1;
		}
	}

	if (tgmin > tgmax) {
		return -1;
	}
	if (tgmax < 0) {
		return -1;
	}

	if (tgmin > 0) {
		return tgmin;
	} else {
		return tgmax;
	}
	
} 

void Box::calcGminmax(float & min, float & max, float & gmin, float & gmax)
{
	if (min > max) {
		std::swap(min, max);
	}
	if (min > gmin) {
		gmin = min;
	}
	if (max < gmax) {
		gmax = max;
	}
}

void Box::print()
{
	cout << "- Min: {" << min.x << " " << min.y << " " << min.z << "}" << endl;
	cout << "- Max: {" << max.x << " " << max.y << " " << max.z << "}" << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << " " << filter << "}" << endl;
	cout << "- Material: \n  - Ambient: " << ambient << "\n  - Diffuse: " << diffuse << endl;
	cout << "  - Specular: " << specular << "\n  - Roughness: " << roughness << endl;
	cout << "  - Reflection: " << reflection << endl;
	cout << "  - Refraction: " << refraction << endl;
	cout << "  - IOR: " << ior << endl;
	cout << endl;
}

glm::vec3 Box::computeNormal(glm::vec3 p) {

	//glm::vec3 tp = glm::vec3(glm::inverse(itransforms) * glm::vec4(p, 0.f));

	glm::vec4 normal;

	if (glm::epsilonEqual(p.x, min.x, 0.0001f)) {
		normal =  glm::vec4(-1, 0, 0, 0);
	}
	if (glm::epsilonEqual(p.x, max.x, 0.0001f)) {
		normal =  glm::vec4(1, 0, 0, 0);
	}
	if (glm::epsilonEqual(p.y, min.y, 0.0001f)) {
		normal =  glm::vec4(0, -1, 0, 0);
	}
	if (glm::epsilonEqual(p.y, max.y, 0.0001f)) {
		normal = glm::vec4(0, 1, 0, 0);
	}
	if (glm::epsilonEqual(p.z, min.z, 0.0001f)) {
		normal = glm::vec4(0, 0, -1, 0);
	}
	if (glm::epsilonEqual(p.z, max.z, 0.0001f)) {
		normal = glm::vec4(0, 0, 1, 0);
	} else {
		std::cerr << "cannot compute box normal" << std::endl;
		normal = glm::vec4(0, 0, 0, 0);
		//std::cerr << "cannot compute box normal" << std::endl;
		//std::exit(-1);
	}

	//normal = itransforms * normal;
	//return normal;

	return glm::normalize(glm::vec3((glm::transpose(itransforms))*normal));

}