#include "Camera.h"

glm::mat4 Camera::matrix()
{
    Recalculate();

    return glm::lookAt(transform.position, glm::vec3(0), up);
}

Camera::Camera() : transform(Transform()), perspective(glm::mat4()) { Recalculate(); };

Camera::~Camera()
{

}

void Camera::Recalculate()
{
    //Update the direction vectors first.
    forward = glm::normalize(glm::vec3(0) - transform.position);
    right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward));
    up = glm::cross(forward, right);

    //Calculate and update view matrix.
    view = glm::lookAt(transform.position, glm::vec3(0), up);
}
