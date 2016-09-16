#include "SpaceShip.h"

#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"

 
SpaceShip::SpaceShip( )
	: VisualObject(  )
{
		VisualObject * fuselage = new Cylinder( 4.0f);
		fuselage->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f));
		fuselage->material.setAmbientAndDiffuseMat(vec4( 0.1f, 0.1, 0.9f, 1.0f)); 
		fuselage->material.setTextureMapped(true);
		fuselage->material.setupTexture("fetch.bmp");
		this->addChild( fuselage );

		VisualObject * nose = new Cone();
		nose->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.0f));
		nose->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 0.0f, 1.0f)); 
		this->addChild(nose);

		VisualObject * engine = new Cone();
		engine->fixedTransformation = translate(mat4(1.0f), vec3(1.0f, 0.0f, -2.0f));
		engine->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 0.0f, 1.0f)); 
		this->addChild(engine);

		VisualObject * engine2 = new Cone();
		engine2->fixedTransformation = translate(mat4(1.0f), vec3(-1.0f, 0.0f, -2.0f));
		engine2->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 0.0f, 1.0f)); 
		this->addChild(engine2);

		VisualObject * bubble = new Sphere( 0.5f);
		bubble->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f));
		bubble->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.0, 0.0f, 1.0f)); 
		this->addChild(bubble);

} // end SpaceShip constructor

void SpaceShip::setShader( GLuint shaderProgram ) 
{ 
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->setShader(shaderProgram);
	}
}



