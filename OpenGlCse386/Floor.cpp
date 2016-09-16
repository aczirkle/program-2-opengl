#include "Floor.h"


#include <vector>

#include "vertexStructs.h"

Floor::Floor(GLfloat w)
	:VisualObject( ), sideLength( w )
{ }
 

void Floor::buildShaderProgram()
{




} // end buildShaderProgram


// Construct visual object display list.
void Floor::initialize()
{
	glUseProgram(shaderProgram);
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);
	
	float divisionsPerSide = sideLength;

	pcVertexData v0, v1, v2, v3;

	short color = 1;

	GLuint VBO, IBO;

	glGenVertexArrays (1, &vertexArrayObject); 
	glBindVertexArray( vertexArrayObject );

	vector<pcVertexData> v;
	vector<unsigned int> indices;

	GLfloat tileWidth = sideLength / divisionsPerSide ;

	// Find corner of the board
	GLfloat tileX = -( (divisionsPerSide/2.0f)  * tileWidth);
	GLfloat tileZ = ( (divisionsPerSide/2.0f) * tileWidth);

	// define the two square colors
	glm::vec4 color1( 0.9f, 0.9f, 0.9f, 1.0f );
 	glm::vec4 color2( 0.05f, 0.05f, 0.05f, 1.0f );
	glm::vec4 currentColor;
	GLuint currentIndex = 0;

	// Loop through rows
	for ( int j = 0 ; j < divisionsPerSide ; j++ ) {

		currentColor = (color++)%2 ? color1 : color2 ;

		// Loop through columns
		for ( int i = 0 ; i < divisionsPerSide  ; i++ ) {

			currentColor = (color++)%2 ? color1 : color2 ;

			v0 = pcVertexData ( glm::vec3(tileX, 0.0f, tileZ-tileWidth ), currentColor );
			v.push_back( v0 );
			v1 = pcVertexData ( glm::vec3(tileX, 0.0f, tileZ ), currentColor );
			v.push_back( v1 );

			tileX += tileWidth;

			v2 = pcVertexData ( glm::vec3(tileX, 0.0f, tileZ), currentColor );
			v.push_back( v2 );
			v3 = pcVertexData ( glm::vec3(tileX, 0.0f, tileZ-tileWidth), currentColor );
			v.push_back( v3 );

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 1);
			indices.push_back(currentIndex + 2);

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 2);
			indices.push_back(currentIndex + 3);
			
			currentIndex += 4;

		} // end for i

		tileX = - ( (divisionsPerSide/2.0f) * tileWidth);
		tileZ -= tileWidth;

	} // end for j

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pcVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pcVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(pcVertexData),(const GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);

	numberOfIndices = indices.size(); 

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	v.clear();
	indices.clear();

	VisualObject::initialize();

} // end initialize


// Preform drawing operations
void Floor::draw()
{
	glUseProgram(shaderProgram);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));

	glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);

	// Draw all children
	VisualObject::draw();

} // end draw
