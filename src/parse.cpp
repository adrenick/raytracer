/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "parse.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
using namespace std;
using namespace glm;

/*
std::istream::ignore
istream& ignore (streamsize n = 1, int delim = EOF);
extracts characyers from input sequence and discards them until either n characters have been extracted or one compared equal to delim

std::istream::get
(3) istream& get (streambuf& sb, char delim);
extracts characyers from the stream and inserts them into the output sequence controlled by the stream buffer object sb, stopping either as soon as such an insertion fails or as soon as the delimiting character is encountered in the input sequence (the deliminiting character being eith the newline character, '/n', or delimm, if this arguement is specifiec). Only the characters successfully inserted into sb are extracted from the stream: neither the delimiting character, nor eventually the character that failed to be inserted at sb, are extracted from the input sequence and remain there as the next character to  be extracted from the stream */

vec4 Parse::ParseColor(stringstream & Stream)
{
	vec4 v;
	float x, y, z, f = 0.f;

	stringbuf buf;

	Stream.ignore(10, '<');
	Stream.get(buf, '>');
	if (Stream.eof()){
    	cerr << "Expected <x, y, z>'" << endl;
    }
	Stream.ignore(numeric_limits<streamsize>::max(), '>');

	std::string line = buf.str(); // be careful...
	int read = sscanf(line.c_str(), "%f, %f, %f, %f", &x, &y, &z, &f);
	
	if (read == 4){
		v = vec4(x, y, z, f);
	} else if (read == 3) {
		v = vec4(x, y, z, 0.f);
	} else {
		std::cerr << "Expected to read 3 vector elements but found '" << line << "'" << endl;
	}

	return v;
}

vec3 Parse::ParseVector(stringstream & Stream)
{
	vec3 v;
	float x, y, z = 0.f;

	stringbuf buf;

	Stream.ignore(10, '<');
	Stream.get(buf, '>');
	if (Stream.eof()){
    	cerr << "Expected <x, y, z>'" << endl;
    }
	Stream.ignore(numeric_limits<streamsize>::max(), '>');

	std::string line = buf.str(); // be careful...
	int read = sscanf(line.c_str(), "%f, %f, %f", &x, &y, &z);
	v = vec3(x, y, z);

	if (read != 3)
	{
		std::cerr << "Expected to read 3 vector elements but found '" << line << "'" << endl;
	}

	return v;
}

