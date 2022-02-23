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
#include"Materials/SolidMaterial.h"
#include"Materials/SurfaceMaterial.h"
#include"Materials/Skybox.h"
#include"Simulated/PlayerController.h"
#include"Entities/Entity.h"
/*
//ImGui:
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include<imgui.h>
#include<backends/imgui_impl_sdl.h>
#include<backends/imgui_impl_opengl3.h>
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





    //Lighting:
    Light* light = Light::Instance();
    light->colour = glm::vec3(2, 2, 2);

    Toolbar toolbar = Toolbar(window, &glContext);
    toolbar.LoadDefault();

    //Camera:
    Simulatables.Insert("MainCamera", Camera::Instance());
    Simulatables.Insert("MainLight", light);
    Camera* camera = Camera::Instance();
    camera->ApplyExtension<PlayerController>();
    Shape shape = Shape(camera);
    Entity* box = new Entity();
    Simulatables.Insert("Box",box);
    MeshRenderer* box2 = new MeshRenderer();
    box->SetMesh(Resources->LoadMesh("Resources/blocks_01.obj", "", "", "", ""));
    
    
    
    box->transform.position = glm::vec3(0, 14, 0);
    box->transform.scale = glm::vec3(0.1, 0.1, 0.1);
    box2->ApplyMesh(new Mesh(Primitives::Square(), Primitives::SqaureIndices()));
    box2->transform->scale = glm::vec3(20, 10, 20);
    box2->transform->position = glm::vec3(0,-1.5, 0);
    box2->transform->rotation = glm::vec3(glm::radians(-90.0f), 0, 0);
    SurfaceMaterial surface = SurfaceMaterial();
    surface.normal = shape.normalTexture;
    surface.base = shape.texture;
    surface.normal = shape.normalTexture;
    surface.Load("Shaders/LitShader");
    box->SetMaterial(&surface);
    box2->ApplyMaterial(&surface);
    Camera::Instance()->transform.position = glm::vec3(0, 0, 0);
    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600);
    Light::Instance()->transform.position.z += 2;

    //Shadow mapping:
    /*
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
    */


    //Main window loop:
    while (!AdvancedInput::Instance()->keyUp(SDLK_ESCAPE))
    {
        AdvancedInput::Instance()->update();
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        box2->Render();
        box->transform.position.x += INPUT->getAxis(SDLK_LEFT, SDLK_RIGHT);

        Resources->UpdateSimulated();
        toolbar.Update();

        SDL_GL_SwapWindow(window);
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