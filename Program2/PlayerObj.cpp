#include "PlayerObj.h"

PlayerObj::PlayerObj(){}

PlayerObj::PlayerObj(glm::vec3 position, vec3 heading, float speed ){
	//decel = 10;
	this->rotac = vec3(0,0,0);
	this->rotvel= vec3(0,0,0);
	this->rotpos= vec3(0,0,0);
	this->position = position;
	this->heading = heading;
	this->speed=speed;
	jumping =false;
	//this->cam= new Camera(vec4(position,1),vec4(heading,1),glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

/*PlayerObj::PlayerObj(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc)
{
	decel = 10;
	position = pos;
	velocity= vel;
	acceleration=acc;
}*/

void PlayerObj::launch(glm::vec3 start, glm::vec3 direction, float speed){

	//acceleration = glm::vec3(0.f,this->acceleration,0.f);
	velocity=  direction*speed;//glm::normalize((direction) *speed);
	position= start;
	
}

void PlayerObj::rotateRight(){
	if(!rotvel.x<=5.0)
	rotvel = vec3(-5,rotvel.y,rotvel.z);
}

void PlayerObj::rotateLeft(){
	if(!rotvel.x>=-5.0)
	rotvel = vec3(5,rotvel.y,rotvel.z);
}

void PlayerObj::rotatePosZ(){
	if(!rotvel.z>=-10.0)
	rotvel = vec3(rotvel.x,rotvel.y,5);
}

void PlayerObj::rotateNegZ(){
	if(!rotvel.z<=10.0)
	rotvel = vec3(rotvel.x,rotvel.y,-5);
}
//urns left
void PlayerObj::rotatePosY(){
	if(!rotvel.y>=-5.0){
	rotvel = vec3(rotvel.x,5,rotvel.z);
	//velocity+=vec3(.001,0,0);
	}
}
//Turns right
void PlayerObj::rotateNegY(){
	if(!rotvel.y<=5.0){
	rotvel = vec3(rotvel.x,-5,rotvel.z);
	//velocity+=vec3(-.001,0,0);
	}

}

void PlayerObj::stopRot(){
	rotvel = vec3(0,0,0);
}

void PlayerObj::moveLeft(){
	if(!velocity.x<=5.0)
	acceleration = vec3(-1,acceleration.y,acceleration.z);
}
void PlayerObj::moveRight(){
	if(!velocity.x>=-5.0)
	acceleration = vec3(1,acceleration.y,acceleration.z);
}
void PlayerObj::moveForward(){
	if(velocity.z>=-5.0)
		acceleration = vec3(acceleration.x,acceleration.y,-1);
}
void PlayerObj::moveBackward(){
	if(velocity.z<=5.0)
	acceleration = vec3(acceleration.x,acceleration.y,1);
}
/*void PlayerObj::moveUp(){
	if(!velocity.y<=5.0)
	//acceleration = acceleration-normalize((heading+ vec3(0,1,0)));
	acceleration = normalize(acceleration+(vec3(0,1,0)));
}*
void PlayerObj::moveDown(){
	if(!velocity.z>=-5.0)
	//acceleration = acceleration+normalize((heading+ vec3(0,-1,0)));
	acceleration = normalize(acceleration+(vec3(0,-1,0)));
}*/
void PlayerObj::moveDown(){
	if(!velocity.z>=-5.0)
	//acceleration = acceleration+normalize((heading+ vec3(0,-1,0)));
	acceleration = vec3(acceleration.x,-2,acceleration.z);
}
void PlayerObj::moveUp(){
	if(!velocity.y<=5.0){
	//acceleration = acceleration-normalize((heading+ vec3(0,1,0)));
	acceleration = vec3(acceleration.x,5,acceleration.z);
	jumping =true;
	}
	else{
		acceleration = vec3(acceleration.x,2,acceleration.z);
	}
	
}
void PlayerObj::ack(){
	int winWid =glutGet(GLUT_SCREEN_WIDTH) ;
	int winHei = glutGet(GLUT_SCREEN_HEIGHT);
	jumping =false;
	glutWarpPointer(winWid/2, winHei/2);
	rotvel=vec3(0,0,0);
	acceleration = vec3(0,0,0);
	velocity = vec3(0,0,0);
}
void PlayerObj::respawn(){
	ack();
	position=vec3(0,0,0);
}

void PlayerObj::jump(){
	jumping= true;
}

void PlayerObj::update(float elapsedTimeSeconds){
	acceleration += glm::vec3(0,-0.5f,0);
	if(jumping){
		acceleration = glm::vec3(acceleration.x,0.f,acceleration.z);
		jumping=false;
	}
	//decel();


	velocity += acceleration *elapsedTimeSeconds;
	//velocity = acceleration *elapsedTimeSeconds;
	//devel();
	position += velocity*elapsedTimeSeconds;
	//some(); //Done with movement
	derot();
	
	//rotvel += rotac *elapsedTimeSeconds;
	rotpos += rotvel*elapsedTimeSeconds;
	if(position.y <-2.f ){
		position.y=-2.f;
		velocity = glm::reflect(velocity,glm::vec3(0.f,1.f,0.f));
	}
	if(position.y >=50.f ){
		position.y=50.f;
		velocity = vec3(velocity.x,0,velocity.z);
	}
	if(position.z <=-50.f ){
		position.z=-50.f;
		velocity = glm::reflect(velocity,glm::vec3(0.f,0.f,1.f));
	}
	if(position.z >=50.f ){
		position.z=50.f;
		velocity = glm::reflect(velocity,glm::vec3(0.f,0.f,1.f));
	}
	if(position.x <=-50.f ){
		position.x=-50.f;
		velocity = glm::reflect(velocity,glm::vec3(1.f,0.f,0.f));
	}
	if(position.x >=50.f ){
		position.x=50.f;
		velocity = glm::reflect(velocity,glm::vec3(1.f,0.f,0.f));
	}
	//if(eye.y<=-2.f){
	//	ack();
	//	position = vec3(0,0,0);
	//}
	//derotVel();
	//Done with rotation
	viewAt();
	//glm::lookAt( glm::vec3(position.xyz), 
	//									 glm::vec3(position.xyz + heading.xyz), 
	//									 glm::vec3(0.0f, 1.0f, 0.0f));
	mat4 rotx = glm::rotate( glm::mat4(1.0f),fmod(heading.x, 360.0f),vec3(rotpos.x,0,0));
	mat4 roty = glm::rotate( glm::mat4(1.0f),fmod(heading.y, 360.0f),vec3(0,rotpos.y,0));
	mat4 rotz = glm::rotate( glm::mat4(1.0f),fmod(heading.z, 360.0f),vec3(0,0,rotpos.z));
	target->modelMatrix = -(glm::translate(glm::mat4(1.f),position))* rotx*roty*roty;
	//target->modelMatrix = (glm::translate(glm::mat4(1.f),position)) ;//* rot;
}
void PlayerObj::viewAt(){
	mat4 viewingTransformation = (glm::lookAt(vec3(position.x,position.y,-position.z), 
										 glm::vec3(/*position.xyz +*/ rotpos.xyz), 
										 glm::vec3(heading.xyz)));
	

	eye = glm::inverse(viewingTransformation)[3].xyz;
	//cout<<"Xeye: "<<eye.x<<endl;
	//cout<<"Yeye: "<<eye.y<<endl;
	//cout<<"Zeye: "<<eye.z<<endl;
}
/**
*Don't use
*/
void PlayerObj::some(){
	float tx = velocity.x;
	float ty = velocity.y;
	float tz = velocity.z;
	if(tx>-0.1f && tx<.1f)
		velocity.x=0;
	if(ty>-0.1f && ty<.1f)
		velocity.y=0;
	if(tz>-0.1f && tz<.1f)
		velocity.z=0;
	
}
/**
*Use use
*/
void PlayerObj::decel(){
	double tx = acceleration.x;
	double ty = acceleration.y;
	double tz = acceleration.z;
	if(tx!=0.0f && tx>0.0f)
		acceleration.x=tx-.1;
	if(tx!=0.0f && tx<0.0f)
		acceleration.x=tx+.1;
	if(ty!=0.0f && ty>0.0f)
		acceleration.y=ty-.1;
	if(ty!=0.0f && ty<0.0f)
		acceleration.y=ty+.1;
	if(tz!=0.0f && tz>0.0f)
		acceleration.z=tz-.1;
	if(tz!=0.0f && tz<0.0f)
		acceleration.z=tz+.1;
}
void PlayerObj::derot(){
	float tx = rotac.x;
	float ty = rotac.y;
	float tz = rotac.z;
	if(tx!=0.0f && tx>0.0f)
		rotac.x=tx-.1;
	if(tx!=0.0f && tx<0.0f)
		rotac.x=tx+.1;
	if(ty!=0.0f && ty>0.0f)
		rotac.y=ty-.1;
	if(ty!=0.0f && ty<0.0f)
		rotac.y=ty+.1;
	if(tz!=0.0f && tz>0.0f)
		rotac.z=tz-.1;
	if(tz!=0.0f && tz<0.0f)
		rotac.z=tz+.1;
}
void PlayerObj::derotVel(){
	float tx = rotvel.x;
	float ty = rotvel.y;
	float tz = rotvel.z;
	if(tx!=0.0f && tx>0.0f)
		rotvel.x=tx-.1;
	if(tx!=0.0f && tx<0.0f)
		rotvel.x=tx+.1;
	if(ty!=0.0f && ty>0.0f)
		rotvel.y=ty-.1;
	if(ty!=0.0f && ty<0.0f)
		rotvel.y=ty+.1;
	if(tz!=0.0f && tz>0.0f)
		rotvel.z=tz-.1;
	if(tz!=0.0f && tz<0.0f)
		rotvel.z=tz+.1;
}
/**
*Don't use
*/
void PlayerObj::devel(){
	double tx = velocity.x;
	double ty = velocity.y;
	double tz = velocity.z;
	if(tx!=0.0f && tx>5.0f)
		velocity.x=5.0f;
	else{
	if(tx!=0.0f && tx<5.0f)
		velocity.x=-5.0f;
	}
	if(ty!=0.0f && ty>5.0f)
		velocity.y=5.0f;
	else{
	if(ty!=0.0f && ty<5.0f)
		velocity.y=-5.0f;
	}
	if(tz!=0.0f && tz>5.0f)
		velocity.z=5.0f;
	else{
	if(tz!=0.0f && tz<5.0f)
		velocity.z=-5.0f;
	}
}
vec3 PlayerObj::posit(){
	return vec3(position);
}
vec3 PlayerObj::headin(){
	return vec3(eye);
}