SceneObject * Parse::ParseSphere(stringstream & Stream)
{
	vec3 v;
	vec4 color;
	vec3 c;
	float d = 0.f;
	float amb, diff, spec, rough, ior, ref, refrac = 0.f;
	stringbuf buf;

	v = Parse::ParseVector(Stream);

	Stream.ignore(1, ',');
	Stream.get(buf, 'p'); 
	if (Stream.eof()){
    	cerr << "Expected <x, y, x>, d'" << endl;
    }

	string line = buf.str();
	int read = sscanf(line.c_str(), "%f", &d);

	if (read != 1)
	{
		cerr << "Expected to read 1 distance but found '" << line << "'" << endl;
	}

	Stream.ignore(10, '{');
    Stream.ignore(15, 'g');

    //c = Parse::ParseVector(Stream);
    color = Parse::ParseColor(Stream);
    c = vec3(color.x, color.y, color.z);

	Parse::ParseFinish(Stream, amb, diff, spec, rough, ior, ref, refrac);

	/*Stream.ignore(2, '}');
	std::string token;
	Stream >> token;
	if ((token == "scale") || (token == "rotate") || (token == "translate")){
		vec3 v = Parse::ParseVector(Stream);
	}*/
	/*string token;
	Stream >> token;
	vec3 t;
	//while (!finish.eof())
	//while (!Stream.eof())
	while (token != "{")
	{
		//cout << "token: " << token << endl;
		if (token == "scale"){
			t = ParseVector(Stream);
			cout << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "rotate"){
			t = ParseVector(Stream);
			cout << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "translate"){
			t = ParseVector(Stream);
			cout << t.x << " " << t.y << " " << t.z << endl;
		}

		Stream >> token;
		//newfinish >> token;
	}*/

    SceneObject * obj = new Sphere(v, d, c);

    Stream.ignore(1, '}');
    string token;
    Stream >> token;
    vec3 t;
    while ((token != "}") && (!Stream.eof()))
    {
    	//cout << "token: " << token << endl;
		if (token == "scale"){
			t = ParseVector(Stream);
			//obj->itransforms = scale(obj->itransforms, t);
			obj->itransforms = scale(mat4(1.f), t)*obj->itransforms;
			cout << "scale: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "rotate"){
			t = ParseVector(Stream);
			obj->itransforms = rotate(mat4(1.f), radians(t.z), vec3(0, 0, 1))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.y), vec3(0, 1, 0))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.x), vec3(1, 0, 0))*obj->itransforms;
			// obj->itransforms = rotate(obj->itransforms, radians(t.z), vec3(0, 0, 1));
			// obj->itransforms = rotate(obj->itransforms, radians(t.y), vec3(0, 1, 0));
			// obj->itransforms = rotate(obj->itransforms, radians(t.x), vec3(1, 0, 0));
			cout << "rotate: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "translate"){
			t = ParseVector(Stream);
			//obj->itransforms = translate(obj->itransforms, t);
			obj->itransforms = translate(mat4(1.f), t)*obj->itransforms;
			cout << "translate: " << t.x << " " << t.y << " " << t.z << endl;
		}

		Stream >> token;
    }
    cout << "\n";
    obj->itransforms = inverse(obj->itransforms);

    obj->ambient = amb;
    obj->diffuse = diff;
    obj->specular = spec;
    obj->roughness = rough;
    obj->ior = ior;
    obj->reflection = ref;
    obj->refraction = refrac;
    obj->filter = color.w;

    obj->type = "Sphere";

    return obj;

}

SceneObject * Parse::ParseTriangle(stringstream & Stream)
{
	vec3 a;
	vec3 b;
	vec3 c;
	vec4 color;
	vec3 col;
	float amb, diff, spec, rough, ior, ref, refrac;
	stringbuf buf;

	a = Parse::ParseVector(Stream);

	Stream.ignore(1, ',');

	b = Parse::ParseVector(Stream);

	Stream.ignore(1, ',');

	c = Parse::ParseVector(Stream);

	Stream.ignore(10, '{');
    Stream.ignore(15, 'g');

    //color = Parse::ParseVector(Stream);
    color = Parse::ParseColor(Stream);
    col = vec3(color.x, color.y, color.z);

	Parse::ParseFinish(Stream, amb, diff, spec, rough, ior, ref, refrac);

    SceneObject * obj = new Triangle(a, b, c, col);

    Stream.ignore(2, '}');
    string token;
    Stream >> token;
    vec3 t;
    while ((token != "}") && (!Stream.eof()))
    {
    	//cout << "token: " << token << endl;
		if (token == "scale"){
			t = ParseVector(Stream);
			obj->itransforms = scale(mat4(1.f), t)*obj->itransforms;
			cout << "scale: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "rotate"){
			t = ParseVector(Stream);
			obj->itransforms = rotate(mat4(1.f), radians(t.z), vec3(0, 0, 1))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.y), vec3(0, 1, 0))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.x), vec3(1, 0, 0))*obj->itransforms;
			cout << "rotate: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "translate"){
			t = ParseVector(Stream);
			obj->itransforms = translate(mat4(1.f), t)*obj->itransforms;
			cout << "translate: " << t.x << " " << t.y << " " << t.z << endl;
		}

		Stream >> token;
    }
    cout << "\n";

    obj->ambient = amb;
    obj->diffuse = diff;
    obj->specular = spec;
    obj->roughness = rough;
    obj->ior = ior;
    obj->reflection = ref;
    obj->refraction = refrac;
    obj->filter = color.w;

    obj->type = "Triangle";

    return obj;

}

