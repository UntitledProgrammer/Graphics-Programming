#version 460
//In's:
in vec3 vp;
in vec2 textureCoordinates;
in vec3 Normal;
in vec3 Tangent;
in vec3 BiTangent;

//Uniforms:
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Out's:
out vec3 fragNormal;
out vec3 fragColour;
out vec3 fragPos;
out vec3 vertexPos;

void main()
{
	gl_Position = projection * view * model * vec4(vp, 1.0);
	vertexPos = vp;
	fragPos = vec3(model * vec4(vp, 1.0));
	fragNormal = Normal; //mat3(transpose(inverse(model))) * Normal;
}
