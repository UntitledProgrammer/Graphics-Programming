#version 450

uniform sampler2D texture_diffuse;
in vec2 fragTextureCoordinates;
in vec3 normal;
out vec4 colour;

//Added:
uniform vec3 fragLightColour;
uniform vec3 fragLightPos;
uniform vec3 fragCamPos;

//Ambient lighting:
float ambientStrength = 0;
vec3 ambient = ambientStrength * fragLightColour;

void main()
{
	float ambientStrength = 2;
	vec3 ambient = ambientStrength * fragLightColour;

	vec4 result = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * ambient, 1);
	colour = result;
}