#include "Controller.h"
class SpinnerController : public Controller {
public:
// Constructor sets the position of the object,
// the axis about which it will rotate, and the rate and direction
// of rotation.
	
GLfloat rotation;
// axis of rotation
glm::vec3 axis;
SpinnerController( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3 ax = glm::vec3(1.0, 0.0f, 0.0f), GLfloat r = 25.0f);
virtual void update(float elapsedTimeSeconds);
protected:
// Position at which the object is spinning in place
glm::vec3 position;

// rate and direction of rotation
GLfloat rate;

};