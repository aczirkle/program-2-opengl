#include "SpinnerController.h"

SpinnerController::SpinnerController( glm::vec3 pos, glm::vec3 ax, GLfloat r) : rotation(0.0f) 
{
	this->position = pos;
	this->axis = ax;
	this->rate = r;
}

void
SpinnerController::update(float elapsedTimeSec)
{
	rotation += elapsedTimeSec * rate;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::rotate( glm::mat4(1.0f),
			fmod(rotation, 360.0f),
			axis);
}