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

ray * raycast::createSuperSampledRay(Camera * camera, int width, int height, int x, int y, int m, int n, int ssN)
{
	float Us = (-0.5f)+(((float)x+((m+0.5f)/ssN))/width);
	float Vs = (-0.5f)+(((float)y+((n+0.5f)/ssN))/height);
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

float raycast::firstHit(ray * r, vector <SceneObject *> scene, bool print, int index)
{
	vec3 origin = r->origin;
	vec3 dir = r->direction;

	float closestHit = -1;
	int closestObjIndex = -1;
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
		vec3 a, d, s;
		vec3 P = origin+closestHit*dir;
		vec3 normal = scene[closestObjIndex]->computeNormal(P);
		computeColor(P, scene, closestObjIndex, normal, camera, lights, true, r, false, a, d, s);
	} 
}

vec3 raycast::computeColor(vec3 hit, vector <SceneObject *> scene, int objIndex, vec3 normal, Camera * camera, vector <Light *> lights, bool print, ray * c, bool altbrdf, glm::vec3 & a, glm::vec3 & d, glm::vec3 & s)
{
	SceneObject * obj = scene[objIndex];

	vec3 amb = obj->color * obj->ambient;
	vec3 color = amb;
	a = amb;

	for (int i = 0; i < lights.size(); i++){
		vec3 n = normal;
		vec3 l = normalize(lights[i]->location - hit);
		vec3 v = normalize(camera->location - hit);
		vec3 h = normalize(l+v);
		
		ray * lRay = new ray(hit + (l*0.0001f), l); 

		float lightHit = firstHit(lRay, scene, false, objIndex);
		
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

				vec3 diff = (lights[i]->color)*kd*clamp(dot(n, l), 0.f, 1.f);
				d = diff;
				color += diff;

				vec3 spec =  (lights[i]->color)*ks*(pow(clamp(dot(h, n), 0.f, 1.f), alpha));
				s = spec;
				color += spec;
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

void raycast::render(vector <SceneObject *> & scene, Camera * camera, vector <Light *> lights, int width, int height, bool altbrdf, bool beers, bool fresnel, int ssN)
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

			ray * r;
			vec3 color = vec3(0);
			if (ssN == 0){
				r = createRay(camera, width, height, x, y);
				color = getColorForRay(r, scene, camera, lights, altbrdf, 0, false, fresnel, beers);
			} else {
				for (int m = 0; m < ssN; ++m){
					for (int n = 0; n < ssN; ++n){
						r = createSuperSampledRay(camera, width, height, x, y, m, n, ssN);
						color += getColorForRay(r, scene, camera, lights, altbrdf, 0, false, fresnel, beers);
					}
				}
				color = color/((float)ssN*ssN);
				
			}
			
			
			//vec3 color = getColorForRay(r, scene, camera, lights, altbrdf, 0, false, fresnel, beers);
			red = (unsigned int) std::round(clamp(color.x, 0.f, 1.f) * 255.f);
			green = (unsigned int) std::round(clamp(color.y, 0.f, 1.f) * 255.f);
			blue = (unsigned int) std::round(clamp(color.z, 0.f, 1.f) * 255.f);

	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
	        data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
	    }
	}

	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
}

float raycast::schlicks_approx(float n, vec3 normal, Camera * camera, vec3 hit)
{	
	vec3 v = normalize(camera->location - hit);
	float Fo = (pow(n - 1.f, 2.f))/(pow(n + 1.f, 2.f));
	float F = Fo + (1.f - Fo)*(pow(1.f - abs(dot(normal, v)), 5.f));

	return F;
}

