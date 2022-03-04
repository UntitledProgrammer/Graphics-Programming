#include "DepthSubstace.h

DepthSubstance::DepthSubstance()
{
    colour = glm::vec3(1, 1, 1);
}

DepthSubstance::~DepthSubstance()
{

}

bool DepthSubstance::Load(const std::string location)
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

void DepthSubstance::Update(Transform& transform)
{
    //Mesh:
    SetUniformMat4("model", transform.GetMatrix());
    SetUniformMat4("lightSpaceModel", lightSpaceMatrix);
}

void DepthSubstance::Bind()
{
    //Use this program.
    glUseProgram(program);
}
