#define GLEW_STATIC //Always define glew static first, even before any include libraries are added.

//Libraries:
#include <glew.h>
#include<SDL_opengl.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<iostream>
#include<string>

#include"Constants.h"
#include"Transform.h"
#include"Camera.h"
#include"Mesh.h"
#include"Input.h"
float vertices[]{ 0.0f, 0.0f, 0.0f, 0.1f, -0.2f, 0.0f, -0.1f, -0.2f, 0.0f };

float r = 0.0f , g = 0.0f , b = 0.0f;

const GLchar* VertexShaderCode =
"#version 450\n"
"in vec3 vp;"
"uniform mat4 model; uniform mat4 projection; uniform mat4 view; vec3 position;"
"void main(){"
"	gl_Position = projection * view * model * vec4(position, 1.0);"
"}";

const GLchar* FragmentShaderCode =
"#version 450\n"
"out vec4 frag_colour;"
"void main(){"
"	frag_colour = vec4(1.0, 0.0, 0.0, 0.0);"
"}";



//Functions:
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram) glGetProgramiv(shader, flag, &success);
    else glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram) glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint getObject(const float* vertices)
{
    //Draw a triangle:
    GLuint VertexBufferObject = 0; //GL-uint represents an unsigned integer.
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    //Create a vertex array object:
    GLuint VertexArrayObject = 0;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);
    glEnableVertexAttribArray(0);

    //Bind vertex buffer object:
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindVertexArray(0);

    return VertexBufferObject;
}





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

    //Linking and compiling the shaders:
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);
    glCompileShader(VertexShader);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);
    glCompileShader(FragmentShader);

    //Connect the shaders to a shader program:
    GLuint ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);

    //Link and validate the shader program:
    glLinkProgram(ShaderProgram);
    CheckShaderError(ShaderProgram, GL_LINK_STATUS, true, "ERROR: program linking failed: ");
    glValidateProgram(ShaderProgram);
    CheckShaderError(ShaderProgram, GL_LINK_STATUS, true, "ERROR: program is invalid: ");

    //Camera:
    Camera camera = Camera();



















    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600);

    Transform transform = Transform();
    transform.position = glm::vec3(0.5, 2, 0);

    Mesh tri = Mesh(vertices, 3);
    camera.Recalculate();
    //Main window loop:
    while (true)
    {
        //Exit loop if any key is pressed.
        SDL_PollEvent(&sdlEvent);
        if (Input::GetKey(SDLK_ESCAPE)) break;

        tri.draw();

        //Otherwise, render the window.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(ShaderProgram);

        GLint modelLoc = glGetUniformLocation(ShaderProgram, "model");
        GLint posLoc = glGetUniformLocation(ShaderProgram, "position");
        GLint viewLoc = glGetUniformLocation(ShaderProgram, "view");
        GLint projLoc = glGetUniformLocation(ShaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.matrix()[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &camera.perspective[0][0]);
        glUniform3f(posLoc, camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
        tri.draw();
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