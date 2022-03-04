#version 460

//Structures:
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
uniform sampler2D texture_shadow;
uniform int SIZE;
uniform Light lights[NUMBER_OF_LIGHTS];

//Inputs:
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec3 fragPos;
in vec3 vertPos;

//Outputs:
out vec4 colour;

float mag(vec3 v) { return sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)); }

void main()
{

	vec3 ambient = lights[0].colour * AMBIENT_STRENGTH;

	vec3 lightDir = normalize(lights[0].position - vertPos);

	float diff = max(dot(lightDir, -fragNormal), 0.0);
	vec3 diffuse = diff * lights[0].colour;

	vec3 reflectDir = reflect(lightDir, fragNormal);
	float spec = pow(max(dot(fragNormal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(0.5f * spec);

	colour = vec4(vec3(ambient + diffuse + specular), 1);
	//colour = vec4(texture2D(texture_shadow, fragTextureCoordinates).rgb, 0);
}