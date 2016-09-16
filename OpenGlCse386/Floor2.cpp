#include "Floor2.h"

#include <vector>

#include "vertexStructs.h"

Floor2::Floor2( GLfloat w)
	:VisualObject( ), sideLength( w ), normalVector(vec3(0.0f, 1.0f, 0.0f))
{ 
		divisionsPerSide = (int)sideLength;

		if( divisionsPerSide% 2 != 0) {
			divisionsPerSide = divisionsPerSide + 1;
		}
		tileWidth = sideLength / divisionsPerSide ;
}
 
Floor2::~Floor2(void)
{
	glDeleteVertexArrays (1, &lightSquareVertexArrayObject);

}

void Floor2::setShaderValues()
{

	// This program will stay in effect for all draw calls until it is 
	// replaced with another or explicitly disabled (and the 
	// fixed function pipeline is enabld) by calling glUseProgram with NULL
	glUseProgram(shaderProgram);

	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);

	darkMaterial.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
						 getUniformLocation( shaderProgram, "object.diffuseMat"),
						 getUniformLocation( shaderProgram, "object.specularMat"),
						 getUniformLocation( shaderProgram, "object.specularExp"),
						 getUniformLocation( shaderProgram, "object.emissiveMat" ),
						 getUniformLocation( shaderProgram, "object.textureMapped") );
	
	darkMaterial.setAmbientAndDiffuseMat( vec4( 0.10f, 0.10f, 0.10f, 1.0f ) );
	darkMaterial.setSpecularMat( vec4(1.0f, 1.0f, 1.0f, 1.0f) );
	darkMaterial.setSpecularExponentMat( 64.0f );
	darkMaterial.setTextureMapped( true );
	darkMaterial.setupTexture("fetch.bmp");

	lightMaterial.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
						 getUniformLocation( shaderProgram, "object.diffuseMat"),
						 getUniformLocation( shaderProgram, "object.specularMat"),
						 getUniformLocation( shaderProgram, "object.specularExp"),
						 getUniformLocation( shaderProgram, "object.emissiveMat" ) ,
						 getUniformLocation( shaderProgram, "object.textureMapped") );
	
	lightMaterial.setAmbientAndDiffuseMat( vec4( 0.90f, 0.90f, 0.90f, 1.0f ) );
	lightMaterial.setSpecularMat( vec4(1.0f, 1.0f, 1.0f, 1.0f) );
	lightMaterial.setSpecularExponentMat( 64.0f );
	lightMaterial.setTextureMapped( true );
	lightMaterial.setupTexture("fetch.bmp");

}


// Construct visual object display list.
void Floor2::initialize()
{
	setShaderValues();

	initilizeDarkSquares();

	initilizeLightSquares();

	VisualObject::initialize();

} // end initialize

void Floor2::initilizeDarkSquares() 
{
	pntVertexData v0, v1, v2, v3;

	GLuint VBO, IBO;

	glGenVertexArrays (1, &vertexArrayObject); 
	glBindVertexArray( vertexArrayObject );

	vector<pntVertexData> v;
	vector<unsigned int> indices;

	// Find corner of the board
	GLfloat tileX = -( (divisionsPerSide/2.0f)  * tileWidth ) ;
	GLfloat tileZ = ( (divisionsPerSide/2.0f) * tileWidth);

	GLuint currentIndex = 0;

	// Loop through rows
	for ( int j = 0 ; j < divisionsPerSide ; j++) {

		// Loop through columns
		for ( int i = 0 ; i < divisionsPerSide/2  ; i++ ) {

			v0 = pntVertexData ( vec3(tileX, 0.0f, tileZ-tileWidth ), normalVector,vec2(0,0) );
			v.push_back( v0 );
			v1 = pntVertexData ( vec3(tileX, 0.0f, tileZ ), normalVector,vec2(1,0) );
			v.push_back( v1 );

			tileX += tileWidth;

			v2 = pntVertexData ( vec3(tileX, 0.0f, tileZ), normalVector,vec2(1,1) );
			v.push_back( v2 );
			v3 = pntVertexData ( vec3(tileX, 0.0f, tileZ-tileWidth), normalVector,vec2(0,1) );
			v.push_back( v3 );

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 1);
			indices.push_back(currentIndex + 2);

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 2);
			indices.push_back(currentIndex + 3);
			
			currentIndex += 4;

			tileX += tileWidth;

		} // end for i

		if(j%2==0) {
			tileX = - ( (divisionsPerSide/2.0f) * tileWidth) + tileWidth ;
		}
		else {
			tileX = - ( (divisionsPerSide/2.0f) * tileWidth);
		}

		tileZ -= tileWidth;

	} // end for j

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData),(const GLvoid*)sizeof(vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);

	darkSquareIndices = indices.size(); 

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	v.clear();
	indices.clear();

} // end initilizeDarkSquares


void Floor2::initilizeLightSquares() 
{
	pntVertexData v0, v1, v2, v3;
	//change to pnt
	GLuint VBO, IBO;

	glGenVertexArrays (1, &lightSquareVertexArrayObject); 
	glBindVertexArray( lightSquareVertexArrayObject );

	vector<pntVertexData> v;
	vector<unsigned int> indices;

	// Find corner of the board
	GLfloat tileX = -( (divisionsPerSide/2.0f)  * tileWidth) + tileWidth;
	GLfloat tileZ = ( (divisionsPerSide/2.0f) * tileWidth);

	GLuint currentIndex = 0;

	// Loop through rows
	for ( int j = 0 ; j < divisionsPerSide ; j++) {

		// Loop through columns
		for ( int i = 0 ; i < divisionsPerSide/2  ; i++ ) {

			v0 = pntVertexData ( vec3(tileX, 0.0f, tileZ-tileWidth ), normalVector, vec2(0,0) );
			v.push_back( v0 );
			v1 = pntVertexData ( vec3(tileX, 0.0f, tileZ ), normalVector,vec2(1,0) );
			v.push_back( v1 );

			tileX += tileWidth;

			v2 = pntVertexData ( vec3(tileX, 0.0f, tileZ), normalVector,vec2(1,1) );
			v.push_back( v2 );
			v3 = pntVertexData ( vec3(tileX, 0.0f, tileZ-tileWidth), normalVector,vec2(0,1) );
			v.push_back( v3 );

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 1);
			indices.push_back(currentIndex + 2);

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 2);
			indices.push_back(currentIndex + 3);
			
			currentIndex += 4;

			tileX += tileWidth;

		} // end for i

		if(j%2==0) {
			tileX = - ( (divisionsPerSide/2.0f) * tileWidth);
		}
		else {
			tileX = - ( (divisionsPerSide/2.0f) * tileWidth) + tileWidth;
		}

		tileZ -= tileWidth;

	} // end for j

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData),(const GLvoid*)sizeof(vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);

	lightSquareIndices = indices.size(); 

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	v.clear();
	indices.clear();

} // end initilizeLightSquares


// Preform drawing operations
void Floor2::draw()
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelAndFixed));

	glBindVertexArray(vertexArrayObject);
	darkMaterial.setShaderMaterialProperties();
    glDrawElements(GL_TRIANGLES, darkSquareIndices, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(lightSquareVertexArrayObject);
	lightMaterial.setShaderMaterialProperties();
    glDrawElements(GL_TRIANGLES, lightSquareIndices, GL_UNSIGNED_INT, 0);

	// Draw all children
	VisualObject::draw();

} // end draw


