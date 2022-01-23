#include "Shader.h"

Shader::Shader(const std::string location, Camera& camera) : camera(&camera), name(location)
{
    program = glCreateProgram();

    //Add shader types:
    shaders[VERTEX] = CreateShader( LoadShader(location + ".vert") , GL_VERTEX_SHADER);
    shaders[FRAGMENT] = CreateShader(LoadShader(location + ".frag"), GL_FRAGMENT_SHADER);

    //Attach shaders:
    for (GLuint i = 0; i < NUM_SHADER_TYPES; i++)
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

    //Lighting:
    uniforms[FRAG_CAMERAPOS] = glGetUniformLocation(program, "fragCamPos");
    uniforms[FRAG_LIGHTCOLOUR] = glGetUniformLocation(program, "fragLightColour");
    uniforms[FRAG_LIGHTPOS] = glGetUniformLocation(program, "fragLightPos");
    //Lighting:
    
    for (GLuint i = 0; i < NUM_UNIFORMS; i++)
    {
        if (uniforms[i] == GL_INVALID_INDEX) std::cout << "Shader " << name << " uniform invalid index: " << static_cast<UniformNames>(i) << " (Might be optimized out if not used)" << std::endl;
    }
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADER_TYPES; i++)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(program);
}

void Shader::update(Transform& transform)
{
    glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, &transform.matrix()[0][0]);
    glUniformMatrix4fv(uniforms[PROJECTION_U], 1, GL_FALSE, &camera->perspective[0][0]);
    glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, &camera->view[0][0]);
}

void Shader::litUpdate(Transform& transform, Light& light)
{
    glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, &transform.matrix()[0][0]);
    glUniformMatrix4fv(uniforms[PROJECTION_U], 1, GL_FALSE, &camera->perspective[0][0]);
    glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, &camera->view[0][0]);

    glUniform3f(uniforms[FRAG_CAMERAPOS], camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    glUniform3f(uniforms[FRAG_LIGHTCOLOUR], light.colour.x, light.colour.y, light.colour.z);
    glUniform3f(uniforms[FRAG_LIGHTPOS], light.transform.position.x, light.transform.position.y, light.transform.position.z);
}

void Shader::bind()
{
    glUseProgram(program);
}

GLuint Shader::CreateShader(const std::string& source, GLenum type)
{
    //Create a new shader.
    GLuint shader = glCreateShader(type);
    if (shader == 0) std::cerr << "Error: shader creation failed." << std::endl;

    //Compile shader.
    const char* tempSource = source.c_str(); //glShaderSource want's a const char rather than a std::string.
    glShaderSource(shader, 1, &tempSource, NULL);
    glCompileShader(shader);

    //Validate shader:
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed: ");

    return shader;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

std::string Shader::LoadShader(const std::string& filename)
{
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);

    std::string output, line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line); 
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << filename << std::endl;
    }

    return output;
}
