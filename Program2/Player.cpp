#include "Camera.h"
#include "Player.h"


/*class Player : public Camera
{
public:




}*/

Player::Player(glm::vec4 position, float heading, float speed )
: Camera(position), heading(heading), speed(speed)
{
     rotateView();
}

void Player::accelerate(glm::vec3 dir){
	acceleration = acceleration + dir;
}


void Player::rotateView()
{
     this->direction = glm::rotate(glm::mat4(1.0f), heading, -glm::vec3(this->up.xyz)) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

     setViewPoint(this->position, this->direction, this->up);

}

 

void Player::moveForward()
{
     position = position + direction * speed;

     setViewPoint(position, direction, up);

}

void Player::moveBackward()
{
   //  acceleration = glm::vec4(0,0,0,0);
	position = position - direction * speed;

     setViewPoint(position, direction, up);

}

void Player::moveRight()
{
     vec3 right = glm::normalize(glm::cross(glm::vec3(direction.xyz), glm::vec3(up.xyz)));

     position = position + vec4(right,1.0f) * speed;

     setViewPoint(position, direction, up);


}

void Player::moveLeft()
{
     vec3 right = -glm::normalize(glm::cross(glm::vec3(direction.xyz), glm::vec3(up.xyz)));

     position = position + vec4(right,1.0f) * speed;

     setViewPoint(position, direction, up);


}
void Player::update(float elapsedTimeSec){


	this->modelMatrix = glm::inverse(viewingTransformation);

	VisualObject::update(elapsedTimeSec);
}


void Player::rotateRight()
{
     heading += 10.0;

     rotateView();
}
