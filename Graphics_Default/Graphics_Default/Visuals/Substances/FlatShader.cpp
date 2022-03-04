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
    SetUniformLights();
}

void FlatSubstance::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    GLuint TextureLoc = glGetUniformLocation(program, "texture_shadow");
    glUniform1i(TextureLoc, 0);
    glBindTexture(GL_TEXTURE_2D, shadowID);

    //Use this program.
    glUseProgram(program);
}
