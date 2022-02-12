#include "Camera.h"
Camera* Camera::defaultInstance = 0;

glm::mat4 Camera::GetMatrix()
{
    recalculate();

    return glm::lookAt(transform.position, glm::vec3(0), up);
}

Camera::Camera() : perspective(glm::mat4(1)) 
{ 
    transform = Transform();
    perspective = glm::perspective(fov, aspect, 1.0f, 100.0f);
    transform.position = glm::vec3(0.0f, 0.0f, 2.0f);
    recalculate();

    simulatedBodies.push_back(this);
};

Camera::~Camera()
{

}

void Camera::recalculate()
{
    //Update the direction vectors first.
    forward = glm::normalize(glm::vec3(0) - transform.position);
    right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    up = glm::cross(forward, right);

    //Calculate and update view matrix.
    view = glm::lookAt(transform.position, glm::vec3(0), up);
}

void Camera::Update()
{
    up = glm::cross(glm::normalize(glm::vec3(0) - transform.position), glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward)));
    view = glm::lookAt(transform.position, glm::vec3(0), up);
}

Camera* Camera::Instance()
{
    if (!defaultInstance) defaultInstance = new Camera();
    return defaultInstance;
}