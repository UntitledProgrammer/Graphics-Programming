#pragma once
#include<cereal/types/memory.hpp>
#include<cereal/archives/json.hpp>
#include<cereal/archives/binary.hpp>
#include<fstream>
#include<glm.hpp>
#include<string>
#include"../Management/ResourceManager.h"

const std::string filename = "Resources/Data/data.JSON";

template<class Archive> void save(Archive& archive, Vec const& m)
{
	archive(cereal::make_nvp("x", m.x));
	archive(cereal::make_nvp("y", m.y));
	archive(cereal::make_nvp("z", m.z));
}

template<class Archive> void load(Archive& archive, Vec& m)
{
	archive(cereal::make_nvp("x", m.x));
	archive(cereal::make_nvp("y", m.y));
	archive(cereal::make_nvp("z", m.z));
}


void SaveSimulation()
{
	std::ofstream os(filename.c_str());
	cereal::JSONOutputArchive archive(os);
	glm::vec3 test = glm::vec3(1, 1, 5);
	for (int i = 0; i < Simulatables.Size(); i++)
	{
		archive(cereal::make_nvp(Simulatables.At(i)->GetName() + std::to_string(i), *Simulatables.At(i)));
	}
}

void LoadSimulation()
{
	std::ofstream os(filename.c_str());
	cereal::JSONOutputArchive archive(os);
}