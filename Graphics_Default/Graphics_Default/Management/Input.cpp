#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::update()
{

}

bool Input::GetKey(SDL_Keycode key)
{
	//Get the current state of the keyboard.
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	//return true if key is down, false if the key is up.
	return keyboard[SDL_GetScancodeFromKey(key)] ? true : false;
}