#ifndef ___FLOOR_TWO_H___
#define ___FLOOR_TWO_H___

#include "VisualObject.h"
 
class Floor2 : public VisualObject
{
	public:

		Floor2( GLfloat w = 8.0f );
		virtual ~Floor2(void);

		virtual void initialize();

		virtual void draw();

	protected:

		void setShaderValues();

		void initilizeDarkSquares();
		void initilizeLightSquares();
		
		int darkSquareIndices;
		int lightSquareIndices;
		GLuint lightSquareVertexArrayObject; 

		GLfloat sideLength; 
		int divisionsPerSide;
		GLfloat tileWidth;
		
		Material darkMaterial;
		Material lightMaterial;

		const vec3 normalVector;

};

#endif // ___FLOOR_TWO_H___
