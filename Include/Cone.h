#ifndef ___CONE_H___
#define ___CONE_H___
 
#include "VisualObject.h"
#include "textureCoordinates.h"

class Cone : public VisualObject
{
	public:
		Cone( float height = 2.0f, float base = 0.5f, int numMajor = 4, int numMinor = 16);

		virtual ~Cone(void);
			
		virtual void initialize();

		virtual void draw();

	protected:
	
		void setShaderValues();

		void initializeConeBody();
		void initializeConeBottom();

		int stacks, slices;
		float height, base;

		GLuint vertexArrayObjectForBottom; 

		// this variable will later be used to hold the number of indices
		int bodyIndicesCount, bottomIndicesCount;

};

#endif /* ___CONE_H___ */



