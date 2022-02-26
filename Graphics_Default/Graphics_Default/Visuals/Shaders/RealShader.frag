#version 460

struct Light
{
	vec3 position;
	vec3 colour;
	vec3 direction;
	float angle;
	unsigned int type;
};

//Defines:
#define NUMBER_OF_LIGHTS 4
#define AMBIENT_STRENGTH 0.5f
#define SPECULAR_STRENGTH 1
//Light Enum: (Update at a later date).
#define Phong 0
#define Directional 1
#define TYPES_OF_LIGHTS 2

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
float mag(vec3 v) { return sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)); }
//Method:
vec3 AddPhong(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	float d = distance(light.position, fragPos);

	vec3 ambient = min(vec3(light.colour.x / d, light.colour.y / d, light.colour.z / d)* AMBIENT_STRENGTH, 0);
	vec3 lightDir = normalize((light.position - fragPos));
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.colour;

	//Specular:
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(SPECULAR_STRENGTH * spec);


	return vec3 (ambient + diffuse + specular);
}

vec3 AddDirectional(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//Ambient:
	//vec3 ambient = vec3(light.colour * AMBIENT_STRENGTH);
	vec3 direction = normalize(-light.direction);

	//Diffuse:
	vec3 diffuse = max(dot(normal, direction), 0.0) * light.colour;
	vec3 reflectDir = reflect(-direction, normal);

	//Specular:
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(SPECULAR_STRENGTH * spec);

	return vec3(specular + diffuse);
}

vec3 AddSpotlight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//Calcuate angle:
	vec3 lightDirection = normalize(-light.direction);
	vec3 fragDirection = normalize(light.position - fragPos);
	//float angle = degrees(acos(dot(lightDirection, fragDirection) / (mag(lightDirection) * mag(fragDirection))));

	//if(angle == light.angle) return vec3(0,0,0);

	//Diffuse:
	vec3 diffuse = max(dot(normal, lightDirection), 0.0) * light.colour;
	vec3 reflectDir = reflect(-lightDirection, normal);

	//Specular:
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(SPECULAR_STRENGTH * spec);

	return vec3(specular + diffuse);
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
		if(lights[i].type == Directional) result += AddSpotlight(lights[i], normal, fragPos, viewDir);
		else if(lights[i].type == Phong) result += AddSpotlight(lights[i], normal, fragPos, viewDir);
	}

	colour = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * result, 1);
}