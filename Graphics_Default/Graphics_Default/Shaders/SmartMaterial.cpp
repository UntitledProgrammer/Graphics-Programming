#include "SmartMaterial.h"

void Substance::Delete()
{
    for (unsigned int i = 0; i < SHADER_TYPES; i++)
    {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(program);
}

GLuint Substance::CreateShader(const std::string& source, GLenum type)
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

void Substance::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

std::string Substance::LoadShader(const std::string& filename)
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
