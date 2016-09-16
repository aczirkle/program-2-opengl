#include "VisualObject.h"

using namespace std;

// Initialize the static object counter
int VisualObject::objectCounter = 0;


VisualObject::VisualObject()
	: objectSerialNumber( objectCounter++ )
{ 
	setUpVisualObject();

} // end VisualObject constructor

 
void VisualObject::setUpVisualObject()
{
	parent = NULL;
	controller = NULL;
	fixedTransformation = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	modelAndFixed = glm::mat4(1.0f);
	shaderProgram = 0;

} // end setUpVisualObject


VisualObject::~VisualObject()
{ 
	cout << "~VisualObject()" << endl;

	for (unsigned int i = 0; i < children.size(); i++) {

		delete children[i];
	}

	children.clear();

	if (controller != NULL) {
		delete controller;
	}

	glDeleteVertexArrays (1, &vertexArrayObject);

} // end destructor

// Preform drawing operations. Draw this object and all of its children.
void VisualObject::initialize()
{
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->initialize();
	}

} // end initialize


// Preform drawing operations. Draw this object and all of its children.
void VisualObject::draw()
{
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->draw();
	}

} // end draw


// Update this object and all of its children
void VisualObject::update(float elapsedTimeSeconds)
{
	if (controller != NULL ) {
		controller->update( elapsedTimeSeconds );
	}

	modelAndFixed = getParentModelMatrix() * modelMatrix * fixedTransformation;

	updateChildren(elapsedTimeSeconds);

} // end update

void VisualObject::updateChildren(float elapsedTimeSeconds) 
{
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->update(elapsedTimeSeconds);
	}

} // end updateChildren


// Add a child to this object and set the child's parent
// to this object
void VisualObject::addChild(VisualObject * child )
{
	children.push_back(child);

	child->parent = this;

} // end addChild


// Set the controller for this object and set the controller
// target to this object.
void VisualObject::addController(Controller * controller )
{
	this->controller = controller;

	controller->target = this;

} // end addController

// Remove the Controller object for this object
// Untested method
Controller*  VisualObject::removeController()
{
	Controller * controllerReference = this->controller; 

	controller->target = NULL;

	this->controller = NULL;

	return controllerReference;

} // end removeController


// Remove and delete the controller. Return true if the a controller 
// was removed.
bool VisualObject::removeAndDeleteController(  )
{
	Controller * cont = removeController(  );

	if (cont != NULL ) {
		delete cont;

		return true;
	}
	else {
		return false;
	}

} // end removeAndDeleteController


// Look for a child of this object and remove it is it 
// is found. Return a reference to the removed child
VisualObject* VisualObject::removeChild( int childID )
{
	unsigned int i = 0;
	VisualObject* removed = NULL;

	// Search for the specific child
	for (; i < children.size(); i++) {

		if ( children[i]->objectSerialNumber == childID) {
			break;
		}

	}
	
	// Remove the child if it was found
	if (i < children.size() ) {

		removed = children[i];
		removed->parent = NULL;

		children.erase(children.begin() + i);
	}

	return removed;

} // end removeChild


// Look for a child of this object and remove and it
// and delete it. Return true if the child was found.
bool VisualObject::removeAndDeleteChild( int childID )
{
	VisualObject * child = removeChild( childID );

	if (child != NULL ) {
		delete child;

		return true;
	}
	else {
		return false;
	}

} // end removeAndDeleteChild


// Detach this object from its parent (if it has one).
bool VisualObject::detachFromParent( )
{
	if (parent != NULL) {
		parent->removeChild(this->objectSerialNumber);
		parent = NULL;
		return true;
	}
	else {
		return false;
	}

} // end detachFromParent


glm::mat4 VisualObject::getParentModelMatrix()
{
	if (parent == NULL) {
		return glm::mat4(1.0f);
	}
	else {

		return parent->getParentModelMatrix() * parent->modelMatrix;
	}

} // end getParentModelMatrix


glm::vec3 VisualObject::getWorldPosition()
{
	glm::mat4 totalTransformation = getParentModelMatrix() * modelMatrix;

	return totalTransformation[3].xyz;

} // end getWorldPosition


void checkOpenGLErrors(const GLchar* methodName)
{
	GLenum errorCode; // Current error code.
	const GLubyte *errorString; // Desriptive string for the error. 
	
	// glGetError returns the value of the error flag. No  errors are 
	// recorded until glGetError is called, the error code is returned, 
	// and the flag is reset to GL_NO_ERROR. If a call to glGetError 
	// returns GL_NO_ERROR, there has been no detectable error since the 
	// last call to glGetError, or since the GL was initialized.
	if (( errorCode = glGetError() ) != GL_NO_ERROR ) {

		errorString = gluErrorString( errorCode );
		cout << errorString << " in " << methodName << endl;
	}

} // end checkOpenGLErrors










