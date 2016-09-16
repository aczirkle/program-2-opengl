#pragma once
#include "VisualObject.h"
class Camera :
	public VisualObject
{
public:
	
	Camera(glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 
		   glm::vec4 direction = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f),
		   glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	~Camera();

	virtual glm::mat4 getViewMatrix();

	virtual void setViewPoint( glm::vec4 position, 
					   glm::vec4 direction, 
					   glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	virtual void update(float elapsedTimeSeconds);

	glm::mat4 viewingTransformation;

	glm::vec4 direction;
	glm::vec4 position;
	glm::vec4 up;

};

