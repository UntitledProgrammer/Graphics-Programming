#include "FlatShader.h"

FlatSubstance::FlatSubstance()
{
    colour = glm::vec3(1, 1, 1);
}

FlatSubstance::~FlatSubstance()
{

}

bool FlatSubstance::Load(const std::string location)
{
    program = glCreateProgram();

    //Add shader types:
    shaders[VERTEX] = CreateShader(LoadShader(location + ".vert"), GL_VERTEX_SHADER);
    shaders[FRAGMENT] = CreateShader(LoadShader(location + ".frag"), GL_FRAGMENT_SHADER);

    //Attach shaders:
    for (GLuint i = 0; i < SHADER_TYPES; i++)
    {
        glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
    glValidateProgram(program);
    CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

    return false;
}

void FlatSubstance::Update(Transform& transform)
{
    //Mesh:
    SetUniformMat4("model", transform.GetMatrix());

    //Camera:
    SetUniformMat4("projection", Camera::Instance()->perspective);
    SetUniformMat4("view", Camera::Instance()->view);

    //Light:

    for (int i = 0; i < Light::lights.size(); i++)
    {
        char buffer[64];
        sprintf_s(buffer, "lights[%i].colour", i);
        SetUniformVec3(buffer, Light::lights[i]->colour);
        sprintf_s(buffer, "lights[%i].position", i);
        SetUniformVec3(buffer, Light::lights[i]->transform.position);
        sprintf_s(buffer, "lights[%i].direction", i);
        SetUniformVec3(buffer, Light::lights[i]->direction);
        sprintf_s(buffer, "lights[%i].type", i);
        SetUniformInt(buffer, (int)Light::lights[i]->category);
        sprintf_s(buffer, "lights[%i].angle", i);
        SetUniformFloat(buffer, 5.0f);
    }
}

void FlatSubstance::Bind()
{
    //Use this program.
    glUseProgram(program);
}
