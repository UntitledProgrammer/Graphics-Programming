#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H

//Includes:
#include"Texture.h"

class Cubemap : public Texture
{
private:
	//Attributes:

public:
	//Constructor:
	Cubemap();

	//Destructor:
	~Cubemap();

	//Base methods:
	bool Load(std::string location) override;
	bool LoadMap(std::vector<std::string> files);
	void Update() override;
	void Bind(std::string name, GLuint program, int index = 0) override;

	//Methods:
};
#endif //!CUBEMAP_H