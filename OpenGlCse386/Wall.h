#ifndef ___WALL_H___
#define ___WALL_H___


#include "visualobject.h"
 
class Wall : public VisualObject
{
	public:
		Wall( float height = 6.0f, float width = 8.0f, 
			  int rows = 1, int columns = 1 );

		virtual ~Wall(void);
			
		virtual void initialize();

		virtual void draw();

	protected:
	
		void setShaderValues();

		int rows, columns;
		float height, width;

		int indiceCount;
};

#endif // ___WALL_H___

