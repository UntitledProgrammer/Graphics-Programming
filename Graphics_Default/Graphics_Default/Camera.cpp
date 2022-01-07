#include "Camera.h"

glm::vec3 Camera::forward()
{
    return glm::normalize(glm::vec3(0) - transform.position);
}

glm::vec3 Camera::up()
{
    return glm::normalize(glm::cross(glm::vec3(0, 1, 0), forward()));
}

glm::vec3 Camera::right()
{
    return glm::cross(forward(), right());
}

glm::mat4 Camera::matrix()
{
    return glm::lookAt(transform.position, glm::vec3(0), up());
}

Camera::Camera() : transform(Transform()), perspective(glm::mat4()) {};

Camera::~Camera()
{

}
