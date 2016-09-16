#include "Pyramid.h"

#include "vertexStructs.h"
#include "textureCoordinates.h"

Pyramid::Pyramid(GLfloat w, GLfloat h)
	: width(w), height(h) {

}

void Pyramid::setShaderValues()
{
	// Bind the shader 
	glUseProgram(shaderProgram);

	// Find the location of the model matrix uniform variable in the shader 
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);

	// Find the locations of the material properties in the Material struct called ect 
	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"), 
							getUniformLocation( shaderProgram, "object.diffuseMat"), 
							getUniformLocation( shaderProgram, "object.specularMat"), 
							getUniformLocation( shaderProgram, "object.specularExp"), 
							getUniformLocation( shaderProgram, "object.emissiveMat" ), 
							getUniformLocation( shaderProgram, "object.textureMapped"));

}

void Pyramid::initialize() {
	
	setShaderValues();

	GLuint VBO;

	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	glm::vec3 v0 = glm::vec3( 0.0f, height/2., 0.0f);
	glm::vec3 v1 = glm::vec3( width/-2., height/-2., width/2.);
	glm::vec3 v2 = glm::vec3( width/2., height/-2., width/2.);
	glm::vec3 v3 = glm::vec3(width/2., height/-2., width/-2.);
	glm::vec3 v4 = glm::vec3( width/-2., height/-2., width/-2.);

	vector<pntVertexData> norms;
	glm::vec3 frontFaceNormal = findUnitNormal(v0, v1, v2);
	norms.push_back(pntVertexData(v0, frontFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v1, frontFaceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v2, frontFaceNormal, getPlanarTextCoords(v2, width, height)));

	frontFaceNormal = findUnitNormal(v0, v2, v3);
	norms.push_back(pntVertexData(v0, frontFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v2, frontFaceNormal, getPlanarTextCoords(v2, width, height)));
	norms.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));

	frontFaceNormal = findUnitNormal(v0, v3, v4);
	norms.push_back(pntVertexData(v0, frontFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));
	norms.push_back(pntVertexData(v4, frontFaceNormal, getPlanarTextCoords(v4, width, height)));

	frontFaceNormal = findUnitNormal(v0, v4, v1);
	norms.push_back(pntVertexData(v0, frontFaceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v4, frontFaceNormal, getPlanarTextCoords(v4, width, height)));
	norms.push_back(pntVertexData(v1, frontFaceNormal, getPlanarTextCoords(v1, width, height)));

	frontFaceNormal = findUnitNormal(v3, v1, v4);
	norms.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));
	norms.push_back(pntVertexData(v1, frontFaceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v4, frontFaceNormal, getPlanarTextCoords(v4, width, height)));

	frontFaceNormal = findUnitNormal(v2, v1, v3);
	norms.push_back(pntVertexData(v2, frontFaceNormal, getPlanarTextCoords(v2, width, height)));
	norms.push_back(pntVertexData(v1, frontFaceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));

	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO );

	glBufferData( GL_ARRAY_BUFFER, norms.size() * sizeof(pntVertexData),&norms[0],GL_STATIC_DRAW);

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0 );
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)sizeof(glm::vec3) );
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);

	numberOfIndices = norms.size();


	// Initialize all children
	VisualObject::initialize();
}

void Pyramid::draw() {

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelMatrix));
	glBindVertexArray(vertexArrayObject);
	material.setShaderMaterialProperties();

	glDrawArrays( GL_TRIANGLES, 0, numberOfIndices );

	VisualObject::draw();
}