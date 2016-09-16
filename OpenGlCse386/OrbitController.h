
#include "Controller.h"
class OrbitController :
	public Controller
{
public:
OrbitController( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3 planeRot = glm::vec3(1.0, 0.0f, 0.0f), glm::vec3 tumbleRot = glm::vec3(1.0, 0.0f, 0.0f), GLfloat r = 25.0f);
virtual void update(float elapsedTimeSeconds);
protected:
// Position at which the object is spinning in place
glm::vec3 position;

// axes of rotation
glm::vec3 tumbleRotation;
glm::vec3 planeRotation;

// rate and direction of rotation
GLfloat rate;

GLfloat rotation;
};

