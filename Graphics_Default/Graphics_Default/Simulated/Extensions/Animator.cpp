#include "Animator.h"

Animator::Animator()
{
	material = nullptr;
	lastframeTime = delay;
	currentframe = startframe;
}

Animator::~Animator()
{

}

void Animator::Insert(unsigned int index, Texture* texture)
{
	if (index < 0 || index >= frames.size()) return;
	frames[index] = texture;
}

void Animator::PushBack(Texture* texture)
{
	frames.push_back(texture);
}

void Animator::PushFront(Texture* texture)
{
	frames.insert(frames.begin(), texture);
}

void Animator::Update()
{
	if (SDL_GetTicks() - lastframeTime >= delay) //Set next frame.
	{
		currentframe = currentframe+1 >= frames.size() ? startframe : currentframe+1; //If the current frame is at the end of the cycle, go back to the starting frame.
		material->base = frames[currentframe];
		lastframeTime = SDL_GetTicks();
		std::cout << "Switching to texture at index: " << currentframe << std::endl;
	}
}

void Animator::Initialise()
{
	MeshRenderer* renderer = static_cast<Entity*>(body)->meshRenderer;
	material = static_cast<SurfaceMaterial*>(renderer->material);
	material->base = frames.front();
}
