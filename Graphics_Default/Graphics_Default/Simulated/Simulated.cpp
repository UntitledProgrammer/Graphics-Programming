#include "Simulated.h"

void Simulated::UpdateExtensions()
{
	for (int i = 0; i < extensions.size(); i++) { if(extensions[i]->active) extensions[i]->Update(); }
}

void Simulated::Initialise()
{
	for (int i = 0; i < extensions.size(); i++) { extensions[i]->Initialise(); }
}
