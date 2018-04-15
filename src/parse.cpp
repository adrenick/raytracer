/* 	Alexa Drenick
	CSC 473
	Raytracer Project */

#include "parse.hpp"

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

vec3 Parse::ParseVector(stringstream & Stream)
{
	vec3 v;
	//v.x = v.y = v.z = 0.0;
	float x, y, z = 0.f;
	stringbuf buf;

	//Stream.ignore(1, '<');
	Stream.ignore(10, '<');
	Stream.get(buf, '>');
	if (Stream.eof()){
    	cerr << "Expected <x, y, z>'" << endl;
    }
	Stream.ignore(numeric_limits<streamsize>::max(), '>');

	std::string line = buf.str(); // be careful...
	//int read = sscanf(line.c_str(), "%f, %f, %f", &v.x, &v.y, &v.z);
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
	vec3 c;
	float d;
	float amb;
	float diff;
	stringbuf buf;

	//cout << "**SPHERE**" << endl;

	v = Parse::ParseVector(Stream);
	//cout << v.x << " " << v.y << " " << v.z << endl;

	Stream.ignore(1, ',');
	Stream.get(buf, 'p');    //THIS IS LAME
	if (Stream.eof()){
    	cerr << "Expected <x, y, x>, d'" << endl;
    }

	string line = buf.str();
	int read = sscanf(line.c_str(), "%f", &d);

	if (read != 1)
	{
		cerr << "Expected to read 1 distance but found '" << line << "'" << endl;
	}

	//cout << d << endl;

	Stream.ignore(10, '{');
    Stream.ignore(15, 'g');

    c = Parse::ParseVector(Stream);

	amb = Parse::ParseAmbient(Stream);

	diff = Parse::ParseDiffuse(Stream);

    //std::cout << c.x << " " << c.y << " " << c.z << std::endl;

    SceneObject * obj = new Sphere(v, d, c);
    obj->ambient = amb;
    obj->diffuse = diff;
    obj->type = "Sphere";

    return obj;

}

float Parse::ParseAmbient(stringstream & Stream)
{
	float a;
	stringbuf buf;

	Stream.get(buf, '{');
    Stream.get(buf, 't');
    Stream.ignore(1, 't');
    buf.str("");
    Stream.get(buf, 'd');
    string line = buf.str();
    //cout << "line: " << line << endl;
    int read = sscanf(line.c_str(), "%f", &a);
	if (read != 1)
	{
		cerr << "Expected to read 1 material ambient constant but found '" << line << "'" << endl;
	}

	return a;
}

float Parse::ParseDiffuse(stringstream & Stream)
{
	float d;
	stringbuf buf;

	Stream.get(buf, 'e');
    Stream.ignore(1, 'e');
    buf.str("");
    Stream.get(buf, '}');
    string line = buf.str();
    //cout << "line: " << line << endl;
    int read = sscanf(line.c_str(), "%f", &d);
	if (read != 1)
	{
		cerr << "Expected to read 1 material ambient constant but found '" << line << "'" << endl;
	}
	return d;
}

SceneObject * Parse::ParsePlane(stringstream & Stream)
{
	vec3 n;
	vec3 c;
	float d, amb, diff;
	stringbuf buf;

	//cout << "**PLANE**" << endl;

	n = Parse::ParseVector(Stream);

	//cout << n.x << " " << n.y << " " << n.z << endl;

	Stream.ignore(1, ',');
	Stream.get(buf, 'p');    //THIS IS LAME
	if (Stream.eof()){
    	cerr << "Expected <x, y, x>, d'" << endl;
    }

	string line = buf.str();
	int read = sscanf(line.c_str(), "%f", &d);

	if (read != 1)
	{
		cerr << "Expected to read 1 distance but found '" << line << "'" << endl;
	}

	//cout << d << endl;

	Stream.ignore(10, '{');
    Stream.ignore(15, 'g');

    c = Parse::ParseVector(Stream);

    amb = Parse::ParseAmbient(Stream);

	diff = Parse::ParseDiffuse(Stream);

    //std::cout << c.x << " " << c.y << " " << c.z << std::endl;

    SceneObject * obj = new Plane(n, d, c);
    obj->ambient = amb;
    obj->diffuse = diff;
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

	//buf.clear();
	Stream.get(buf, 'h');
	Stream.ignore(1, 't');
	//string line = buf.str();
	//cout << "R***: " << line << endl;
	r = Parse::ParseVector(Stream);

	Stream.get(buf, '_');
	Stream.ignore(1, 'a');
	Stream.ignore(1, 't');
	la = Parse::ParseVector(Stream);

	//cout << "camera" << endl;
	return new Camera(l, u, r, la);
}

Light * Parse::ParseLight(std::stringstream & Stream)
{
	vec3 l;
	vec3 c;
	stringbuf buf;

	//Stream.ignore(1, '{');
	l = Parse::ParseVector(Stream);

	Stream.get(buf, 'b');
	//Stream.ignore(10, '{');
    //Stream.ignore(15, 'g');
	c = Parse::ParseVector(Stream);

	return new Light(l, c);


}


