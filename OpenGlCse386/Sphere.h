#ifndef ___SPHERE_H___
#define ___SPHERE_H___

#include "VisualObject.h"
#include "textureCoordinates.h"
 

class Sphere : public VisualObject
{
	public:
		Sphere(  float Radius = 1.0f, int slices = 16, int stacks = 16 );
		virtual ~Sphere(void);

		virtual void initialize();

		virtual void draw();

	protected:
	
		void setShaderValues();

		void initializeSphereBody();
		void initializeSphereBottom();
		void initializeSphereTop();
		
		float radius;
		int stacks;
		int slices;

		GLuint vertexArrayObjectForBottom, vertexArrayObjectForTop; 

		// this variable will later be used to hold the number of indices
		int bodyIndicesCount, bottomIndicesCount, topIndicesCount;

		// Step in z and radius as stacks are drawn.
		double z0, z1;
		double r0, r1;

		float stackStep;
		float sliceStep;
};

#endif /* ___SPHERE_H___ */

