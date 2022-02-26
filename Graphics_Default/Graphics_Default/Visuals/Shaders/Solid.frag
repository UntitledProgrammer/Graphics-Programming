#version 460
out vec4 colour;

//Added:
uniform sampler2D texture_diffuse;
uniform vec3 surfaceColour;

in vec2 textureCoordinates;

void main()
{
	colour = vec4(surfaceColour * texture2D(texture_diffuse, textureCoordinates).rgb, 1.0);
}