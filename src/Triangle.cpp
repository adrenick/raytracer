/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "Triangle.hpp"
#include <iostream>
using namespace std;

BB Triangle::getBoundingBox() {
	BB box;

	box.Reset(A);
	box.AddPoint(B);
	box.AddPoint(C);

	box.transformBox(transforms);

	return box;
	
}

float Triangle::intersect(const ray & r)
{
	float a = A.x - B.x;
	float b = A.y - B.y;
	float c = A.z - B.z;
	float d = A.x - C.x;
	float e = A.y - C.y;
	float f = A.z - C.z;
	float g = r.direction.x;
	float h = r.direction.y;
	float i = r.direction.z;

	float j = A.x - r.origin.x;
	float k = A.y - r.origin.y;
	float l = A.z - r.origin.z;

	float ei_hf = e*i - h*f;
	float gf_di = g*f - d*i;
	float dh_eg = d*h - e*g;
	float ak_jb = a*k - j*b;
	float jc_al = j*c - a*l;
	float bl_kc = b*l - k*c;

	float detA = a*ei_hf + b*gf_di + c*dh_eg;

	float beta = (j*ei_hf + k*gf_di + l*dh_eg)/detA;
	float gamma = (i*ak_jb + h*jc_al + g*bl_kc)/detA;
	float alpha = 1.0f - beta - gamma;

	if ((alpha >= 0) && (beta >= 0) && (gamma >= 0)) {
		float t = (-d*bl_kc-e*jc_al-f*ak_jb)/detA;
		if (t >= 0){
			return t;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
} 

void Triangle::print()
{
	cout << "- Point A: {" << A.x << " " << A.y << " " << A.z << "}" << endl;
	cout << "- Point B: {" << B.x << " " << B.y << " " << B.z << "}" << endl;
	cout << "- Point C: {" << C.x << " " << C.y << " " << C.z << "}" << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << " " << filter << "}" << endl;
	cout << "- Material: \n  - Ambient: " << ambient << "\n  - Diffuse: " << diffuse << endl;
	cout << "  - Specular: " << specular << "\n  - Roughness: " << roughness << endl;
	cout << "  - Reflection: " << reflection << endl;
	cout << "  - Refraction: " << refraction << endl;
	cout << "  - IOR: " << ior << endl;
	cout << endl;
}

glm::vec3 Triangle::computeNormal(glm::vec3 p) {
	
	float BAx = B.x - A.x;
	float BAy = B.y - A.y;
	float BAz = B.z - A.z;

	float CAx = C.x - A.x;
	float CAy = C.y - A.y;
	float CAz = C.z - A.z;

	float xNorm = BAy*CAz - BAz*CAy;
	float yNorm = BAz*CAx - BAx*CAz;
	float zNorm = BAx*CAy - BAy*CAx;

	glm::vec4 norm = glm::vec4(xNorm, yNorm, zNorm, 0.f);

	return glm::normalize(glm::vec3((glm::transpose(itransforms))*norm));

}
