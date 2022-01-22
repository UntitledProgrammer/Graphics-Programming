#define GLEW_STATIC //Always define glew static first, even before any include libraries are added.

//Libraries:
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>
#include<string>

#include"Shader.h"
#include"Mesh.h"
#include"AdvancedInput.h"
#define STB_IMAGE_IMPLEMENTATION
#include"Texture.h"

/*
GLuint textureID;

void LoadTexture(std::string location)
{
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(location.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

    if (imageData == NULL) std::cerr << "Texture loading failed for texture: " << location << std::endl;

    GLenum format=1;
    if (numComponents == 1) format = GL_RED;
    if (numComponents == 3) format = GL_RGB;
    if (numComponents == 4) format = GL_RGBA;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);
}
*/

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



    //Load some textures:
    //LoadTexture("brickwall.jpg");
    Texture texture;
    texture.load("brickwall.jpg");


    //Camera:
    Camera camera = Camera();

    //Add shader:
    Shader* basic = new Shader("Shaders/Basic", camera);

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600);
    unsigned int indicies[]{ 0,1,2,0,2,3 };

    Mesh tri = Mesh(&Primitives::Square()[0], Primitives::Square().size(), &indicies[0], 6);
    tri.transform.position = glm::vec3(0, 0, -20.0f);
    tri.transform.scale = glm::vec3(10, 10, 0);

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
        //glBindTexture(GL_TEXTURE_2D, textureID);
        texture.update();

        basic->update(tri.transform);

        tri.draw();

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