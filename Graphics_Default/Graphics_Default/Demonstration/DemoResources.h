/*
Context:
This file is far from an ideal solution for loading in a 'level' / 'scene' but without the time for fully implementing
some form of serialisation this is the only other possible solution. I chose to load all resources that are needed for the project
on this file to keep the rest of the project tidy, this could of course, have been achieved all in the 'main' file.
*/

#ifndef DEMO_RESOURCES_H
#define DEMO_RESOURCES_H

//Includes:
#include<string>
#include"DemoResources.h"
#include"../Management/ResourceManager.h"
#include"../Simulated/Extensions/PlayerController.h"
#include"../Simulated/Extensions/Rotate.h"
#include"../Simulated/Extensions/Animator.h"
#include"../Visuals/Substances/FlatShader.h"
#include"../Visuals/Substances/SurfaceMaterial.h"
#include"../Visuals/Substances/SolidMaterial.h"

namespace Demo
{
	//Directory paths:
	#define texturesLocation "Resources/Textures"
	#define objectsLocation "Resources/Objects"
	//Files:
	const std::string textureFiles[] = { "/brickwall.jpg","/brickwall_normal.jpg", "/0.jpg", "/wood.jpg", "/cardboard.jpg", "/cardboard_normal.jpg", "/zombie_open.jpg","/zombie_closed.jpg"};
	const std::string objFiles[] = { "/blocks_01.obj","/cube.obj", "/monkey.obj", "/sphere.obj", "/cone.obj","/torus.obj"};
	//Colours:
	const glm::vec3 red = glm::vec3(1.0, 0.0, 0.0);
	const glm::vec3 green = glm::vec3(0.0, 1.0, 0.0);
	const glm::vec3 blue = glm::vec3(0.0, 0.0, 1.0);
	const glm::vec3 white = glm::vec3(1.0, 1.0, 1.0);

	/// <summary>Loads all texture files referenced in the demo project.</summary>
	static bool LoadTextures()
	{
		for (unsigned int i = 0; i < sizeof(textureFiles) / sizeof(textureFiles[0]); i++)
		{
			Texture* texture = new Texture();
			if (texture->Load(texturesLocation + textureFiles[i]))
			{
				Textures.Insert(textureFiles[i], texture);
				texture = nullptr;
			}
			else
			{
				std::cout << "Error: Failed to load texture at filepath: " << (texturesLocation + textureFiles[i]) << "." << std::endl;
				return false;
			}
		}
		return true;
	}


	/// <summary>Loads all mesh (.obj) files referenced in the demo project.</summary>
	static bool LoadMeshes()
	{
		for (unsigned int i = 0; i < sizeof(objFiles) / sizeof(objFiles[0]); i++)
		{
			std::vector<unsigned int> indices;
			std::string location = objectsLocation + objFiles[i];
			std::vector<Vertex> vertices = Resources->LoadMesh(location, "", "", "", "", indices);
			if (vertices.size() > 0)
			{
				Mesh* mesh = new Mesh(vertices, indices);
				Meshes.Insert(objFiles[i], mesh);
				mesh = nullptr;
			}
			else
			{
				std::cout << "Error: Failed to load mesh at filepath: " << objectsLocation << objFiles[i] << "." << std::endl;
				return false;
			}
		}
		return true;
	}

	static Entity* AddEntity(std::string name, Mesh* mesh, Substance* substance, glm::vec3 position = glm::vec3(0,0,0))
	{
		Entity* entity = new Entity(name);
		entity->SetMesh(mesh);
		entity->SetMaterial(substance);
		entity->transform.position = position;
		Simulatables.Add(entity);
		return entity;
	}

	/// <summary>Builds the default simulated environment for the demo project.</summary>
	static bool BuildSimulation()
	{
		//Load resources:
		LoadMeshes();
		LoadTextures();
		Meshes.Insert("/plain.obj", new Mesh(Primitives::Square(), Primitives::SqaureIndices(), true));

		//Create substances / materials:
		FlatSubstance* flatSubstance = new FlatSubstance();
		flatSubstance->Load("Visuals/Shaders/FlatShader");
		SurfaceMaterial* surface = new SurfaceMaterial();
		surface->Load("Visuals/Shaders/RealShader");
		surface->base = Textures.Get("/brickwall.jpg");
		surface->normal = Textures.Get("/brickwall_normal.jpg");
		SurfaceMaterial* surface2 = new SurfaceMaterial();
		surface2->Load("Visuals/Shaders/RealShader");
		surface2->base = Textures.Get("/cardboard.jpg");
		surface2->normal = Textures.Get("/cardboard_normal.jpg");
		SolidMaterial* solid = new SolidMaterial();
		solid->Load("Visuals/Shaders/Solid");
		solid->base = Textures.Get("/wood.jpg");
		solid->colour = glm::vec4(1, 1, 1, 1);
		SolidMaterial* solid2 = new SolidMaterial();
		solid2->Load("Visuals/Shaders/Solid");
		solid2->base = Textures.Get("/zombie_open.jpg");
		solid2->colour = glm::vec4(1, 1, 1, 1);

		//Setup and add camera:
		MainCamera->ApplyExtension<CameraController>();
		Simulatables.Add(MainCamera);

		//Lighting:
		Simulatables.Add(new Light("Directional Light", LightCategory::Directional, white));
		Simulatables.Add(new Light("Point Light", LightCategory::Phong, blue));
		Simulatables.Add(new Light("Spotlight", LightCategory::Spotlight, red));

		//Add simulated objects:
		AddEntity("Cube", Meshes.Get("/cube.obj"), solid, glm::vec3(5, 0, 0));
		AddEntity("Sphere", Meshes.Get("/sphere.obj"), flatSubstance, glm::vec3(-5, 0, 0));
		Simulatables.At(Simulatables.End())->ApplyExtension<Rotate>();
		AddEntity("Plain", Meshes.Get("/plain.obj"), surface, glm::vec3(10, -2, 0));
		AddEntity("Cone", Meshes.Get("/cone.obj"), flatSubstance, glm::vec3(0, 5, 5));
		AddEntity("Torus", Meshes.Get("/torus.obj"), surface2, glm::vec3(5, -5, 2));
		Entity* plane = AddEntity("Plane", Meshes.Get("/plain.obj"), solid2);
		plane->transform.rotation = glm::vec3(0, 0, glm::radians(180.0f));

		//Animator:
		std::shared_ptr<Animator> animator = plane->ApplyExtension<Animator>();
		animator->PushBack(Textures.Get("/zombie_open.jpg"));
		animator->PushBack(Textures.Get("/zombie_open.jpg"));
		animator->PushBack(Textures.Get("/zombie_open.jpg"));
		animator->PushBack(Textures.Get("/zombie_closed.jpg"));
		animator->PushBack(Textures.Get("/zombie_open.jpg"));
		animator->delay = 500.0f;
		return true;
	}
}
#endif //!DEMO_RESOURCES_H