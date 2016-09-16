#ifndef ___FLOOR_H___
#define ___FLOOR_H___

#include "VisualObject.h"


 
class Floor : public VisualObject
{
	public:

		Floor(GLfloat w = 8.0f );

		virtual void initialize();

		virtual void draw();

	protected:

		void buildShaderProgram();
		
		int numberOfIndices;

		GLfloat sideLength;

		GLuint projectionLocation; 


};

#endif // ___FLOOR_H___
