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
uniform int SIZE;
uniform Light lights[NUMBER_OF_LIGHTS];
in vec2 fragTextureCoordinates;
in vec3 fragNormal;
in vec3 fragPos;
in mat3 TBN;
in vec3 testNormal;
in vec3 Tang;
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
	vec3 lightDirection = normalize(light.position - fragPos);
	float theta = dot(lightDirection, normalize(-light.direction));
	float angle = degrees(acos(dot(light.position, fragPos) / (mag(light.position) * mag(fragPos))));

	if(angle >= light.angle) return vec3(0,0,0);

	//Diffuse:
	vec3 diffuse = max(dot(normal, light.direction), 0.0) * light.colour;
	vec3 reflectDir = reflect(-lightDirection, normal);

	//Specular:
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(SPECULAR_STRENGTH * spec);

	return vec3(diffuse + specular);
}

vec3 AddPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 ambient = 0.1 * light.colour;

	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.colour;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(normal, reflectDir), 0.0), 32.0);
	vec3 specular = vec3(10.0f * spec);

	return vec3 (ambient + diffuse + specular);
}


void main()
{
	//Calculate view direction:
	vec3 viewDir = normalize(cameraPosition - fragPos);



	//Calculate bump normal:
	vec3 normal = normalize(testNormal);
	vec3 Tan = normalize(Tang);
	Tan = normalize(Tan - dot(Tan, normal) * normal);
	vec3 BiTan = cross(Tan, testNormal);
	vec3 bumpNormal = texture(texture_normal, fragTextureCoordinates).xyz;
	bumpNormal = 2.0 * bumpNormal - vec3(1.0,1.0,1.0);
	vec3 NewNormal;
	mat3 TBN = mat3(Tan, BiTan, normal);
	NewNormal = TBN * bumpNormal;
	NewNormal = normalize(NewNormal);

	vec3 result;
	for(int i = 0; i < NUMBER_OF_LIGHTS; i++)
	{
		if(lights[i].type == Directional) result += AddPointLight(lights[i], NewNormal, fragPos, viewDir);
		else if(lights[i].type == Phong) result += AddPointLight(lights[i], NewNormal, fragPos, viewDir);
	}

	colour = vec4(texture2D(texture_diffuse, fragTextureCoordinates).rgb * result, 1);
}