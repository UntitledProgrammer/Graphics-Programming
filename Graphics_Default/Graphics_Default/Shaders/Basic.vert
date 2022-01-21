#version 450
in vec3 vp;
in vec2 txCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vp, 1.0);
}
