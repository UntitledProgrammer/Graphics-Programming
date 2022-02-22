#version 460

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec3 fragPos;
in mat3 TBN;
out vec4 colour;

//Added:
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
//Ambient:
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColour;

	//Diffuse:
	vec3 normal = normalize(fragNormal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	//Specular:
	float specularStrength = 1f;
	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(specularStrength * spec);

	colour = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * (ambient + diffuse + spec), 1);
}