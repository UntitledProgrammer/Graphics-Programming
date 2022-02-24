#pragma once
#ifndef SIMULATED_H
#define SIMULATED_H

//Includes:
#include<map>
#include<vector>
#include<iostream>
#include<string>
#include"../Math/Transform.h"
#include"Extension.h"

class Simulated
{
private:
	std::vector<std::shared_ptr<Extension>> extensions;
	std::string name = "DefaultSimulated";

public:
	//Attributes:
	/// <summary>All simulated bodies require a transform component.</summary>
	Transform transform;

	//Abstract methods:
	/// <summary>Update is called during every frame of runtime.</summary>
	virtual void Update() = 0;
	virtual Simulated* Instantiate() { return nullptr; };
	void UpdateExtensions();
	void Initialise();
	void SetName(std::string n){ name = n; }
	std::string GetName() { return name; }
	void DrawCentre(float scale = 1.0f);
	
	//Methods:
	template<typename ExtensionType> void ApplyExtension()
	{
		//If extension type does not inherit extension as a base class return.
		if (!std::is_base_of<Extension, ExtensionType>::value)
		{
			std::cout << "Error: " << typeid(ExtensionType).name() << ", does not inherit extension as a base class." << std::endl;
			return;
		}
		std::shared_ptr extension = std::make_shared<ExtensionType>();
		extension->body = this;
		extensions.push_back(extension);
	}

};
#endif SIMULATED_H //!SIMULATED_H