vec3 raycast::getColorForRay(ray * r, vector <SceneObject *> scene, Camera * camera, vector <Light *> lights, bool altbrdf, int numRecurse, bool print, bool fresnel, bool beers)
{

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
		return color;
	
	} else {
		float fresnel_ref = 0.f;
		vec3 attenuation = vec3(1);
		float ref = scene[closestObjIndex]->reflection;
		float refrac = scene[closestObjIndex]->filter;
		vec3 P = r->origin+closestHit*r->direction;
		vec3 normal = scene[closestObjIndex]->computeNormal(P);
		vec3 color = vec3(0);
		vec3 refracColor = vec3(0);
		vec3 refColor = vec3(0);
		int entering = -1;

		if ((ref > 0.f) && (numRecurse < 6)){
			vec3 refDir = r->direction-2.f*dot(r->direction, normal)*normal;
			ray refRay = ray(P+.001f*refDir, refDir);
			refColor = getColorForRay(&refRay, scene, camera, lights, altbrdf, numRecurse+1, print, fresnel, beers)*scene[closestObjIndex]->color;
		}

		if ((refrac > 0.f)){
			vec3 dir = r->direction;
			float dDotn = dot(dir, normal);
			float objIor = scene[closestObjIndex]->ior;
			float n1, n2;

			if (dDotn < 0) {
				n1 = 1.0f;
				n2 = objIor;
				entering = 1;
			} else {
				n1 = objIor;
				n2 = 1.0f;
				normal = -1.f*normal;
				dDotn = dot(dir, normal);
				entering = 0;
			}

			float ratio = (n1/n2);
			vec3 refracDir = ratio*(dir-dDotn*normal)-normal*(float)(sqrt(1-(pow(ratio, 2)*(1-pow(dDotn, 2)))));
			ray refracRay = ray(P+0.001f*refracDir, refracDir);
			if (print){
				cout << "   Iteration Type: Refraction" << endl;
			}
			
			refracColor = (getColorForRay(&refracRay, scene, camera, lights, altbrdf, numRecurse+1, print, fresnel, beers))*scene[closestObjIndex]->color;
			
			if (fresnel){
				//fresnel_ref = schlicks_approx(n1, normal, camera, P);
				fresnel_ref = schlicks_approx(objIor, normal, camera, P);
			}
			if (beers){
				vec3 absorbance = (vec3(1)-scene[closestObjIndex]->color)*0.15f*(P - r->origin)*-1.f;
				attenuation = exp(absorbance);
			}
		}

		vec3 a, d, s;
		vec3 localColor = computeColor(P, scene, closestObjIndex, normal, camera, lights, false, r, altbrdf, a, d, s);

		color = (1.f-refrac)*(1.f-ref)*localColor + ((1.f-refrac)*(ref)+(refrac)*(fresnel_ref))*refColor+(refrac)*(1.f-fresnel_ref)*(attenuation)*refracColor;

		if (print) {
			a = a*(1.f-ref)*(1.f-refrac);
			d = d*(1.f-ref)*(1.f-refrac);
			s = s*(1.f-ref)*(1.f-refrac);
			refracColor = refracColor*refrac;
			refColor = (1.f-refrac)*(ref)*refColor;

			cout << "              Ray: {" << r->origin.x << " " << r->origin.y << " " << r->origin.z << "} -> {";
			cout << r->direction.x << " " << r->direction.y << " " << r->direction.z << "}" << endl;
			cout << "       Hit Object: (ID #" << closestObjIndex+1 << " - " << scene[closestObjIndex]->type << ")" << endl;
			cout << "     Intersection: {" << P.x << " " << P.y << " " << P.z << "} at T = " << closestHit << endl;
			cout << "           Normal: {" << normal.x << " " << normal.y << " " << normal.z << "}" << endl;
			cout << "      Final Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;
			cout << "          Ambient: {" << a.x << " " << a.y << " " << a.z << "}" << endl;
			cout << "          Diffuse: {" << d.x << " " << d.y << " " << d.z << "}" << endl;
			cout << "         Specular: {" << s.x << " " << s.y << " " << s.z << "}" << endl;
			cout << "       Reflection: {" << refColor.x << " " << refColor.y << " " << refColor.z << "}" << endl;
			cout << "       Refraction: {" << refracColor.x << " " << refracColor.y << " " << refracColor.z << "}" << endl;
			cout << "    Contributions: " << (1.f-ref)*(1.f-refrac) << " Local, " << (1.f-refrac)*(ref) << " Reflection, " << refrac << " Transmission" << endl;
			if (entering == 0) {
				cout << "       Extra Info: " << "into-air" << endl << endl;
			} else if (entering == 1) {
				cout << "       Extra Info: " << "into-object" << endl << endl;
			} else {
				cout << endl;
			}
		}
		
		return color;
	}
}

