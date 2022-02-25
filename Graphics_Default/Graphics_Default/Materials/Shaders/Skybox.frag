#version 460
out vec4 FragColour;
in vec3 TexCoords;
uniform samplerCube skybox;

void main()
{             
    FragColour = vec4(texture(skybox, TexCoords).rgb, 1);
}  