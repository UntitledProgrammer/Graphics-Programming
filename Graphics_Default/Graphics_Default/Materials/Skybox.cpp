#include "Skybox.h"

Skybox::Skybox()
{

}

Skybox::~Skybox()
{
}

bool Skybox::Load(const std::string location)
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

    uniforms[PROJECTION] = glGetUniformLocation(program, "projection");
    uniforms[VIEW] = glGetUniformLocation(program, "view");
    uniforms[SKYBOX] = glGetUniformLocation(program, "skybox");

    return true;
}

void Skybox::Update(Transform& transform)
{
    glUniformMatrix4fv(uniforms[PROJECTION], 1, GL_FALSE, &Camera::Instance()->perspective[0][0]);
    glUniformMatrix4fv(uniforms[VIEW], 1, GL_FALSE, &Camera::Instance()->view[0][0]);
}

void Skybox::Bind()
{
    glUseProgram(program);

    //glDepthMask(GL_FALSE);
    //glActiveTexture(GL_TEXTURE0);

    glActiveTexture(cubemap->id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->id);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDepthMask(GL_TRUE);
}

void Skybox::SetFace(CubeFace position, std::string location)
{
    //textures[position]->Load(location);
}
