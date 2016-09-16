#include "Figure2.h"


Figure2::Figure2(void)
{
}


Figure2::~Figure2(void)
{
}

void
	Figure2::draw()
{
	//cout << "IM DRAWING" << endl;
	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_LINES, 0, 6);

	//cout << "FigureOne draw method called." << endl;
}

void
	Figure2::initialize()
{
	glUseProgram(shaderProgram);
	cout << "FigureTwo initialize method called." << endl;
	glm::vec3 v0 = glm::vec3( 0.5f, 0.f, 0.0f);
	glm::vec3 v1 = glm::vec3( 0.5f, 0.5f, 0.0f);
	glm::vec3 v2 = glm::vec3(-0.5f, 0.0f, 0.0f);
	glm::vec3 v3 = glm::vec3( -0.5f, -0.5f, 0.0f);
	glm::vec3 v5 = glm::vec3( -0.5f, -0.5f, 0.0f);
	glm::vec3 v4 = glm::vec3( 0.5f, -0.5f, 0.0f);
	vector<glm::vec3> v;
	//vector<glm::vec3> v2;
	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v2 );
	v.push_back( v3 );
	v.push_back( v5 );
	v.push_back( v4 );

	GLuint VBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_ARRAY_BUFFER,
		v.size() * sizeof(glm::vec3),
		&v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer( 0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0 );
	glEnableVertexAttribArray( 0 );	

}