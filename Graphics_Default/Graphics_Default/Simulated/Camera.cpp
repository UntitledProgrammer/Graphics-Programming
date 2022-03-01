#include "Camera.h"
#include<iostream>
Camera* Camera::defaultInstance = 0;

glm::mat4 Camera::GetModel()
{
    return glm::lookAt(transform.position, transform.position + glm::vec3(0,0,0.01), up);
}

Camera::Camera() : perspective(glm::mat4(1)) 
{ 
    transform = Transform();
    perspective = glm::perspective(glm::radians(fov), aspect, 1.0f, 100.0f);
    transform.position = glm::vec3(0.0f, 0.0f, 2.0f);
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0);

    SetName("Camera");
};

Camera::~Camera()
{

}

void Camera::recalculate()
{
    //Update the direction vectors first.
    forward = glm::normalize(glm::vec3(0) - transform.position);
    right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), Direction() ));
    up = glm::cross(Direction(), right);

    //Calculate and update view matrix.
    view = glm::lookAt(transform.position, transform.rotation, up);
}

void Camera::Update()
{
    UpdateExtensions();
    //Update the direction vectors first.
    //forward = glm::normalize(glm::vec3(0) - transform.position);
    //right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), Direction()));
    //up = glm::cross(Direction(), right);

    //Calculate and update view matrix.
    view = glm::lookAt(transform.position, transform.position + forward, -up);
}

Camera* Camera::Instance()
{
    if (!defaultInstance) defaultInstance = new Camera();
    return defaultInstance;
}