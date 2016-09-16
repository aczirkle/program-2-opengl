#include "OpenGLApplicationBase.h"
#include "Camera.h"
#include "Controller.h"
class PlayerObj:
	public Controller
{
	public:
		PlayerObj();
		PlayerObj(glm::vec3 position, float heading, float speed );
		PlayerObj(glm::vec3 position, vec3 heading, float speed );

		//virtual void draw();
		void rotateView();
		void moveRight();
		void moveLeft();
		void moveForward();
		void moveBackward();
		void moveUp();
		void moveDown();
		void rotateRight();
		void rotateLeft();
		void rotatePosZ();
		void rotateNegZ();
		void rotatePosY();
		void rotateNegY();
		void viewAt();
		vec3 posit();
		vec3 headin();
		bool jumping;
		void jump();
		void respawn();
		void accelerate(vec3 dir);
		void stopRot();
		void decel();
		void derot();
		void derotVel();
		void devel();
		void some();
		void launch(glm::vec3 start, glm::vec3 direction, float speed);
		void update(float elapsedTimeSeconds);
		vec3 rotac;
		vec3 rotvel;
		vec3 rotpos;
		vec3 eye;
		vec3 velocity;
		vec3 position;
		void ack();
		vec3 heading;
	protected:
		vec3 acceleration;
		
		//float decel;
		//vec3 velocity;
		
		
		//Camera* cam;
		float speed;
		
};