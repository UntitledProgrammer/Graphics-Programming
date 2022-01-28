#define GLEW_STATIC //Always define glew static first, even before any include libraries are added.

//Libraries:
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>
#include<string>

#include"AdvancedInput.h"
#define STB_IMAGE_IMPLEMENTATION
#include"Shape.h"
#include"LightBase.h"
#include"DisplayWindow.h"


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
    SDL_Window* window = SDL_CreateWindow("Default Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    //Glew status:
    glewExperimental = GL_TRUE;
    GLenum status = glewInit(); // Initialise status.

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Check if glew was initialised correctly.
    if (status != GLEW_OK) std::cout << "GLEW failed initialisation." << std::endl;

    SDL_Event sdlEvent;



    //Camera:
    Camera camera = Camera();
    Shape shape = Shape(&camera);
    shape.mesh->transform.position.z -= 0.5;


    //Lighting:
    Light* light = new Light();
    light->transform = shape.mesh->transform;
    light->transform.position.z += 3;

    //Add shader:
    Shader* basic = new Shader("Shaders/LitShader", camera);
    GLuint DiffuseID = Texture::getTexture("brickwall_normal.jpg");

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600);
    camera.recalculate();

    //Main window loop:
    while (true)
    {
        AdvancedInput::Instance()->update();
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);
        if (AdvancedInput::Instance()->keyUp(SDLK_ESCAPE)) break;
        std::cout << camera.transform.position.x << std::endl;
        camera.transform.position += glm::vec3(AdvancedInput::Instance()->getAxis(SDLK_d, SDLK_a) * -0.2f,  AdvancedInput::Instance()->getAxis(SDLK_w, SDLK_s) * -0.2f, 0);
        camera.aspect += AdvancedInput::Instance()->keyDown(SDLK_SPACE) * 0.1;
        camera.recalculate();

        //camera.transform.position




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        basic->bind();
        glActiveTexture(GL_TEXTURE0);
        GLuint textureLoc = glGetUniformLocation(basic->getProgram(), "texture_diffuse");
        glUniform1i(textureLoc, 0);

        glActiveTexture(GL_TEXTURE0);
        textureLoc = glGetUniformLocation(basic->getProgram(), "texture_normal");
        glUniform1i(textureLoc, 1);
        //glBindTexture(GL_TEXTURE_2D, textureID);
        //texture.update();

        //basic->update(tri.transform);

        //tri.draw();
        shape.draw(*light);
        light->draw(&camera);

        //Otherwise, render the window.

        SDL_Delay(16);

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