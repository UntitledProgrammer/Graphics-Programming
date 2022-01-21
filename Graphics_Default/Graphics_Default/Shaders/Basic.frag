#version 450

uniform sampler2D texture_diffuse;
in vec2 fragTextureCoordinates;
out vec4 colour;

void main()
{
	colour = vec4( texture2D(texture_diffuse, fragTextureCoordinates).rgb, 1);
}