void Parse::ParseFinish(stringstream & Stream, float & a, float & d, float & s, float & r, float & ior, float & ref, float & refrac){

	string whole;
	stringbuf buf;
	stringstream finish;

	Stream.get(buf, '{');
	buf.str("");
	Stream.get(buf, '}');

	whole = buf.str();

	finish.str(whole);

	a = d = s = r = refrac = ref = ior = 0.f;

	//a = ParseAmbient(finish);

	//d = ParseDiffuse(finish);

	stringstream newfinish;
	newfinish.str(whole);
	//newfinish.ignore(10, 't');
	//newfinish.ignore(14, 'e');

	
	string token;
	finish.ignore(1, '{');
	finish >> token;
	//newfinish >> token;

	//while(!newfinish.eof())
	while (!finish.eof())
	{
		//cout << "token: " << token << endl;
		if (token == "ambient"){
			a = ParseAmbient(finish);
		} else if (token == "diffuse") {
			d = ParseDiffuse(finish);
		} else if (token == "specular"){
			s = ParseSpecular(finish);
		} else if (token == "roughness"){
			r = ParseRoughness(finish);
		} else if (token == "reflection"){
			ref = ParseReflection(finish);
		} else if (token == "refraction"){
			refrac = ParseRefraction(finish);
		} else if (token == "ior"){
			ior = ParseIOR(finish);
		}

		finish >> token;
		//newfinish >> token;
	}
	//cout << "token after: " << token << endl;

	/*s = ParseSpecular(newfinish);

	stringstream newnewfinish;
	newnewfinish.str(whole);

	if (s == 0.f){
		//cout << "parsing reflection" << endl;

		ref = ParseReflection(newnewfinish);
		r = 0.f;
		//ior = 0.f;

	} else {
		
		r = ParseRoughness(newnewfinish);
	}

		stringstream newnewnewfinish;
		newnewnewfinish.str(whole);

		refrac = ParseRefraction(newnewnewfinish);

		ior = ParseIOR(newnewnewfinish);*/

}

float Parse::ParseRefraction(stringstream & Stream)
//float Parse::ParseRefraction(string finish)
{


	//stringstream Stream;
	//Stream.str(finish);
	float r = 0.f;
	stringbuf buf;

	/*Stream.ignore(16, 'n');
	Stream.ignore(32, 'n');
	Stream.ignore(16, 'n');
	Stream.get(buf, 'r');*/

	/*Stream.ignore(18, 'f');
	Stream.ignore(1, 'f');
	Stream.ignore(14, 'f');
	Stream.ignore(100, 'r');


	Stream.ignore(10, 'n');
	Stream.get(buf, 'i');*/
	//Stream.ignore(1, 'i');
	//Stream.ignore(1, 'o');
	//Stream.ignore(1, 'r');

	Stream.ignore (1, ' ');
	Stream.get(buf, ' ');


	string line = buf.str();
	//cout << "string: " << line << endl;

	int read = sscanf(line.c_str(), "%f", &r);

	if (read != 1)
	{
		r = 0.f;
	}

	line = Stream.str();

	return r;
}


//float Parse::ParseIOR(string finish)
float Parse::ParseIOR(stringstream & Stream)
{
	//stringstream Stream;
	//Stream.str(finish);

	float i = 0.f;
	stringbuf buf;
   
	/*Stream.ignore(40, 'r');
	Stream.ignore(15, 's');
	Stream.ignore(10, 'r');
	Stream.ignore(1, 'r');*/

	/*Stream.ignore(3, 'r');
	Stream.get(buf, '}');*/
	Stream.ignore(1, ' ');
	Stream.get(buf, ' ');

	string line = buf.str();
	//cout << line << endl;

	int read = sscanf(line.c_str(), "%f", &i);

	if (read != 1)
	{
		i = 0.f;
	}

	return i;
}


