#pragma once
#ifndef ADVANCED_INPUT

//Defines:
#define ADVANCED_INPUT
#define INPUT AdvancedInput::Instance()

//Includes:
#include<SDL.h>
#include<glm.hpp>
#include<vector>
#include<map>

/// <summary>The advanced input class provides a high level of choice and functionality when it comes to detecting keyboard input. The class is designed to intergrate
/// effortlessly into 'SDL2' as a singleton.</summary>
class AdvancedInput
{
private:
	//Attributes:
	const Uint8* currentState;
	const Uint8* previousState;
	Uint8 previous[SDL_NUM_SCANCODES];
	static AdvancedInput* defaultInstance;
	glm::ivec3 previousMousePosition;
	std::map<SDL_Keycode, bool> keysdown;

public:
	//Attribute:
	glm::ivec3 mousePosition;
	glm::ivec3 deltaMousePosition;

	//Constructor:
	AdvancedInput();

	//Deconstructor:
	~AdvancedInput();

	//Methods:
	/// <returns>True, if the 'key' parameter is currently down.</returns>
	bool keyDown(SDL_Keycode key);
	/// <returns>True, if the 'key' parameter is down during this frame but up during the previous frame.</returns>
	bool keyPressed(SDL_Keycode key);
	/// <returns>True, if the 'key' parameter is currently up.</returns>
	bool keyUp(SDL_Keycode key);
	/// <returns>True, if the 'key' parameter was down during the previous frame and up during the current frame</returns>
	bool keyReleased(SDL_Keycode key);
	/// <summary>The update method allows an instance of 'Input' to update the current keyboard state / environment.</summary>
	void Update();
	glm::ivec3 MouseDelta();
	int getAxis(SDL_Keycode positive, SDL_Keycode negative);

	//Static methods:
	static AdvancedInput* Instance();
};
#endif // !ADVANCED_INPUT
