#version 460

in vec3 vp;
in vec2 coordinates;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 textureCoordinates;

void main()
{
	textureCoordinates = coordinates;
	gl_Position = projection * view * model * vec4(vp, 1.0);
}
