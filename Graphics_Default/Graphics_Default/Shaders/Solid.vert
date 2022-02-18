#version 460

in vec3 vp;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 forward;

void main()
{
	gl_Position = projection * view * model * vec4(vp, 1.0);
}