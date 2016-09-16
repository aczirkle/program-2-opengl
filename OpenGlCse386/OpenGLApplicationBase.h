
#ifndef OPENGL_APPLICATION_BASE_H
#define OPENGL_APPLICATION_BASE_H

#include "VisualObject.h"
#include "SharedProjectionAndViewing.h"
const GLint FPS = 60; // Desired maximum number of frames per second

/**
* Super class for OpenGL applications. Implements the ICallbacks interface
* so that it can respond to events raised by the GLUTbase framework. Inherits 
* initialize, draw, and update method from the VisualObject class. This methods
* will normally be overriden by sub-classes of this class.
*/
class OpenGLApplicationBase : public VisualObject
{
public:



	/**
	* Responds to regular key presses. When inheriting, call this method in the default case of the 
	* switch statement to preserve exit on escape and 'f' key press to toggle full screen.
	* @param Key The generated ASCII character for the key whose press triggered the callback.
	* @param x The x-coordinate of the mouse relative to the window at the time the key is pressed. 
	* @param y The y-coordinate of the mouse relative to the window at the time the key is pressed.
	*/
	virtual void OpenGLApplicationBase::KeyboardCB(unsigned char Key, int x, int y);

	/**
	* Acts as the display function for the window. Renders and updates the entire scene each
	* time it is callded as long as sufficient time has pass since the last rendering.
	*
	* THIS METHOD SHOULD NOT BE OVERRIDEN.
	*/
	void RenderSceneCB();

	/**
	* Called whenever the window it resphapes and immediately before a windows 
	* first display. 
	* @windowWidth new window width in pixels.
	* @windowHeight new window height in pixels.
	*/
	virtual void ReshapeCB( int windowWidth, int windowHeight );

	//Sets up the menus, obviously.
	void setupMenus();

	GLuint createPointSizeMenu();

	GLuint createLineWidthMenu();

	GLuint createAntiAliasingMenu();

	void setViewPoint();
	

protected:

	SharedProjectionAndViewing projectionAndViewing;
	GLuint createPolygonMenu();
	GLuint createFrontFaceMenu();
	// integer id for top-level popup menu.
	GLuint topMenu;

	// milliseconds between frames. Used to control the framerate.
	static const GLint FRAME_INTERVAL = 1000/FPS; 


}; // end OpenGLApplicationBase


// Points to the OpenGLApplicationBase object  which was delivered to
// GLUTBase(). Basic events are forwarded to this object. GlutBase calls the initialize,
// draw, and render methods through this pointer.
static OpenGLApplicationBase* s_pOpenGLAppBase;

	//Called when an item on the main menu is selected.
	void mainMenu(int value);

	void polygonMenu(int value);

	void frontFaceMenu(int value);

	void pointSizeMenu(int value);

	void lineWidthMenu(int value);

	void antiAliasMenu(int value);


#endif /* OPENGL_APPLICATION_BASE */