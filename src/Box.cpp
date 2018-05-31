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
	else if (glm::epsilonEqual(p.x, max.x, 0.0001f)) {
		normal =  glm::vec4(1, 0, 0, 0);
	}
	else if (glm::epsilonEqual(p.y, min.y, 0.0001f)) {
		normal =  glm::vec4(0, -1, 0, 0);
	}
	else if (glm::epsilonEqual(p.y, max.y, 0.0001f)) {
		normal = glm::vec4(0, 1, 0, 0);
	}
	else if (glm::epsilonEqual(p.z, min.z, 0.0001f)) {
		normal = glm::vec4(0, 0, -1, 0);
	}
	else if (glm::epsilonEqual(p.z, max.z, 0.0001f)) {
		normal = glm::vec4(0, 0, 1, 0);
	} else {
		std::cerr << "cannot compute box normal" << std::endl;
		cout << "point: " << p.x << " " << p.y << " " << p.z << endl;
		normal = glm::vec4(0, 0, 0, 0);
		//std::cerr << "cannot compute box normal" << std::endl;
		//std::exit(-1);
	}

	//normal = itransforms * normal;
	//return normal;

	return glm::normalize(glm::vec3((glm::transpose(itransforms))*normal));

}

void Box::Reset(glm::vec3 p) {
	min = max = p;
}
	
void Box::AddPoint(glm::vec3 p) {
	min.x = glm::min(min.x, p.x);
	min.y = glm::min(min.y, p.y);
	min.z = glm::min(min.z, p.z);

	max.x = glm::max(max.x, p.x);
	max.y = glm::max(max.y, p.y);
	max.z = glm::max(max.z, p.z);
}

void Box::AddBox(Box other) {
	AddPoint(other.min);
	AddPoint(other.max);
}

void Box::transformBox(glm::mat4 itforms) {
	glm::vec4 p1 = glm::vec4(min, 1.0f);
	glm::vec4 p2 = glm::vec4(max, 1.0f);  //front top right
	glm::vec4 p3 = glm::vec4(min.x, max.y, min.z, 1.0f); //back top left
	glm::vec4 p4 = glm::vec4(max.x, max.y, min.z, 1.0f); //back top right
	glm::vec4 p5 = glm::vec4(min.x, max.y, max.z, 1.0f); //front top left
	glm::vec4 p6 = glm::vec4(min.x, min.y, max.z, 1.0f); //front bottom left
	glm::vec4 p7 = glm::vec4(max.x, min.y, max.z, 1.0f); //front bottom right
	glm::vec4 p8 = glm::vec4(max.x, min.y, min.z, 1.0f); //back bottom right

	p1 = itforms * p1;
	p2 = itforms * p2;
	p3 = itforms * p3;
	p4 = itforms * p4;
	p5 = itforms * p5;
	p6 = itforms * p6;
	p7 = itforms * p7;
	p8 = itforms * p8;

	Reset(glm::vec3(p1));
	AddPoint(glm::vec3(p2));
	AddPoint(glm::vec3(p3));
	AddPoint(glm::vec3(p4));
	AddPoint(glm::vec3(p5));
	AddPoint(glm::vec3(p6));
	AddPoint(glm::vec3(p7));
	AddPoint(glm::vec3(p8));

}

Box Box::calculateBBox(std::vector <SceneObject *> objs) {
	Box total = Box();// = new Box();
		
	for (uint i = 0; i < objs.size(); i++) {
		Box box;// = Box();
			
		if (objs[i]->type == "Sphere"){
			Sphere * obj = dynamic_cast<Sphere *> (objs[i]);
			//box = Box(obj->origin - glm::vec3(obj->radius), obj->origin - glm::vec3(obj->radius));
			box.Reset(obj->origin - glm::vec3(obj->radius));
			box.AddPoint(obj->origin + glm::vec3(obj->radius));
			//box.itransforms = obj->itransforms;
			box.transformBox(obj->itransforms);
			total.AddBox(box);
			//total->AddBox(box);
		} else if (objs[i]->type == "Triangle") {
			Triangle * obj = dynamic_cast<Triangle *> (objs[i]);
			box.Reset(obj->A);
			box.AddPoint(obj->B);
			box.AddPoint(obj->C);
			//box = Box(glm::min(glm::min(obj->A, obj->B), obj->C), )
			//box.itransforms = obj->itransforms;
			box.transformBox(obj->itransforms);
			total.AddBox(box);
		} else if (objs[i]->type == "Box") {
			Box * obj = dynamic_cast<Box *> (objs[i]);
			//box.Reset(obj->min);
			//box.AddPoint(obj->max);
			box = *obj;
			//box.itransforms = obj->itransforms;
			box.transformBox(obj->itransforms);
			total.AddBox(box);
		} else {
			std::cerr << "snakes on a plane" << std::endl;
		}
	}

	return total;
}
