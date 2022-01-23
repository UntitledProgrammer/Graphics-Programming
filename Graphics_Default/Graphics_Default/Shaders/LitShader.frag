#version 450

uniform sampler2D texture_diffuse;
in vec2 fragTextureCoordinates;
out vec4 colour;

//Added:
uniform vec3 fragLightColour;
uniform vec3 fragLightPos;
uniform vec3 fragCamPos;

void main()
{
	colour = vec4( texture2D(texture_diffuse, fragTextureCoordinates).rgb, 1);
}