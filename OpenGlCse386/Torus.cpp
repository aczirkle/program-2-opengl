#include "Torus.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Torus::Torus( glm::vec4 color, float innerRadius, float outerRadius,  int sides, int rings)
	:VisualObject()
{
	dInnerRadius =  innerRadius;
	dOuterRadius = outerRadius;
	nSides = sides; 
	nRings = rings;
}

void Torus::initialize(){
	//setShaderValues();
	VisualObject::initialize();
}

void Torus::setShaderValues()
{
	// This program will stay in effect for all draw calls until it is 
	// replaced with another or explicitly disabled (and the 
	// fixed function pipeline is enabled) by calling glUseProgram with NULL
    glUseProgram(shaderProgram);

	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);


	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
						 getUniformLocation( shaderProgram, "object.diffuseMat"),
						 getUniformLocation( shaderProgram, "object.specularMat"),
						 getUniformLocation( shaderProgram, "object.specularExp"),
						 getUniformLocation( shaderProgram, "object.emissiveMat" ),
						 getUniformLocation( shaderProgram, "object.textureMapped") );
}

// Preform drawing operations
void Torus::draw()
{
	VisualObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidTorus( dInnerRadius, dOuterRadius, nSides, nRings);

} // end draw

