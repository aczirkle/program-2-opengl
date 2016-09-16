#ifndef ___CYLINDER_H___
#define ___CYLINDER_H___

#include "VisualObject.h"
#include "textureCoordinates.h"
 

class Cylinder : public VisualObject
{
	public:
		Cylinder( float height = 2.0f, float radius = 0.5f, int numMajor = 4, int numMinor = 16);

		virtual ~Cylinder(void);
			
		virtual void initialize();

		virtual void draw();

	protected:
	
		void setShaderValues();

		void initializeCylinderBody();
		void initializeCylinderBottom();
		void initializeCylinderTop();

		int stacks, slices;
		float height, radius;

		GLuint vertexArrayObjectForBottom, vertexArrayObjectForTop; 

		// this variable will later be used to hold the number of indices
		int bodyIndicesCount, bottomIndicesCount, topIndicesCount;
};

#endif /* ___CYLINDER_H___ */

