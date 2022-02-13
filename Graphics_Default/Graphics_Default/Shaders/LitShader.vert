#version 460

in vec3 vp;
in vec2 textureCoordinates;
in vec3 Normal;
in vec3 Tangent;
in vec3 BiTangent;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 forward;

out vec2 fragTextureCoordinates;
out vec3 fragNormal;
out vec3 fragPos;
out mat3 TBN;

void main()
{
	//TBN:
	vec3 T = normalize(vec3(model * vec4(Tangent, 0.0)));
	vec3 B = normalize(vec3(model * vec4(BiTangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(Normal, 0.0)));

	TBN = mat3(T,B,N);

	fragPos = vec3(model * vec4(vp, 1.0));
	fragNormal = mat3(transpose(inverse(model))) * Normal;

	fragTextureCoordinates = textureCoordinates;
	gl_Position = projection * view * model * vec4(vp, 1.0);
}
