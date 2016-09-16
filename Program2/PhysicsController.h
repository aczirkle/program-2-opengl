#pragma once
#include "Controller.h"
#include "OpenGLApplicationBase.h"
class PhysicsController :
	public Controller
{
public:
	PhysicsController(void);
	PhysicsController(float grav);
	PhysicsController(glm::vec3 pos, glm::vec3 vec, glm::vec3 acc);
	PhysicsController(glm::vec3 pos, glm::vec3 vec, glm::vec3 acc,float grav);
	void launch(glm::vec3 start, glm::vec3 direction, float speed);
	void launchDir(glm::vec3 start, glm::mat4 direction, float speed);
	void update(float elapsedTimeSeconds);
protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	GLfloat gravity;
};

