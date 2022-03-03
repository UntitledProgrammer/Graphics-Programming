#version 460

//Inputs:
in vec3 vp;
in vec2 textureCoordinates;
in vec3 Normal;
in vec3 Tangent;
in vec3 BiTangent;

//Uniforms:
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Outputs:
out vec2 fragTextureCoordinates;
out vec3 fragNormal;
out vec3 fragPos;
out vec3 vertPos;

void main()
{
	vertPos = vp;
	fragPos = vec3(model * vec4(vp, 1.0));
	fragNormal = mat3(transpose(inverse(model))) * Normal;
	fragTextureCoordinates = textureCoordinates;
	gl_Position = projection * view * model * vec4(vp, 1.0);
}
