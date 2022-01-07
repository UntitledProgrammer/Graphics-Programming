#pragma once
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>

#include"Constants.h"

class Window
{
public:
    //Attributes:
    SDL_Event sdlEvent;
    //Create a window and context for openGL to render too.
    SDL_Window* window;
    SDL_GLContext glContext;

public:
	//Default constructor:
	Window(SDL_Window* win) : window(win)
	{
        SDL_Init(SDL_INIT_EVERYTHING); //Initialise all of SDL's systems.

        //Instruct SDL with how we want to set up openGL.
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

        //Create a window and context for openGL to render too.
        window = SDL_CreateWindow("Default Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        glContext = SDL_GL_CreateContext(window);

        //Glew status:
        glewExperimental = GL_TRUE;
        GLenum status = glewInit(); // Initialise status.

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //Check if glew was initialised correctly.
        if (status != GLEW_OK) std::cout << "GLEW failed initialisation." << std::endl;
	}
};

