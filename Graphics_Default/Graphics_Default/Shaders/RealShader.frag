#version 460

struct Light
{
	vec3 position;
	vec3 colour;
	vec3 direction;
};

#define NUMBER_OF_LIGHTS 4
#define AMBIENT_STRENGTH 0.5f
#define SPECULAR_STRENGTH 1

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform Light lights[NUMBER_OF_LIGHTS];
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec3 fragPos;
in mat3 TBN;

out vec4 colour;

//Added:
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

//Method:
vec3 AddLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 ambient = AMBIENT_STRENGTH * light.colour;
	vec3 lightDir = normalize((lightPosition - fragPos));
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.colour;

	//Specular:
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(SPECULAR_STRENGTH * spec);


	return vec3 (ambient + diffuse + specular);
}

void main()
{
	//Calculate view direction:
	vec3 viewDir = normalize(cameraPosition - fragPos);

	//Calculate normal:
	vec3 normal = normalize(texture2D(texture_normal, fragTextureCoordinates).rgb);
	normal = normalize((normal * 2.0)-1.0);
	normal = normalize(TBN * normal);

	vec3 result;
	for(int i = 0; i < NUMBER_OF_LIGHTS; i++)
	{
		result += AddLight(lights[i], normal, fragPos, viewDir);
	}




	colour = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * result, 1);
}