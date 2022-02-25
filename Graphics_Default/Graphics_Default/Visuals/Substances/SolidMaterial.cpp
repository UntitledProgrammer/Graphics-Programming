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


    uniforms[MODEL_U] = glGetUniformLocation(program, "model");
    uniforms[PROJECTION_U] = glGetUniformLocation(program, "projection");
    uniforms[VIEW_U] = glGetUniformLocation(program, "view");
    uniforms[FORWARD] = glGetUniformLocation(program, "forward");

    //Lighting:
    uniforms[FRAG_CAMERAPOS] = glGetUniformLocation(program, "fragCamPos");
    uniforms[FRAG_LIGHTCOLOUR] = glGetUniformLocation(program, "lightColour");
    uniforms[SURFACE_COLOUR] = glGetUniformLocation(program, "surfaceColour");

    //Lighting:
    for (GLuint i = 0; i < NUM_UNIFORMS; i++)
    {
        if (uniforms[i] == GL_INVALID_INDEX) std::cout << "Shader " << name << " uniform invalid index: " << typeid(static_cast<UniformNames>(i)).name() << " (Might be optimized out if not used)" << std::endl;
    }

    return true;
}

void SolidMaterial::Update(Transform& transform)
{
    glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, &transform.GetMatrix()[0][0]);
    glUniformMatrix4fv(uniforms[PROJECTION_U], 1, GL_FALSE, &Camera::Instance()->perspective[0][0]);
    glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, &Camera::Instance()->view[0][0]);

    glUniform3f(uniforms[FRAG_CAMERAPOS], Camera::Instance()->transform.position.x, Camera::Instance()->transform.position.y, Camera::Instance()->transform.position.z);
    glUniform3f(uniforms[FRAG_LIGHTCOLOUR], Light::Instance()->colour.x, Light::Instance()->colour.y, Light::Instance()->colour.z);
    glUniform3f(uniforms[FRAG_LIGHTPOS], Light::Instance()->transform.position.x, Light::Instance()->transform.position.y, Light::Instance()->transform.position.z);
    glUniform3f(uniforms[FORWARD], Camera::Instance()->transform.position.x, Camera::Instance()->transform.position.y, Camera::Instance()->transform.position.z + 0.5f);
    glUniform3f(uniforms[SURFACE_COLOUR], colour.x, colour.y, colour.z);
}

void SolidMaterial::Bind()
{
    //Use this program.
    glUseProgram(program);
}
