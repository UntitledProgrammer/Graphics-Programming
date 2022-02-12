#version 460

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec3 fragPos;
in mat3 TBN;
out vec4 colour;

//Added:
uniform vec3 fragLightColour;
uniform vec3 fragLightPos;
uniform vec3 fragCamPos;

void main()
{
//Ambient:
	float ambientStrength = 0.8;
	vec3 ambient = ambientStrength * fragLightColour;

	//Diffuse:
	//vec3 normal = normalize(fragNormal);
	vec3 normal = normalize(texture2D(texture_normal, fragTextureCoordinates).rgb);
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	vec3 lightDir = normalize(fragLightPos - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * fragLightColour;

	//Specular:
	float specularStrength = 3.0f;
	vec3 viewDir = normalize(fragCamPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 64.0);
	vec3 specular = vec3(specularStrength * spec);

	vec4 result = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * (ambient + diffuse + spec), 1);
	colour = result;
	colour = vec4(texture2D(texture_normal, fragTextureCoordinates).rgb,1);
}