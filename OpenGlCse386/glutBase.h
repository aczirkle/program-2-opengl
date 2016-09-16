#ifndef GLUT_BASE_H
#define GLUT_BASE_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGLApplicationBase.h"

#define WINDOW_WIDTH 1024 // Default window width
#define WINDOW_HEIGHT 768 // Default window height

using namespace std;

/**
* GLUTBase provides a mechanism for getting support a class that implements 
* the ICallbacks interface. A reference to the class it held in a pointer varibale
* called s_pCallbacks which is declared in glutBase.cpp. To use glutBase functionality
* GLUTBaseInit, GLUTBaseCreateWindow, and GLUTBaseRun should be called in order by the 
* main.
*/

/**
* Performs basic initialization for an OpenGL GLUT application. Initializes GLUT library and 
* negotiates a session with the window system. Sets the initial display mode for the a top 
* level window. Command line arguments passed to the main should be passed to this function.
* @param argcp A pointer to the program’s unmodified argc variable from main.
* @param argv The program’s unmodified argv variable from main.
*/
void GLUTBaseInit(int argc, char** argv);

/**
* Specifies  initial title, size, position and name of window and whether or not fullscreen is desired. 
* Default window is determined by #defines in glutBase.h. Initializes GLEW and diplays version OpenGL and 
* GLSL version information. All parameters have a default value except for the window title (pTitle).
* @param pTitle window title
* @param width desired width of the window in pixels
* @param height desired height of the window in pixels
* @param fullScreen GL_TRUE is  window desired width of the window
* @returns true if the window was successfully created. false otherwise
*/
GLboolean GLUTBaseCreateWindow(const char* pTitle, GLuint Width = WINDOW_WIDTH, GLuint Height = WINDOW_HEIGHT, GLboolean isFullScreen = GL_FALSE);

/**
* Takes an object of a class that implements the ICallbacks interface
* and registers it handle basic GLUT generated events, then enters the GLUT main
* loop.
* @param pCallbacks pointer to an Object of a class that impplements ICallbacks
*/
void GLUTBaseRunApplication(OpenGLApplicationBase* pCallbacks);

// Points to the OpenGLApplicationBase object. This static
// variable is declared in OpenGLApplicationBase.h
extern OpenGLApplicationBase* s_pOpenGLAppBase;


#endif /* GLUT_BASE_H */
