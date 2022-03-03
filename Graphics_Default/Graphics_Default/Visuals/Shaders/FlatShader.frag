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

//Uniforms:
uniform int SIZE;
uniform Light lights[NUMBER_OF_LIGHTS];

//In's:
in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertexPos;

//Added:
uniform vec3 cameraPosition;

//Out's:
out vec4 colour;

//Functions:
float mag(vec3 v) { return sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)); }

vec3 AddPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	float d = distance(light.position, fragPos) * 1000;
    vec3 ambient = min(vec3(light.colour.x / d, light.colour.y / d, light.colour.z / d)* AMBIENT_STRENGTH, 0);

	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.colour;

	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(10.0f * spec);

	return vec3 (ambient + diffuse + specular);
}


void main()
{
	vec3 direction = vec3(lights[0].position - vertexPos);
	vec3 ambient = vec3(1,1,1) * AMBIENT_STRENGTH;
	float diff = max(dot(direction, -fragNormal), 0.0);
	vec3 diffuse = diff * lights[0].colour;

	colour = vec4(vec3(abs(fragNormal.x),abs(fragNormal.y), abs(fragNormal.z)) , 1);
}