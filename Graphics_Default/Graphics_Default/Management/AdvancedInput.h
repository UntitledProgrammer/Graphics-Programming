#pragma once
#ifndef ADVANCED_INPUT
#define ADVANCED_INPUT
#include<SDL.h>

class AdvancedInput
{
private:
	//Attributes:
	const Uint8* currentState;
	const Uint8* previousState;
	static AdvancedInput* defaultInstance;

public:
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
	void update();

	int getAxis(SDL_Keycode positive, SDL_Keycode negative);

	//Static methods:
	static AdvancedInput* Instance();
};
#endif // !ADVANCED_INPUT
