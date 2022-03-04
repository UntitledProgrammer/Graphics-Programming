#include "LightBase.h"
std::vector<Light*> Light::lights = std::vector<Light*>();

Light* Light::defaultInstance = 0;

Light* Light::Instance()
{
	if (!defaultInstance) defaultInstance = new Light();
	return defaultInstance;
}

Light::Light()
{
	SetName("Light");
	lights.push_back(this);
	colour = glm::vec3(1, 1, 1);
}

Light::Light(std::string name, LightCategory category, glm::vec3 colour) : colour(colour)
{
	this->category = category;
	this->SetName(name);
	lights.push_back(this);
}

Light::~Light()
{

}

void Light::Draw()
{
	Camera* camera = Camera::Instance();
	//Setup:
	glUseProgram(0); //Do not use a current shader program.
	const float scale = 0.5f;

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&camera->perspective); //In the perspective matrix above load the camera's current perspective.
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = camera->view * transform.GetMatrix();
	glLoadMatrixf((const GLfloat*)&MV[0]);

	//Draw:
	glBegin(GL_LINES);
	glm::vec3 p1 = transform.position, p2 = p1;

	//Red line.
	glColor3f(2, 0, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(1, 0, 0) * scale;
	glColor3f(2, 0, 0);
	glVertex3fv(&p2.x);

	//Green line.
	glColor3f(0, 2, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 1, 0) * scale;
	glColor3f(0, 2, 0);// Green.
	glVertex3fv(&p2.x);

	//Blue line.
	glColor3f(0, 0, 2); //Blue.
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 0, 1) * scale;
	glColor3f(0, 0, 2);
	glVertex3fv(&p2.x);
	glEnd();
}

void Light::Update()
{
	//Draw lines:
	Camera* camera = Camera::Instance();
	//Setup:
	glUseProgram(0); //Do not use a current shader program.
	const float scale = 0.1f;

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&camera->perspective); //In the perspective matrix above load the camera's current perspective.
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = camera->view * transform.GetMatrix();
	glLoadMatrixf((const GLfloat*)&MV[0]);

	//Draw:
	glBegin(GL_LINES);
	glm::vec3 p1 = transform.position, p2 = p1;

	//Red line.
	glColor3f(2, 0, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(1, 0, 0) * scale;
	glColor3f(0, 2, 0);// Green.
	glVertex3fv(&p2.x);

	//Green line.
	glColor3f(0, 2, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 1, 0) * scale;
	glColor3f(0, 1, 0);// Green.
	glVertex3fv(&p2.x);

	//Blue line.
	glColor3f(0, 0, 2); //Blue.
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 0, 1) * scale;
	glColor3f(0, 0, 1);
	glVertex3fv(&p2.x);
	glEnd();
}

glm::mat4 Light::GetProjectionMatrix()
{
	glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(transform.position, glm::vec3(0), glm::vec3(0, 1, 0)); //Note, add method to get position directly from matrix.
	glm::mat4 lightSpaceMatrix = lightProjection * lightView; //Note, implement these calculations into the light class.

	return lightSpaceMatrix;
}
