#define GLEW_STATIC //Always define glew static first, even before any include libraries are added.

//Libraries:
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>
#include<string>

#include"Management/AdvancedInput.h"
#define STB_IMAGE_IMPLEMENTATION
#include"Components/Shape.h"
#include"Simulated/LightBase.h"
#include"Management/ResourceManager.h"
#include"Components/MeshRenderer.h"
#include"Editor/Toolbar.h"
#include"Visuals/Substances/SolidMaterial.h"
#include"Visuals/Substances/SurfaceMaterial.h"
#include"Visuals/Skybox.h"
#include"Simulated/Extensions/PlayerController.h"
#include"Simulated/Entity.h"
#include"Simulated/Extensions/Animator.h"
#include"Obsolete/Serialisation.h"
#include"Visuals/Substances/FlatShader.h"
#include"Demonstration/DemoResources.h"

//ImGui:
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include<imgui.h>
#include<backends/imgui_impl_sdl.h>
#include<backends/imgui_impl_opengl3.h>

float mag(glm::vec3 v) { return glm::sqrt( glm::pow(v.x, 2) + glm::pow(v.y, 2) + glm::pow(v.z, 2)); }

int main(int argc, char* argv[])
{
    glm::vec3 a = glm::vec3(1, 6,0), b = glm::vec3(5, 2,0);
    float angle = glm::degrees(glm::acos(dot(a, b) / (mag(a) * mag(b))));
    std::cout << "Result: " << angle<<std::endl;

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
    SDL_Window* window = SDL_CreateWindow("Default Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    
    //Glew status:
    glewExperimental = GL_TRUE;
    GLenum status = glewInit(); // IEnitialise status.

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Check if glew was initialised correctly.
    if (status != GLEW_OK) std::cout << "GLEW failed initialisation." << std::endl;

    SDL_Event sdlEvent;

    Demo::BuildSimulation();

    Toolbar toolbar = Toolbar(window, &glContext);
    toolbar.LoadDefault();



    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    /*
    //Shadow mapping:
    DepthSubstance depthSubstance = DepthSubstance();
    depthSubstance.Load("Visuals/Shaders/DepthShader");
    //Get some space on the GPU for passing a rendered image.
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

    //Create a new texture:
    GLuint shadowMapID;
    int shadowWidth = 2048;
    int shadowHeight = 2048;

    glGenTextures(1, &shadowMapID);
    glBindTexture(GL_TEXTURE_2D, shadowMapID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColour[] = { 1.0,1.0,1.0,1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapID, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { std::cerr << "Error: Frame buffer is incomplete." << std::endl; }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    flat.shadowID = shadowMapID;
    */
    //Main window loop:

    Resources->InitaliseSimulated();

    while (!AdvancedInput::Instance()->keyUp(SDLK_ESCAPE))
    {
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);

        //Shadow map: 
        /*
        GLfloat near_plane = 1.0f, far_plane = 100;
        glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(LightSingleton->transform.position, glm::vec3(0), glm::vec3(0, 1, 0)); //Note, add method to get position directly from matrix.
        glm::mat4 lightSpaceMatrix = lightProjection * lightView; //Note, implement these calculations into the light class.
        depthSubstance.lightSpaceMatrix = lightSpaceMatrix;

        glViewport(0, 0, shadowWidth, shadowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        depthSubstance.Update(testMesh->transform);
        depthSubstance.Bind();

        //!Shadow map.
        */

        glClearColor(0.0f, 0.15f, 0.3f, 1.0);
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Resources->UpdateSimulated();
        toolbar.Update();
        SDL_GL_SwapWindow(window);
        INPUT->Update();
        SDL_Delay(16);
    }


    //Clean up program:
    SDL_GL_DeleteContext(glContext); //Always delete context first.
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();

    std::cout << "SDL has succesfully closed." << std::endl;

    return 0;
}