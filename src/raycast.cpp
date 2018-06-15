/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "raycast.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;
using namespace glm;


ray raycast::createRay(Camera * camera, int width, int height, int x, int y)
{
	float Us = (((float)x + 0.5)/(float)width)-0.5;
	float Vs = (((float)y + 0.5)/(float)height)-0.5;
	float Ws = -1.0;

	vec3 origin = camera->location;
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));

	ray r = ray(origin, dir);

	return r;
}

ray raycast::createSuperSampledRay(Camera * camera, int width, int height, int x, int y, int m, int n, int ssN)
{
	float Us = (-0.5f)+(((float)x+((m+0.5f)/ssN))/width);
	float Vs = (-0.5f)+(((float)y+((n+0.5f)/ssN))/height);
	float Ws = -1.0;

	vec3 origin = camera->location;
	vec3 dir = normalize((Us * camera->right)+(Vs * camera->up)+(Ws * normalize(camera->location-camera->look_at)));

	ray r = ray(origin, dir);

	return r;
}

void raycast::doRaycast(vector <SceneObject *> & scene, Camera * camera, int width, int height)
{
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);

	//unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	unsigned char data [size.x * size.y * numChannels];

	for (int y = 0; y < size.y; ++ y)
	{
	    for (int x = 0; x < size.x; ++ x)
	    {
	    	unsigned int red, green, blue = 0;

			ray r = createRay(camera, width, height, x, y);

			float closestHit = -1;
			float closestObjIndex = -1;
			for (uint i = 0; i < scene.size(); i++){
				float hit = scene[i]->intersect(r);
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
	//delete[] data;

}

void raycast::printPixelRay(int x, int y, ray r)
{
	cout << "Pixel: [" << x << ", " << y << "] Ray: {";
	cout << r.origin.x << " " << r.origin.y << " " << r.origin.z;
	cout << "} -> {";
	cout << r.direction.x << " " << r.direction.y << " " << r.direction.z << "}" << std::endl;
}

void raycast::pixelRay(Camera * camera, int width, int height, int x, int y)
{
	ray r = createRay(camera, width, height, x, y);

	printPixelRay(x, y, r);
}


void raycast::pixelColor(vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, int width, int height, int x, int y)
{

	ray r = createRay(camera, width, height, x, y);

	printPixelRay(x, y, r);

	float closestHit = -1;
	float closestObjIndex = -1;
	for (uint i = 0; i < scene.size(); i++){
		float hit = scene[i]->intersect(r);
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
		vec3 a, d, s;
		vec3 P = r.origin+closestHit*r.direction;
		vec3 normal = scene[closestObjIndex]->computeNormal(P);
		BVH_Node * nulltree = nullptr;
		vector <SceneObject *> nullplanes;

		computeColor(P, nulltree, scene, nullplanes, scene[closestObjIndex], normal, camera, lights, true, false, a, d, s, false, 0);
	} 
}

float raycast::firstHit(ray r, vector <SceneObject *> scene, bool print)
{

	float closestHit = -1;
	int closestObjIndex = -1;
	for (uint i = 0; i < scene.size(); i++){

		mat4 M = scene[i]->itransforms;
		vec4 Oprime = M*vec4(r.origin, 1.0);
		vec4 Dprime = M*vec4(r.direction, 0.0);

		ray tr = ray(vec3(Oprime), vec3(Dprime));

		float hit = scene[i]->intersect(tr);

		if ((hit > 0) && (closestHit == -1)){
			closestHit = hit;
			closestObjIndex = i;
		}
		if ((hit > 0) && (hit < closestHit)){
			closestHit = hit;
			closestObjIndex = i;
		}
	}
	//Internal shading below
	/*if (closestObjIndex == index){
		return -1;
	}*/

	if (print){
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

vec3 raycast::cookTorrence(SceneObject * obj, vec3 n, vec3 l, vec3 v, vec3 h)
{

	vec3 kd = obj->diffuse*obj->color;
	vec3 ks = obj->specular*obj->color;

	float alpha = pow(obj->roughness, 2);

	float D = calcD(n, h, alpha);

	float G = (calcG(l, h, n, alpha))*(calcG(v, h, n, alpha));

	float Fo = (pow(obj->ior - 1, 2))/(pow(obj->ior + 1, 2));
	float F = Fo + (1 - Fo)*(pow(1-clamp(dot(v, h), 0.f, 1.f), 5));

	vec3 rs = ks*((D*G*F)/(4*clamp(dot(n, v), 0.f, 1.f))); 

	return (kd*(clamp(dot(n, l), 0.f, 1.f))+rs);
}

void raycast::blinnPhong(SceneObject * obj, vec3 n, vec3 l, vec3 h, vec3 & d, vec3 & s) {
	
	vec3 kd = obj->diffuse*obj->color;
	vec3 ks = obj->specular*obj->color;

	float alpha = 2/(pow(obj->roughness, 2))-2;

	vec3 diff = kd*clamp(dot(n, l), 0.f, 1.f);
	d = diff;

	vec3 spec = ks*(pow(clamp(dot(h, n), 0.f, 1.f), alpha));
	s = spec;

}

bool raycast::inShadow(SceneObject * & obj, float & hitPt, vec3 hit, vec3 lightPosition, BVH_Node * tree, vector <SceneObject *> scene, vector <SceneObject *> planes, bool sds)
{
	float lightHit = -1;
	ray tRay = ray(vec3(0), vec3(0));

	vec3 l = normalize(lightPosition - hit);
	ray lRay = ray(hit + (l*0.001f), l); 

	obj = getIntersect(lRay, tree, scene, lightHit, tRay, sds, planes);

	if (lightHit > 0) {
		if (lightHit <= length(lightPosition - hit)) {
			hitPt = lightHit;
			return true;
		}
	}

	return false;
}

vec3 raycast::computeColor(vec3 hit, BVH_Node * tree, vector <SceneObject *> scene, vector <SceneObject *> planes, SceneObject * obj, vec3 normal, Camera * camera, vector <Light *> lights, bool print, bool altbrdf, vec3 & a, vec3 & d, vec3 & s, bool sds, int gi)
{
	vec3 amb = obj->color * obj->ambient;
	
	if (gi > 0) {
		amb = a;
	}
	vec3 color = amb;

	vec3 v = normalize(camera->location - hit);

	for (uint n = 0; n < lights.size(); n++){
		vec3 l = normalize(lights[n]->location - hit);
		vec3 h = normalize(l+v);

		for (uint i = 0; i < lights[n]->rows; i++) {
			for (uint j = 0; j < lights[n]->columns; j++){
				vec3 sample = lights[n]->getSample(i, j);
				l = normalize(sample - hit);
				float weight = 1.0 / (lights[n]->rows * lights[n]->columns);

				SceneObject * hitObj;
				float hitPt = -1;

				if (!inShadow(hitObj, hitPt, hit, sample, tree, scene, planes, sds)) {
					if (altbrdf) {
						color += (lights[n]->color)*cookTorrence(obj, normal, l, v, h);
					} else {
						blinnPhong(obj, normal, l, h, d, s);
						color += (lights[n]->color)*d*weight;
						color += (lights[n]->color)*s*weight;
					}

				} else {
					if (hitObj->filter > 0 && hitObj != obj){

						vec3 P = hit + l*hitPt;

						vec3 refNormal = hitObj->computeNormal(P);

						float dDotn = dot(l, refNormal);
						float n1 = 1.0f;
						float n2 = hitObj->ior;
						float ratio = (n1/n2);
						
						vec3 refracDir = ratio*(l-dDotn*refNormal)-refNormal*(float)(sqrt(1-(pow(ratio, 2)*(1-pow(dDotn, 2)))));
						ray entering = ray(P+0.001f*refracDir, refracDir);

						entering = ray(P+0.001f, l);

						float exitHit = hitObj->intersect(entering);

						vec3 exitPt = P + exitHit*entering.direction;

						ray r = ray(lights[n]->location, normalize(exitPt - lights[n]->location));
						float i = hitObj->intersect(r);

						float dif = abs(dot(r.direction, hitObj->computeNormal(lights[n]->location + r.direction*i)));

						color += color*dif*hitObj->ior*weight; 
					}
				}
			}
		}	
	}

	if (print) {
		uint r = round(clamp(color.x, 0.f, 1.f) * 255.f);
		uint g = round(clamp(color.y, 0.f, 1.f) * 255.f);
		uint b = round(clamp(color.z, 0.f, 1.f) * 255.f);
		cout << "BRDF: Blinn-Phong" << endl;
		cout << "Color: (" << r << ", " << g << ", " << b << ")" << endl;
	}

	return color;
}

float raycast::calcD(vec3 n, vec3 h, float alpha)
{
	int chi;
	float ndoth = clamp(dot(n, h), 0.f, 1.f);
	float alpha2 = pow(alpha, 2);

	if (ndoth > 0){
		chi = 1;
	} else {
		chi = 0;
	}

	const float pi = 4*atan(1);
	float bottom = pi*pow(pow(ndoth, 2)*(alpha2-1)+1, 2);

	return chi*(alpha2/bottom);
}

float raycast::calcG(vec3 x, vec3 h, vec3 n, float r)
{
	int chi;

	if ((clamp(dot(x, h), 0.f, 1.f))/(clamp(dot(x, n), 0.f, 1.f)) > 0){
		chi = 1;
	} else {
		chi = 0;
	}

	float xdotn2 = pow(clamp(dot(x, n), 0.f, 1.f), 2);
	float quant = 1 + pow(r, 2)*((1 - xdotn2)/xdotn2);

	return chi * (2 / (1 + sqrt(quant)));
}

void raycast::render(vector <SceneObject *> & scene, Camera * camera, vector <Light *> lights, int width, int height, bool altbrdf, bool beers, bool fresnel, bool sds, int ssN, int gi)
{
	const int numChannels = 3;
	const string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(width, height);

	unsigned char data [size.x * size.y * numChannels];

	BVH_Node * tree;
	std::vector <SceneObject *> planes;
	if (sds){
		std::vector <SceneObject *> objs;
		for (uint i = 0; i < scene.size(); i++){
			if (scene[i]->type == "Plane") {
				planes.push_back(scene[i]);
			} else {
				objs.push_back(scene[i]);
			}
		} 
		tree = new BVH_Node(objs);

		tree->buildTree(0);
		std::string root = "root";
		tree->printTree(root);
	}

	for (int y = 0; y < size.y; ++ y)
	{
	    for (int x = 0; x < size.x; ++ x)
	    {
	    	unsigned int red, green, blue = 0;

			ray r;
			vec3 color = vec3(0);
			if (ssN == 0){
				float f;
				r = createRay(camera, width, height, x, y);
				color = getColorForRay(r, tree, scene, camera, lights, altbrdf, 0, false, fresnel, beers, sds, planes, f, gi);
			} else {
				for (int m = 0; m < ssN; ++m){
					for (int n = 0; n < ssN; ++n){
						float f;
						r = createSuperSampledRay(camera, width, height, x, y, m, n, ssN);
						color += getColorForRay(r, tree, scene, camera, lights, altbrdf, 0, false, fresnel, beers, sds, planes, f, gi);
					}
				}
				color = color/((float)ssN*ssN);
			}
			
			red = (unsigned int) std::round(clamp(color.x, 0.f, 1.f) * 255.f);
			green = (unsigned int) std::round(clamp(color.y, 0.f, 1.f) * 255.f);
			blue = (unsigned int) std::round(clamp(color.z, 0.f, 1.f) * 255.f);

	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
	    }
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	//delete[] data;
}

float raycast::schlicks_approx(float n, vec3 normal, vec3 v)
{	
	float Fo = pow((n-1.f)/(n+1.f), 2.0f);
	float F = Fo + (1.f - Fo)*(pow(1.f - (abs(dot(normal, v))), 5.f));

	return F;
}

bool raycast::recurseDownTree(ray r, BVH_Node * tree, float & closesthit, SceneObject * & closestObj, ray & tRay)
{
	
	if (tree->volume.intersect(r) < 0)
	{
		return false;
	}

	for (uint i = 0; i < tree->children.size(); i++) {
		float newHit;
		SceneObject * newObj = nullptr;
		ray newTRay;
		if (recurseDownTree(r, tree->children[i], newHit, newObj, newTRay) > 0) {
			if ((closestObj == nullptr) || ((newHit >= 0) && (newHit < closesthit))) {
				closestObj = newObj;
				closesthit = newHit;
				tRay = newTRay;
			}
		}
	}

	for (uint i = 0; i < tree->objects.size(); i++){
		vec4 Oprime = tree->objects[i]->itransforms*vec4(r.origin, 1.0);
		vec4 Dprime = tree->objects[i]->itransforms*vec4(r.direction, 0.0);
		ray tr = ray(vec3(Oprime), vec3(Dprime));

		float hit = tree->objects[i]->intersect(tr);
		if (hit >= 0){
			if ((closestObj == nullptr) || (hit < closesthit))
			{
				closestObj = tree->objects[i];
				closesthit = hit;
				tRay = tr;
			}
		}
	}

	return closestObj != nullptr;
}

void raycast::intersectPlanes(ray r, float & closestHit, SceneObject * & obj, ray & tRay, vector <SceneObject *> planes)
{
	for (uint i = 0; i < planes.size(); i++)
	{
		vec4 Oprime = planes[i]->itransforms*vec4(r.origin, 1.0);
		vec4 Dprime = planes[i]->itransforms*vec4(r.direction, 0.0);
		ray tr = ray(vec3(Oprime), vec3(Dprime));

		float hit = planes[i]->intersect(tr);

		if (hit > 0) {
			if ((closestHit == -1) || (hit < closestHit)) {
				closestHit = hit;
				obj = planes[i];
				tRay = tr;
			}
		}
	}
}

SceneObject * raycast::getIntersect(ray r, BVH_Node * tree, vector <SceneObject *> scene, float & closestHit, ray & tRay, bool sds, vector <SceneObject *> planes)
{
	if (sds){
		SceneObject * obj = nullptr;
		bool intersect = recurseDownTree(r, tree, closestHit, obj, tRay);
		intersectPlanes(r, closestHit, obj, tRay, planes);

		if (intersect){
			return obj;
		} else {
			closestHit = -1;
			return nullptr;
		}
		
	} 
	else {
		int closestObjIndex = -1;
		for (uint i = 0; i < scene.size(); i++){

			mat4 M = scene[i]->itransforms;
			vec4 Oprime = M*vec4(r.origin, 1.0);
			vec4 Dprime = M*vec4(r.direction, 0.0);

			ray tr = ray(vec3(Oprime), vec3(Dprime));

			float hit = scene[i]->intersect(tr);
			
			if ((hit > 0) && (closestHit == -1)){
				closestHit = hit;
				closestObjIndex = i;
				tRay = tr;
			}
			
			if ((hit > 0) && (hit < closestHit)){
				closestHit = hit;
				closestObjIndex = i;
				tRay = tr;
			}
		}
		
		return scene[closestObjIndex];
	}
}

vec3 raycast::alignSample(vec3 sample, vec3 up, vec3 normal) {
	
	float angle = acos(dot(up, normal));

	vec3 axis;

	if (normal == up) {
		return sample;
	} else if (normal == -up) {
		return -sample;
	} else {
		axis = cross(up, normal);
	} 	
	
	mat4 rotMat = mat4(1.f);
	rotMat = rotate(mat4(1.f), angle, axis) * rotMat; 

	return vec3(rotMat * vec4(sample, 0.f));
}	

vec3 raycast::cosineWeightedPt(float u, float v) {
	const double pi = 3.14159265358979323846;

	float radial = sqrt(u);
	float theta = 2.f * pi * v;

	float x = radial * cos(theta);
	float y = radial * sin(theta);

	return vec3(x, y, sqrt(1.f - u));
}

vec3 raycast::generateHemispherePt(vec3 normal) {
	

	float u, v;

	u = rand() / (float) RAND_MAX; //STRATIFY
	v = rand() / (float) RAND_MAX;

	vec3 pt = (alignSample(cosineWeightedPt(u, v), vec3(0, 0, 1), normal));

	return pt;
}

vec3 raycast::getColorForRay(ray r, BVH_Node * tree, vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, bool altbrdf, int numRecurse, bool print, bool fresnel, bool beers, bool sds, std::vector <SceneObject *> planes, float & distanceHit, int gi)
{

	float closestHit = -1;
	ray tRay = ray(vec3(0), vec3(0));
		
	SceneObject * obj = getIntersect(r, tree, scene, closestHit, tRay, sds, planes);

	if (closestHit == -1){

		vec3 color = vec3(0.0, 0.0, 0.0);
		return color;
	
	} else {

		float distance = 0.f;
		float fresnel_ref = 0.f;
		vec3 attenuation = vec3(1);
		float ref = obj->reflection;
		float refrac = obj->filter;

		vec3 OGP = r.origin+closestHit*r.direction;
		vec3 P = tRay.origin+closestHit*tRay.direction; 
		vec3 normal = obj->computeNormal(P);

		vec3 color = vec3(0);
		vec3 refracColor = vec3(0);
		vec3 refColor = vec3(0);
		bool entering;

		//Reflection
		if (numRecurse < 6){

			if ( ((fresnel) && (refrac > 0.f)) || (ref > 0.f) )
			{
				vec3 refDir = r.direction - 2.f*dot(r.direction, normal)*normal;
				ray refRay = ray(OGP+.001f*normal, refDir);

				if (dot(r.direction, normal) > 0) {
					refRay = ray(OGP+.001f*-normal, refDir);
				}
				refColor = getColorForRay(refRay, tree, scene, camera, lights, altbrdf, numRecurse+1, print, fresnel, beers, sds, planes, distance, gi)*obj->color;
			}
		}

		//Refraction
		if ((refrac > 0.f)){

			vec3 dir = r.direction;
			float dDotn = dot(dir, normal);
			float objIor = obj->ior;
			float n1, n2;

			if (dDotn < 0) {
				n1 = 1.0f;
				n2 = objIor;
				entering = true;
				
			} else {
				n1 = objIor;
				n2 = 1.0f;
				normal = -1.f*normal;
				dDotn = dot(dir, normal);
				entering = false;
				distanceHit = closestHit;
			}

			float ratio = (n1/n2);
			vec3 refracDir = ratio*(dir-dDotn*normal)-normal*(float)(sqrt(1-(pow(ratio, 2)*(1-pow(dDotn, 2)))));
			ray refracRay = ray(OGP+0.001f*refracDir, refracDir);

			if (print){
				cout << "   Iteration Type: Refraction" << endl;
			}
			
			if (numRecurse < 12){
				refracColor = (getColorForRay(refracRay, tree, scene, camera, lights, altbrdf, numRecurse+1, print, fresnel, beers, sds, planes, distance, gi));
			}

			if (entering){
				if (beers){
					float d = distance;
					vec3 absorbance = (vec3(1.f)-obj->color)*0.15f*-d;
					attenuation = vec3(exp(absorbance.x), exp(absorbance.y), exp(absorbance.z));
				} else {
					refracColor *= obj->color;
				}
			}
			if (fresnel){
				vec3 d = -r.direction;
				fresnel_ref = schlicks_approx(objIor, normal, d);
			}
		}

		vec3 a = vec3(0.f);
		vec3 d, s;

		if (gi > 0){
			for (uint i = 0; i < gi; i++) {
				vec3 pt = generateHemispherePt(normal);
				vec3 dir = normalize(pt);

				ray giRay = ray(OGP+0.0001f*dir, dir);
				
				if (gi == 64){
					a += getColorForRay(giRay, tree, scene, camera, lights, altbrdf, numRecurse+1, print, fresnel, beers, sds, planes, distance, 16);
				} 
			}

			a *= 1.f/ gi; 
		}
										
		vec3 localColor = computeColor(OGP, tree, scene, planes, obj, normal, camera, lights, false, altbrdf, a, d, s, sds, gi);

		color = (1.f-refrac)*(1.f-ref)*localColor + 
				((1.f-refrac)*(ref)+(refrac)*(fresnel_ref))*refColor + 
				(refrac)*(1.f-fresnel_ref)*(attenuation)*refracColor;

		if (print) {
			a = a*(1.f-ref)*(1.f-refrac);
			d = d*(1.f-ref)*(1.f-refrac);
			s = s*(1.f-ref)*(1.f-refrac);
			refracColor = refracColor*refrac;
			refColor = (1.f-refrac)*(ref)*refColor;

			cout << "              Ray: {" << r.origin.x << " " << r.origin.y << " " << r.origin.z << "} -> {";
			cout << r.direction.x << " " << r.direction.y << " " << r.direction.z << "}" << endl;
			cout << "  Transformed Ray: {" << tRay.origin.x << " " << tRay.origin.y << " " << tRay.origin.z << "} -> {";
			cout << tRay.direction.x << " " << tRay.direction.y << " " << tRay.direction.z << "}" << endl;
			//cout << "       Hit Object: (ID #" << closestObjIndex+1 << " - " << scene[closestObjIndex]->type << ")" << endl;
			cout << "Transformed Intersection: {" << P.x << " " << P.y << " " << P.z << "} at T = " << closestHit << endl;
			cout << "     Intersection: {" << OGP.x << " " << OGP.y << " " << OGP.z << "} at T = " << closestHit << endl;
			cout << "           Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
			cout << "      Final Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
			cout << "          Ambient: {" << a.x << " " << a.y << " " << a.z << "}" << endl;
			cout << "          Diffuse: {" << d.x << " " << d.y << " " << d.z << "}" << endl;
			cout << "         Specular: {" << s.x << " " << s.y << " " << s.z << "}" << endl;
			cout << "       Reflection: {" << refColor.x << " " << refColor.y << " " << refColor.z << "}" << endl;
			cout << "       Refraction: {" << refracColor.x << " " << refracColor.y << " " << refracColor.z << "}" << endl;
			cout << "    Contributions: " << (1.f-ref)*(1.f-refrac) << " Local, " << (1.f-refrac)*(ref) << " Reflection, " << refrac << " Transmission" << endl;
		}
		
		return color;
	}
}