//float Parse::ParseReflection(string finish)
float Parse::ParseReflection(stringstream & Stream)
{
	//stringstream Stream;
	//Stream.str(finish);
	float r = 0.f;
	stringbuf buf;

	/*Stream.ignore(16, 'n');
	Stream.ignore(32, 'n');
	Stream.get(buf, '}');*/

	/*Stream.ignore(100, 'l');
	Stream.ignore(8, 'n');
	Stream.get(buf, '}');*/
	Stream.ignore (1, ' ');
	Stream.get(buf, ' ');

	string line = buf.str();
	//cout << "reflection string: " << line << endl;

	int read = sscanf(line.c_str(), "%f", &r);

	if (read != 1)
	{
		r = 0.f;
	}

	line = Stream.str();

	return r;

}

//float Parse::ParseSpecular(string finish)
float Parse::ParseSpecular(stringstream & Stream)
{
	//stringstream Stream;
	//Stream.str(finish);
	float s = 0.f;
	stringbuf buf;

	/*Stream.ignore(40, 'r');
	Stream.get(buf, 'r');*/
	Stream.ignore(1, ' ');
	Stream.get(buf, ' ');

	string line = buf.str();

	int read = sscanf(line.c_str(), "%f", &s);

	if (read != 1)
	{
		s = 0.f;
	}

	line = Stream.str();

	return s;
}

float Parse::ParseRoughness(stringstream & Stream)
//float Parse::ParseRoughness(string finish)
{
	//stringstream Stream;
	//Stream.str(finish);
	float r = 0.f;
	stringbuf buf;
   
	/*Stream.ignore(40, 'r');
	Stream.ignore(15, 's');
	Stream.ignore(1, 's');
	Stream.get(buf, EOF);*/
	Stream.ignore(1, ' ');
	Stream.get(buf, ' ');

	string line = buf.str();

	int read = sscanf(line.c_str(), "%f", &r);

	if (read != 1)
	{
		r = 0.f;
	}

	return r;
}

float Parse::ParseAmbient(stringstream & Stream)
{
	float a = 0.f;
	stringbuf buf;

	/*Stream.ignore(2, '{');
    Stream.get(buf, 't');
    Stream.ignore(1, 't');

    buf.str("");
    Stream.get(buf, 'd');*/
    Stream.ignore(1, ' ');
    Stream.get(buf, ' ');
    string line = buf.str();

    int read = sscanf(line.c_str(), "%f", &a);
	if (read != 1)
	{
		cerr << "Expected to read 1 material ambient constant but found '" << line << "'" << endl;
	}

	return a;
}

float Parse::ParseDiffuse(stringstream & Stream)
{
	float d = 0.f;
	stringbuf buf;

	/*Stream.get(buf, 'e');
    Stream.ignore(1, 'e');
    Stream.ignore(1, ' ');
    buf.str("");
    Stream.get(buf, ' ');*/

    Stream.ignore(1, ' ');
    Stream.get(buf, ' ');

    string line = buf.str();

    int read = sscanf(line.c_str(), "%f", &d);
	if (read != 1)
	{
		cerr << "Expected to read 1 material diffuse constant but found '" << line << "'" << endl;
	}
	return d;

}

