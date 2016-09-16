#include "VisualObject.h"
#include "textureCoordinates.h"


class Torus : public VisualObject
{
	public:
		Torus( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f), 
			   float innerRadius= 0.25f, float outerRadius = 1.0f, 
			   int sides = 8, int rings = 16);

		virtual void draw();
		virtual void initialize();

	protected:
		void setShaderValues();
		GLdouble dInnerRadius, dOuterRadius;
		GLint nSides, nRings;
};


