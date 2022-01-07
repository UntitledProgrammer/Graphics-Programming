#define GLEW_STATIC //Always define glew static first, even before any include libraries are added.

//Libraries:
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>


int main(int argc, char* argv[])
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
    SDL_Window* window = SDL_CreateWindow("Default Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 880, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    //Glew status:
    glewExperimental = GL_TRUE;
    GLenum status = glewInit(); // Initialise status.

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Check if glew was initialised correctly.
    if (status != GLEW_OK) std::cout << "GLEW failed initialisation." << std::endl;

    SDL_Event sdlEvent;

    //Main window loop:
    while (true)
    {
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);
        if (sdlEvent.type == SDL_KEYDOWN) break;

        //Otherwise, render the window.
        glClearColor(1.0f, 0.15f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 800, 600);

        SDL_GL_SwapWindow(window);
    }



    //Clean up program:
    SDL_GL_DeleteContext(glContext); //Always delete context first.
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();

    std::cout << "SDL has succesfully closed." << std::endl;

    return 0;
}