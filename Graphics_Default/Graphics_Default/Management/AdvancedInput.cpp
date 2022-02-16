#include "AdvancedInput.h"
#include<iostream>
AdvancedInput* AdvancedInput::defaultInstance = 0;

AdvancedInput::AdvancedInput() : mousePosition(glm::vec3(0)), deltaMousePosition(glm::vec3(0)), previousMousePosition(glm::vec3(0))
{
	currentState = SDL_GetKeyboardState(NULL);
	previousState = currentState;
}

AdvancedInput::~AdvancedInput()
{
	delete currentState;
	delete previousState;

	currentState = nullptr;
	previousState = nullptr;
}

bool AdvancedInput::keyDown(SDL_Keycode key)
{
	return currentState[SDL_GetScancodeFromKey(key)];
}

bool AdvancedInput::keyPressed(SDL_Keycode key)
{
	return currentState[SDL_GetScancodeFromKey(key)] && !previousState[SDL_GetScancodeFromKey(key)];
}

bool AdvancedInput::keyUp(SDL_Keycode key)
{
	return currentState[SDL_GetScancodeFromKey(key)];
}

bool AdvancedInput::keyReleased(SDL_Keycode key)
{
	return !currentState[SDL_GetScancodeFromKey(key)] && previousState[SDL_GetScancodeFromKey(key)];
}

void AdvancedInput::update()
{
	SDL_GetMouseState(&previousMousePosition.x, &previousMousePosition.y);
	previousState = currentState;
	currentState = SDL_GetKeyboardState(NULL);
}

int AdvancedInput::getAxis(SDL_Keycode positive, SDL_Keycode negative)
{
	return (keyDown(positive) ? 1 : 0 + keyDown(negative) ? -1 : 0);
}

AdvancedInput* AdvancedInput::Instance()
{
	if (!defaultInstance) defaultInstance = new AdvancedInput();
	return defaultInstance;
}

glm::ivec3 AdvancedInput::MouseDelta()
{
	glm::ivec3 current = glm::ivec3(0);
	SDL_GetMouseState(&current.x, &current.y);
	return current - previousMousePosition;
}