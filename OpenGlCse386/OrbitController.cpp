#include "OrbitController.h"


OrbitController::OrbitController( glm::vec3 pos, glm::vec3 planeRot, glm::vec3 tumbleRot, GLfloat r) : rotation(0.0f) 
{
	this->position = pos;
	this->planeRotation = planeRot;
	this->tumbleRotation = tumbleRot;
	this->rate = r;
}

void
OrbitController::update(float elapsedTimeSec)
{
	rotation += elapsedTimeSec * rate;
	target->modelMatrix = glm::rotate(glm::mat4(1.0f), fmod(rotation, 360.0f), planeRotation) *
		glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), fmod(rotation * 3, 360.0f), tumbleRotation);
}