#version 460
out vec4 FragColour;

//Added:
uniform vec3 lightColour;
uniform vec3 surfaceColour;

void main()
{
	FragColour = vec4(surfaceColour * lightColour, 1.0);
}