#include "SurfaceMaterial.h"

SurfaceMaterial::SurfaceMaterial()
{
}

SurfaceMaterial::~SurfaceMaterial()
{
}

bool SurfaceMaterial::Load(const std::string location)
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
    uniforms[FRAG_LIGHTCOLOUR] = glGetUniformLocation(program, "fragLightColour");
    uniforms[FRAG_LIGHTPOS] = glGetUniformLocation(program, "fragLightPos");

    //Lighting:
    for (GLuint i = 0; i < NUM_UNIFORMS; i++)
    {
        if (uniforms[i] == GL_INVALID_INDEX) std::cout << "Shader " << name << " uniform invalid index: " << static_cast<UniformNames>(i) << " (Might be optimized out if not used)" << std::endl;
    }

	return false;
}

void SurfaceMaterial::Update(Transform& transform)
{
    //Mesh:
    SetUniformMat4("model", transform.GetMatrix());

    //Camera:
    SetUniformMat4("projection", Camera::Instance()->perspective);
    SetUniformMat4("view", Camera::Instance()->view);
    SetUniformVec3("cameraPosition", Camera::Instance()->transform.position);

    //Light:

    for (int i = 0; i < Light::lights.size(); i++)
    { 
        char buffer[64];
        sprintf_s(buffer, "lights[%i].colour", i);
        SetUniformVec3(buffer , Light::lights[i]->colour);
        sprintf_s(buffer, "lights[%i].position", i);
        SetUniformVec3(buffer, Light::lights[i]->transform.position);
    }


    SetUniformVec3("lightColour", Light::Instance()->colour);
    SetUniformVec3("lightPosition", Light::Instance()->transform.position);
}

void SurfaceMaterial::Bind()
{
    //Bind base texture:
    glActiveTexture(GL_TEXTURE0);
    base->Bind("texture_diffuse", program, 0);

    //Bind normal-map texture:
    glActiveTexture(GL_TEXTURE1);
    normal->Bind("texture_normal", program, 1);

    //Use this program.
    glUseProgram(program);
}
