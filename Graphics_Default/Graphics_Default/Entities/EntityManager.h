#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

//Includes:
#include<vector>
#include"../Simulated/Entity.h";

/// <summary>The entity manager class is a fairly lightweight resource manager with functionality designed specifically for use with the entity class.</summary>
class SimulatedManager
{
private:
	//Attributes:
	std::vector<Simulated*> entities;

public:
	//Constructor:
	SimulatedManager() {};

	//Destructor:
	~SimulatedManager() {};

	//Methods:
	void Add(Simulated* entity)
	{
		entities.push_back(entity);
	}

	void Find(std::string name)
	{

	}

	int Size() { return entities.size(); }

	Simulated* At(int i)
	{
		if (i < 0 || i >= entities.size()) { return nullptr; }
		return entities[i];
	}
};
#endif // !ENTITY_MANAGER_H