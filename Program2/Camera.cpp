#include "Camera.h"


Camera::Camera(glm::vec4 position, glm::vec4 direction, glm::vec4 up)
{
	setViewPoint(position, direction, up);
}


Camera::~Camera()
{
}


glm::mat4 Camera::getViewMatrix()
{
	return viewingTransformation;

}

void Camera::setViewPoint(glm::vec4 position, glm::vec4 direction, glm::vec4 up)
{
	this->position = position;
	this->direction = direction;
	this->up = up;

	viewingTransformation = glm::lookAt( glm::vec3(position.xyz), 
										 glm::vec3(position.xyz + direction.xyz), 
										 glm::vec3(up.xyz));
}

void Camera::update(float elapsedTimeSeconds)
{
	this->modelMatrix = glm::inverse(viewingTransformation);

	VisualObject::update(elapsedTimeSeconds);

	
}

 