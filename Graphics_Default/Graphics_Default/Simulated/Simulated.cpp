#include "Simulated.h"
#include"../Simulated/Camera.h"
void Simulated::UpdateExtensions()
{
	for (int i = 0; i < extensions.size(); i++) { if(extensions[i]->active) extensions[i]->Update(); }
}

void Simulated::Initialise()
{
	for (int i = 0; i < extensions.size(); i++) { extensions[i]->Initialise(); }
}

void Simulated::DrawCentre(float scale)
{
	Camera* camera = Camera::Instance();
	const float length = 1.0;
	//Setup:
	glUseProgram(0); //Do not use a current shader program.

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&camera->perspective); //In the perspective matrix above load the camera's current perspective.
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = camera->view * transform.GetMatrix();
	glLoadMatrixf((const GLfloat*)&MV[0]);

	//Draw:
	glBegin(GL_LINES);
	glm::vec3 p1 = transform.position, p2 = p1;

	//Red line.
	glColor3f(1, 0, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(length, 0, 0) * scale;
	glColor3f(1, 0, 0);// Green.
	glVertex3fv(&p2.x);

	//Green line.
	glColor3f(0, 1, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, length, 0) * scale;
	glColor3f(0, 1, 0);// Green.
	glVertex3fv(&p2.x);

	//Blue line.
	glColor3f(0, 0, 1); //Blue.
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 0, length) * scale;
	glColor3f(0, 0, 1);
	glVertex3fv(&p2.x);
	glEnd();
}