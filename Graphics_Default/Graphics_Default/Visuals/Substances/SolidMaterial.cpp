#include "SolidMaterial.h"

SolidMaterial::SolidMaterial()
{
}

SolidMaterial::~SolidMaterial()
{
}

bool SolidMaterial::Load(const std::string location)
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

    return true;
}

void SolidMaterial::Update(Transform& transform)
{
    //Mesh:
    SetUniformMat4("model", transform.GetMatrix());
    SetUniformVec3("surfaceColour", colour);
    //Camera:
    SetUniformMat4("projection", Camera::Instance()->perspective);
    SetUniformMat4("view", Camera::Instance()->view);
}

void SolidMaterial::Bind()
{
    if (!base) { glUseProgram(program); return; }
    //Use this program.
    glActiveTexture(GL_TEXTURE0);
    base->Bind("texture_diffuse", program, 0);
    glUseProgram(program);
}