SceneObject * Parse::ParsePlane(stringstream & Stream)
{
	vec3 n;
	vec3 c;
	vec4 color;
	float d, amb, diff, spec, rough, ior, ref, refrac;
	stringbuf buf;

	//cout << "before n\n";
	n = Parse::ParseVector(Stream);

	Stream.ignore(1, ',');
	Stream.get(buf, 'p');   
	if (Stream.eof()){
    	cerr << "Expected <x, y, x>, d'" << endl;
    }

	string line = buf.str();
	int read = sscanf(line.c_str(), "%f", &d);

	if (read != 1)
	{
		cerr << "Expected to read 1 distance but found '" << line << "'" << endl;
	}

	Stream.ignore(10, '{');
    Stream.ignore(15, 'g');

    //c = Parse::ParseVector(Stream);
    //cout << "before color\n";
    color = Parse::ParseColor(Stream);
    c = vec3(color.x, color.y, color.z);

    //cout << "before finish\n";

	Parse::ParseFinish(Stream, amb, diff, spec, rough, ior, ref, refrac);

    SceneObject * obj = new Plane(n, d, c);

    Stream.ignore(1, '}');

    buf.str("");
    Stream.get(buf, '}');
    string whole = buf.str();
    stringstream rest;
	rest.str(whole);

    string token;
    //cout << token << endl;
    rest >> token;
    cout << "token before loop: " << token << endl;
    vec3 t;
    while ((token != "}") && (!rest.eof()))
    {
    	cout << "token in plane: " << token << endl;
		if (token == "scale"){
			t = ParseVector(rest);
			//obj->itransforms = scale(obj->itransforms, t);
			obj->itransforms = scale(mat4(1.f), t)*obj->itransforms;
			cout << "scale: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "rotate"){
			t = ParseVector(rest);
			obj->itransforms = rotate(mat4(1.f), radians(t.z), vec3(0, 0, 1))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.y), vec3(0, 1, 0))*obj->itransforms;
			obj->itransforms = rotate(mat4(1.f), radians(t.x), vec3(1, 0, 0))*obj->itransforms;
			// obj->itransforms = rotate(obj->itransforms, radians(t.z), vec3(0, 0, 1));
			// obj->itransforms = rotate(obj->itransforms, radians(t.y), vec3(0, 1, 0));
			// obj->itransforms = rotate(obj->itransforms, radians(t.x), vec3(1, 0, 0));
			cout << "rotate: " << t.x << " " << t.y << " " << t.z << endl;
		} else if (token == "translate"){
			t = ParseVector(rest);
			//obj->itransforms = translate(obj->itransforms, t);
			obj->itransforms = translate(mat4(1.f), t)*obj->itransforms;
			cout << "translate: " << t.x << " " << t.y << " " << t.z << endl;
		}

		rest >> token;
    }
    cout << "token after loop: " << token << endl;
    //Stream.ignore(1, '}');
    //Stream.get(buf, ' ');
    cout << "\n";

    obj->ambient = amb;
    obj->diffuse = diff;
    obj->specular = spec;
    obj->roughness = rough;
    obj->ior = ior;
    obj->reflection = ref;
    obj->refraction = refrac;
    obj->filter = color.w;

    obj->type = "Plane";
    
    return obj;
}

Camera * Parse::ParseCamera(std::stringstream & Stream)
{
	vec3 l;
	vec3 u;
	vec3 r;
	vec3 la;
	stringbuf buf;

	Stream.get(buf, 'n');
	l = Parse::ParseVector(Stream);

	Stream.get(buf, 'p');
	u = Parse::ParseVector(Stream);

	Stream.get(buf, 'h');
	Stream.ignore(1, 't');

	r = Parse::ParseVector(Stream);

	Stream.get(buf, '_');
	Stream.ignore(1, 'a');
	Stream.ignore(1, 't');
	la = Parse::ParseVector(Stream);

	return new Camera(l, u, r, la);
}

Light * Parse::ParseLight(std::stringstream & Stream)
{
	vec3 l;
	vec3 c;
	stringbuf buf;

	l = Parse::ParseVector(Stream);

	Stream.get(buf, 'b');

	c = Parse::ParseVector(Stream);

	return new Light(l, c);
}

void Parse::parseString(std::stringstream & stream, vector <SceneObject *> & scene, Camera * & camera, vector <Light *> & lights)
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
		} else if (token.compare("triangle") == 0) {
			stream.ignore(3, '{');
			scene.push_back(Parse::ParseTriangle(stream));
		} else if (token.substr(0, 2) == "//") { 
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

void Parse::parseFile(string filename, vector <SceneObject *> &scene, Camera * & camera, vector <Light *> & lights)
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
