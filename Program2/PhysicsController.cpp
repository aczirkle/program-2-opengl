#include "PhysicsController.h"
#include "OpenGLApplicationBase.h"

PhysicsController::PhysicsController(void){gravity=-10;}
PhysicsController::PhysicsController(float grav){gravity=grav;}
PhysicsController::PhysicsController(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc)
{
	gravity=-10;
	position = pos;
	velocity= vel;
	acceleration=acc;
}

PhysicsController::PhysicsController(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc, float grav)
{
	gravity=grav;
	position = pos;
	velocity= vel;
	acceleration=acc;
}

void PhysicsController::launch(glm::vec3 start, glm::vec3 direction, float speed){

	acceleration = glm::vec3(0.f,gravity,0.f);
	velocity=  glm::normalize(direction)*speed;//direction*speed;
	position= start;
	
}

void PhysicsController::launchDir(glm::vec3 start, glm::mat4 direction, float speed){

	acceleration = glm::vec3(0.f,gravity,0.f);
	//velocity=  glm::normalize(direction)*speed;//direction*speed;
	position= start;
	
}

void PhysicsController::update(float elapsedTimeSeconds){
	if(position.y <=-2.f){
		position.y=-2.f;
		velocity = glm::reflect(velocity,glm::vec3(0.f,1.f,0.f));
	}
	velocity += acceleration *elapsedTimeSeconds;
	position += velocity*elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.f),position);
}

