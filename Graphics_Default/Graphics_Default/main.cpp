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
    Light* light = new Light();
    light->transform.position.z += 1;

    Toolbar toolbar = Toolbar(window, &glContext);
    toolbar.LoadDefault();

    //Camera:
    Camera* camera = Camera::Instance();
    Shape shape = Shape(camera);

    //Add shader:
    std::vector<glm::uint> indecies;
    std::vector<Vertex> verticies;

    verticies = ResourceManager::LoadOBJ("Resources", "blocks_01.obj", "", "", "", "", indecies);


    Mesh* mesh = new Mesh(verticies.data(), verticies.size(), indecies.data(), indecies.size());

    MeshRenderer* meshRenderer = new MeshRenderer();
    meshRenderer->ApplyMesh(mesh);
    mesh->transform.scale = glm::vec3(0.001f, 0.001f, 0.001f);
    meshRenderer->transform->scale = glm::vec3(0.1f, 0.1f, 0.1f);
    meshRenderer->transform->position = light->transform.position;
    Skybox skybox = Skybox();
    Texture texture = Texture();
    std::vector<std::string> files = { "brickwall.jpg", "brickwall.jpg", "brickwall.jpg", "brickwall.jpg", "brickwall.jpg", "brickwall.jpg" };
    texture.LoadCubemap(files);
    skybox.cubemap = &texture;
    meshRenderer->ApplyMaterial(&skybox);




    //meshRenderer->ApplyMaterial(&surface);
    Camera::Instance()->transform.position = glm::vec3(0, 0, 0);

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600);

    //Main window loop:
    while (true)
    {
        AdvancedInput::Instance()->update();
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);
        if (AdvancedInput::Instance()->keyUp(SDLK_ESCAPE)) break;
        camera->transform.position += glm::vec3(AdvancedInput::Instance()->getAxis(SDLK_d, SDLK_a) * 0.2f,0,AdvancedInput::Instance()->getAxis(SDLK_w, SDLK_s) * 0.2f);
        camera->transform.rotation += glm::vec3(0, AdvancedInput::Instance()->MouseDelta().x * -0.1f, AdvancedInput::Instance()->MouseDelta().y * -0.1f);
        camera->aspect += AdvancedInput::Instance()->keyDown(SDLK_SPACE) * 0.1;
        camera->Update();
        meshRenderer->transform->position = camera->transform.position;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        meshRenderer->Render();

        light->draw();

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