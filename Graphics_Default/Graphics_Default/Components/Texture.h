#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<glew.h>
#include<string>
#include<iostream>
#include"../stb_image.h"

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
	bool Load(std::string location);
	static GLuint getTexture(std::string location);
	void Update();
	void Bind(std::string name, GLuint program, int index = 0);
};
#endif // !TEXTURE_H