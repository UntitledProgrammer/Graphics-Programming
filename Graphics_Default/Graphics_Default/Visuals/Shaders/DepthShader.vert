#version 460

//Inputs:
in vec3 position;

//Uniforms:
uniform mat4 model;
uniform mat4 lightSpaceModel;

void main()
{
	gl_Position = lightSpaceModel * model * vec4(position, 1.0f);
}