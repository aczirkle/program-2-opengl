#ifndef ___SPACESHIP_H___
#define ___SPACESHIP_H___

#include "visualobject.h"

class SpaceShip : public VisualObject
{
	public:
		SpaceShip( );

		virtual void setShader( GLuint shaderProgram );

};

#endif // ___SPACESHIP_H___
 