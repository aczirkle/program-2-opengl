#include "Camera.h"

class Player : public Camera
{
	public:
		Player();
		Player(glm::vec4 position, float heading, float speed );

		//virtual void draw();
		void rotateView();
		void moveRight();
		void moveLeft();
		void moveForward();
		void moveBackward();
		void rotateRight();
		void accelerate(vec3 dir);
		virtual void update(float elaspedTimeSec);
		
	protected:
		vec3 acceleration;
		vec4 velocity;
		vec4 position;
		float heading,speed;
		
};
