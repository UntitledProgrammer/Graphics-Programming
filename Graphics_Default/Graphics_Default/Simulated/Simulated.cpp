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
	//Setup:
	glUseProgram(0); //Do not use a current shader program.

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&MainCamera->perspective); //In the perspective matrix above load the camera's current perspective.
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 viewMatrix = MainCamera->view * transform.GetMatrix();
	glLoadMatrixf((const GLfloat*)&viewMatrix[0]);

	//Draw:
	glBegin(GL_LINES);
	glm::vec3 centre = glm::vec3(transform.GetMatrix()[0][3], transform.GetMatrix()[1][3], transform.GetMatrix()[2][3]), end = centre;

	//Red line.
	glColor3f(1, 0, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&centre.x);
	end = centre + glm::vec3(scale, 0, 0);
	glColor3f(1, 0, 0);// Green.
	glVertex3fv(&end.x);

	//Green line.
	glColor3f(0, 1, 0); //Red. (0.0f - 1.0f : 0 - 255).
	glVertex3fv(&centre.x);
	end = centre + glm::vec3(0, scale, 0);
	glColor3f(0, 1, 0);// Green.
	glVertex3fv(&end.x);

	//Blue line.
	glColor3f(0, 0, 1); //Blue.
	glVertex3fv(&centre.x);
	end = centre + glm::vec3(0, 0, scale);
	glColor3f(0, 0, 1);
	glVertex3fv(&end.x);
	glEnd();
}