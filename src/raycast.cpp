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

float raycast::firstHit(ray * r, vector <SceneObject *> scene, bool print)
{
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
		computeColor(origin+closestHit*dir, scene, closestObjIndex, camera, lights, true, r, false);
	} 
}

vec3 raycast::computeColor(vec3 hit, vector <SceneObject *> scene, int objIndex, Camera * camera, vector <Light *> lights, bool print, ray * c, bool altbrdf)
{
	SceneObject * obj = scene[objIndex];

	vec3 color = obj->color * obj->ambient;

	for (int i = 0; i < lights.size(); i++){
		
		vec3 n = obj->computeNormal(hit);
		vec3 l = normalize(lights[i]->location - hit);
		vec3 v = normalize(camera->location - hit);
		vec3 h = normalize(l+v);
		
		ray * lRay = new ray(hit + (l*0.0001f), l); //ray * lRay = new ray(hit + (n*0.0001f), l);

		/*cout << "=== jaccuse below ===" << endl;
		cout << "n: " << n.x << " " << n.y << " " << n.z << endl;
		cout << "l: " << l.x << " " << l.y << " " << l.z << endl;
		cout << "v: " << v.x << " " << v.y << " " << v.z << endl;
		cout << "h: " << h.x << " " << h.y << " " << h.z << endl;
		cout << "lRay: <" << lRay->origin.x << " " << lRay->origin.y << " " << lRay->origin.z << "> -> <";
		cout << lRay->direction.x << " " << lRay->direction.y << " " << lRay->direction.z << ">" << endl;*/

		float lightHit = firstHit(lRay, scene, false);
		
		if (!((lightHit) != -1 && (lightHit < length(lights[i]->location - hit)))) {

			vec3 kd = obj->diffuse*obj->color;
			vec3 ks = obj->specular*obj->color;

			if (altbrdf){
				float alpha = pow(obj->roughness, 2);

				float D = calcD(n, h, alpha);

				float G = (calcG(l, h, n, alpha))*(calcG(v, h, n, alpha));

				float Fo = (pow(obj->ior - 1, 2))/(pow(obj->ior + 1, 2));
				float F = Fo + (1 - Fo)*(pow(1-clamp(dot(v, h), 0.f, 1.f), 5));

				vec3 rs = ks*((D*G*F)/(4*clamp(dot(n, v), 0.f, 1.f))); 

				color += (lights[i]->color)*(kd*(clamp(dot(n, l), 0.f, 1.f))+rs);
			} else {

				float alpha = 2/(pow(obj->roughness, 2))-2;
				//vec3 diff = ( lights[i]->color)*kd*dot(n, l);
				vec3 diff = (lights[i]->color)*kd*clamp(dot(n, l), 0.f, 1.f);
				//color += ( lights[i]->color)*kd*dot(n, l);
				color += diff;
				//vec3 spec = (lights[i]->color)*ks*(pow(dot(h, n), alpha));
				vec3 spec =  (lights[i]->color)*ks*(pow(clamp(dot(h, n), 0.f, 1.f), alpha));
				color += spec;
				//color += (lights[i]->color)*ks*(pow(dot(h, n), alpha));
				if ((diff.x < 0) || (diff.y < 0) || (diff.z < 0)){
					cout << "*** DIFF < 0 ***" << endl;
					//cout << "kd: " << kd.x << " " << kd.y << " " << kd.z << endl;
					cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
				}
				if ((spec.x < 0) || (spec.y < 0) || (spec.z < 0)){
					cout << "*** SPEC < 0 ***" << endl;
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

	//color = vec3(clamp(color.x, 0.f, 1.f), clamp(color.y, 0.f, 1.f), clamp(color.z, 0.f, 1.f));

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

void raycast::render(vector <SceneObject *> & scene, Camera * camera, vector <Light *> lights, int width, int height, bool altbrdf)
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

			ray * r = createRay(camera, width, height, x, y);/*
			vec3 origin = r->origin;
			vec3 dir = r->direction;

			float closestHit = -1;
			float closestObjIndex = -1;
			for (int i = 0; i < scene.size(); i++){
				float hit = scene[i]->intersect(*r); //WHY?
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
				vec3 color = computeColor(origin+closestHit*dir, scene, closestObjIndex, camera, lights, false, r, altbrdf);

				red = (unsigned int) std::round(color.x * 255.f);
				green = (unsigned int) std::round(color.y * 255.f);
				blue = (unsigned int) std::round(color.z * 255.f);
			} */
			vec3 color = getColorForRay(r, scene, camera, lights, altbrdf, 0);
			red = (unsigned int) std::round(clamp(color.x, 0.f, 1.f) * 255.f);
			green = (unsigned int) std::round(clamp(color.y, 0.f, 1.f) * 255.f);
			blue = (unsigned int) std::round(clamp(color.z, 0.f, 1.f) * 255.f);
			//clamp(color.x, 0.f, 1.f)

	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
	    }
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

vec3 raycast::getColorForRay(ray * r, vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, bool altbrdf, int numRecurse)
{
	//ray * r = createRay(camera, width, height, x, y);
			//vec3 origin = r->origin;
			//vec3 dir = r->direction;

	if (numRecurse > 0)
	{
		//cout << "Ray: {" << r->origin.x << " " << r->origin.y << " " << r->origin.z << "} -> {";
		//cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
	}
	

	float closestHit = -1;
	float closestObjIndex = -1;
			
	for (int i = 0; i < scene.size(); i++){
		float hit = scene[i]->intersect(*r);
		
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

		vec3 color = vec3(0.0, 0.0, 0.0);
		return color;
	
	} else {
		float ref = scene[closestObjIndex]->reflection;
		float refrac = scene[closestObjIndex]->filter;
		vec3 P = r->origin+closestHit*r->direction;
		vec3 normal = scene[closestObjIndex]->computeNormal(P);
		vec3 color = (1.f-ref)*(1.f-refrac)*computeColor(P, scene, closestObjIndex, camera, lights, false, r, altbrdf);
		//vec3 color = (1.f-ref)*computeColor(P, scene, closestObjIndex, camera, lights, false, r, altbrdf);

		//cout << "ref: " << ref << endl;
		if ((ref > 0.f) && (numRecurse < 6)){
			//vec3 normal = scene[closestObjIndex]->computeNormal(P);
			vec3 refDir = r->direction-2.f*dot(r->direction, normal)*normal;
			ray refRay = ray(P+.001f*refDir, refDir);
			//vec3 refRay = r->direction-2.f*dot(r->direction, normal)*normal; //calcReflectionRay()
			color += ref*(1.f-refrac)*(getColorForRay(&refRay, scene, camera, lights, altbrdf, numRecurse+1))*scene[closestObjIndex]->color;
			//color = vec3(clamp(color.x, 0.f, 1.f), clamp(color.y, 0.f, 1.f), clamp(color.z, 0.f, 1.f));
		}
		if ((refrac > 0.f)){
			vec3 dir = r->direction;
			float dDotn = dot(dir, normal);
			float objIor = scene[closestObjIndex]->ior;
			float n1, n2;
			if (dDotn < 0) {
				n1 = 1.0f;
				n2 = objIor;
			} else {
				n1 = objIor;
				n2 = 1.0f;
				normal = -1.f*normal;
			}
			float ratio = (n1/n2);
			vec3 refracDir = ratio*(dir-dDotn*normal)-normal*(float)(sqrt(1-(pow(ratio, 2)*(1-pow(dDotn, 2)))));
			ray refracRay = ray(P+0.001f*refracDir, refracDir);
			color += refrac*(getColorForRay(&refracRay, scene, camera, lights, altbrdf, numRecurse+1))*scene[closestObjIndex]->color;


		}

		//dot normal and direction
		
		return color;

	}

}

void raycast::getAmbDiffSpec(vec3 hit, vector <SceneObject *> scene, int objIndex, vec3 normal, Camera * camera, vector <Light *> lights, ray * c, glm::vec3 & a, glm::vec3 & d, glm::vec3 & s)
{
	SceneObject * obj = scene[objIndex];

	vec3 amb = obj->color * obj->ambient;
	vec3 color = amb;
	a = amb;

	//vector <vec3> comps;
	//comps.push_back(amb);

	for (int i = 0; i < lights.size(); i++){
		
		vec3 n = normal;
		//vec3 n = obj->computeNormal(hit);
		vec3 l = normalize(lights[i]->location - hit);
		vec3 v = normalize(camera->location - hit);
		vec3 h = normalize(l+v);
		
		ray * lRay = new ray(hit + (l*0.0001f), l); //ray * lRay = new ray(hit + (n*0.0001f), l);

		float lightHit = firstHit(lRay, scene, false); //NEED TO PASS NORMAL HERE?
		
		if (!((lightHit) != -1 && (lightHit < length(lights[i]->location - hit)))) {

			vec3 kd = obj->diffuse*obj->color;
			vec3 ks = obj->specular*obj->color;

			float alpha = 2/(pow(obj->roughness, 2))-2;
			vec3 diff = ( lights[i]->color)*kd*clamp(dot(n, l), 0.f, 1.f);
			cout << "*******************diff: " << diff.x << " " << diff.y << " " << diff.z << endl;
			//comps.push_back(diff);
			d = diff;
			color += diff;


			vec3 spec = (lights[i]->color)*ks*(pow(clamp(dot(h, n), 0.f, 1.f), alpha));
			//comps.push_back(spec);
			s = spec;
			color += spec;

			if ((diff.x < 0) || (diff.y < 0) || (diff.z < 0)){
					cout << "*** DIFF < 0 ***" << endl;
					//cout << "kd: " << kd.x << " " << kd.y << " " << kd.z << endl;
					cout << "normal: " << n.x << " " << n.y << " " << n.z << endl;
				}
				if ((spec.x < 0) || (spec.y < 0) || (spec.z < 0)){
					cout << "*** SPEC < 0 ***" << endl;
				}

			//cout << "Ambient: {" << amb.x << " " << amb.y << " " << amb.z << "}" << endl;
			//cout << "Diffuse: {" << diff.x << " " << diff.y << " " << diff.z << "}" << endl;
			//cout << "Specular: {" << spec.x << " " << spec.y << " " << spec.z << "}" << endl;
		} 


				
	}

	//return comps;
}

vec3 raycast::printRays(ray * r, vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, bool altbrdf, int numRecurse)
{
	//ray * r = createRay(camera, width, height, x, y);
			//vec3 origin = r->origin;
			//vec3 dir = r->direction;

	if (numRecurse > 0)
	{
		//cout << "Ray: {" << r->origin.x << " " << r->origin.y << " " << r->origin.z << "} -> {";
		//cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
	}
	

	float closestHit = -1;
	int closestObjIndex = -1;
			
	for (int i = 0; i < scene.size(); i++){
		float hit = scene[i]->intersect(*r);
		
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

		vec3 color = vec3(0.0, 0.0, 0.0);
		cout << "no hit" << endl;
		return color;
	
	} else {
		float ref = scene[closestObjIndex]->reflection;
		//float refrac = scene[closestObjIndex]->refraction;
		float refrac = scene[closestObjIndex]->filter;
		vec3 P = r->origin+closestHit*r->direction;
		vec3 normal = scene[closestObjIndex]->computeNormal(P);
		vec3 color = vec3(0);
		vec3 refracColor = vec3(0);
		vec3 refColor = vec3(0);

		/*vec3 color = (1.f-ref)*(1.f-refrac)*computeColor(P, scene, closestObjIndex, camera, lights, false, r, altbrdf);
		
		cout << "Ray: {" << r->origin.x << " " << r->origin.y << " " << r->origin.z << "} -> {";
		cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
		cout << "Hit Object: (ID #" << closestObjIndex+1 << " - " << scene[closestObjIndex]->type << ")" << endl;
		cout << "Intersection: {" << P.x << " " << P.y << " " << P.z << "} at T = " << closestHit << endl;
		cout << "Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;

		vec3 a, d, s;
		getAmbDiffSpec(P, scene, closestObjIndex, camera, lights, r, a, d, s);
		cout << "Ambient: {" << (1.f-ref)*(1.f-refrac)*a.x << " " << (1.f-ref)*(1.f-refrac)*a.y << " " << (1.f-ref)*(1.f-refrac)*a.z << "}" << endl;
		cout << "Diffuse: {" << (1.f-ref)*(1.f-refrac)*d.x << " " << (1.f-ref)*(1.f-refrac)*d.y << " " << (1.f-ref)*(1.f-refrac)*d.z << "}" << endl;
		cout << "Specular: {" << (1.f-ref)*(1.f-refrac)*s.x << " " << (1.f-ref)*(1.f-refrac)*s.y << " " << (1.f-ref)*(1.f-refrac)*s.z << "}" << endl;
		cout << "Contributions: " << (1.f-ref)*(1.f-refrac) << " Local, " << ref << " Reflection, " << refrac << " Transmission" << endl;*/
		
		//vec3 color = (1.f-ref)*computeColor(P, scene, closestObjIndex, camera, lights, false, r, altbrdf);

		//cout << "ref: " << ref << endl;
		if ((ref > 0.f) && (numRecurse < 6)){
			//vec3 normal = scene[closestObjIndex]->computeNormal(P);
			vec3 refDir = r->direction-2.f*dot(r->direction, normal)*normal;
			ray refRay = ray(P+.001f*refDir, refDir);
			//vec3 refRay = r->direction-2.f*dot(r->direction, normal)*normal; //calcReflectionRay()
			cout << "----\nIteration type: Reflection" << endl;
			refColor = ref*(1.f-refrac)*(printRays(&refRay, scene, camera, lights, altbrdf, numRecurse+1))*scene[closestObjIndex]->color;
			color += refColor;
			
			//color = vec3(clamp(color.x, 0.f, 1.f), clamp(color.y, 0.f, 1.f), clamp(color.z, 0.f, 1.f));
		} 
		if ((refrac > 0.f)){
			vec3 dir = r->direction;
			float objIor = scene[closestObjIndex]->ior;
			float n1, n2;
			float dDotn = dot(dir, normal);
			if (dDotn < 0) {
				n1 = 1.0f;
				n2 = objIor;
			} else {
				n1 = objIor;
				n2 = 1.0f;
				normal = -1.f*normal;
				dDotn = dot(dir, normal);
			}
			float ratio = (n1/n2);
			//cout << "objIOR: " << objIor << endl;
			vec3 refracDir = ratio*(dir-dDotn*normal)-normal*(float)(sqrt(1-(pow(ratio, 2)*(1-pow(dDotn, 2)))));
			ray refracRay = ray(P+0.001f*refracDir, refracDir);
			cout << "----\nIteration type: Refraction" << endl;
			//cout << "Ray: {" << refracRay.origin.x << " " << refracRay.origin.y << " " << refracRay.origin.z << "} -> {";
			//cout << refracRay.direction.x << " " << refracRay.direction.y << " " << refracRay.direction.z << "}" << endl;
			refracColor = refrac*(printRays(&refracRay, scene, camera, lights, altbrdf, numRecurse+1))*scene[closestObjIndex]->color;
			color += refracColor;
			
		}

		color += (1.f-ref)*(1.f-refrac)*computeColor(P, scene, closestObjIndex, camera, lights, false, r, altbrdf);

		vec3 a, d, s;
		getAmbDiffSpec(P, scene, closestObjIndex, normal, camera, lights, r, a, d, s);
		
		cout << "Ray: {" << r->origin.x << " " << r->origin.y << " " << r->origin.z << "} -> {";
		cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
		cout << "Hit Object: (ID #" << closestObjIndex+1 << " - " << scene[closestObjIndex]->type << ")" << endl;
		cout << "Intersection: {" << P.x << " " << P.y << " " << P.z << "} at T = " << closestHit << endl;
		cout << "Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
		cout << "Final Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
		cout << "Ambient: {" << (1.f-ref)*(1.f-refrac)*a.x << " " << (1.f-ref)*(1.f-refrac)*a.y << " " << (1.f-ref)*(1.f-refrac)*a.z << "}" << endl;
		cout << "Diffuse: {" << (1.f-ref)*(1.f-refrac)*d.x << " " << (1.f-ref)*(1.f-refrac)*d.y << " " << (1.f-ref)*(1.f-refrac)*d.z << "}" << endl;
		cout << "Specular: {" << (1.f-ref)*(1.f-refrac)*s.x << " " << (1.f-ref)*(1.f-refrac)*s.y << " " << (1.f-ref)*(1.f-refrac)*s.z << "}" << endl;
		cout << "Reflection: {" << refColor.x << " " << refColor.y << " " << refColor.z << "}" << endl;
		cout << "Refraction: {" << refracColor.x << " " << refracColor.y << " " << refracColor.z << "}" << endl;
		cout << "Contributions: " << (1.f-ref)*(1.f-refrac) << " Local, " << ref << " Reflection, " << refrac << " Transmission" << endl;

		//dot normal and direction
		
		
		return color;

	}

}


