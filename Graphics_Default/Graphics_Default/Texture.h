#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<glew.h>
#include<string>
#include<iostream>
#include"stb_image.h"

class Texture
{
public:
	//Attributes:
	int width, height;
	unsigned char* data;
	GLuint id;
	GLenum format;

	//Constructor:
	Texture();

	//Deconstructor:
	~Texture();

	//Methods:
	bool load(std::string location);
	void update();
};
#endif // !TEXTURE_H