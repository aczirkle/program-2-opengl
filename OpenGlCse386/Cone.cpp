#include "Cone.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Cone::Cone(  float height, float base, int numMajor, int numMinor)
	:VisualObject(),stacks(numMajor), slices(numMinor), height(height), base(base) 
{}

Cone::~Cone(void)
{
	glDeleteVertexArrays (1, &vertexArrayObjectForBottom);
} 

void Cone::setShaderValues()
{
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


// Construct visual object display list.
void Cone::initialize()
{
	setShaderValues();
	
	initializeConeBottom();
	initializeConeBody();

	VisualObject::initialize();
	 
} // end initialize

void Cone::initializeConeBody()
{
    // Step in z and radius as stacks are drawn.
    double z0,z1;
	double r0, r1;

	const float angleStep = 2.0f * M_PI / slices;
	const float zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
    const float rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

	// Scaling factors for vertex normals 
    const float cosn = ( height / sqrt ( height * height + base * base ));
    const float sinn = ( base   / sqrt ( height * height + base * base ));

	// vector containers to hold  data
	vector<pntVertexData> v; // vertex positions
	vector<unsigned int> indices; // indices
	GLuint VBO, IBO; // Identifiers for buffer objects

	// Do the stacks
	z0 = 0.0;
    z1 = zStep;

    r0 = base;
    r1 = r0 - rStep;

	GLuint currentIndex = 0;

	float theta = 0.0f;

	for( int i = 0; i < stacks-1; i++ )
    {
        for( int j=0; j < slices; j++)
        {
			theta = j* angleStep;

            vec3 n01 = vec3(cos(theta) * cosn, sin(theta)*cosn, sinn);

            vec3 v0 = vec3(cos(theta) * r0,   sin(theta)*r0,   z0  );
			v.push_back( pntVertexData( v0, n01, getPlanarTextCoords( v0, base, height  )) ); // 0
            
			vec3 v1 = vec3(cos(theta) * r1,   sin(theta)*r1,   z1  );
			v.push_back( pntVertexData( v1, n01, getPlanarTextCoords( v1, base, height )) ); // 1

			theta = (j+1)* angleStep;
			vec3 n23 = vec3(cos(theta) * cosn, sin(theta) * cosn, sinn);

            vec3 v2 = vec3(cos(theta) * r0,   sin(theta) * r0,   z0  );
			v.push_back( pntVertexData( v2, n23, getPlanarTextCoords( v2, base, height )) ); // 2
           
			vec3 v3 = vec3(cos(theta) * r1,   sin(theta) * r1,  z1  );
			v.push_back( pntVertexData( v3, n23, getPlanarTextCoords( v3, base, height )) ); // 3

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 2);
			indices.push_back(currentIndex + 3);

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 3);
			indices.push_back(currentIndex + 1);

			currentIndex += 4;
        }

        z0 = z1; 
		z1 += zStep;
        r0 = r1; 
		r1 -= rStep;
    }

	vec3 n = vec3(cos(0.0)*cosn, sin(0.0)*cosn, sinn);


	for (int j=0; j < slices; j++)
	{
		theta = j* angleStep;

		vec3 v0 = vec3( cos(theta) * r0, sin(theta) * r0, z0 );
		v.push_back( pntVertexData( v0, n, getPlanarTextCoords( v0, base, height )) ); // 0
		
		vec3 v1 = vec3( 0, 0, height);
		v.push_back( pntVertexData( v1, n, getPlanarTextCoords( v1, base, height )) ); // 1

		theta = (j+1)* angleStep;

		n = vec3 ( cos(theta) * cosn, sin(theta) * cosn, sinn );
		vec3 v2 = vec3( cos(theta) * r0, sin(theta)*r0, z0 );
		v.push_back( pntVertexData( v2, n, getPlanarTextCoords( v2, base, height )) ); // 2

		indices.push_back(currentIndex);
		indices.push_back(currentIndex + 2);
		indices.push_back(currentIndex + 1);
		currentIndex += 3;
	}

	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	// Create the buffer to hold interleaved data and bind the data to them
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Buffer for vertex data
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW); //Buffering vertex data

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)sizeof(vec3) );
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);

	// Generate a buffer for the indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0] , GL_STATIC_DRAW);

	// store the number of indices for later use
	bodyIndicesCount = indices.size();
 
	v.clear();
	indices.clear();

} // end

void Cone::initializeConeBottom()
{
	float angleStep = 2.0f * M_PI / slices;

	// vector containers to hold  data
	vector<pntVertexData> v; // vertex positions
	vector<unsigned int> indices; // indices
	GLuint VBO, IBO; // Identifiers for buffer objects
	
	GLuint currentIndex = 0;

    vec3 n = vec3(0.0f,0.0f,-1.0f);
	vec3 ctr = vec3( 0.0f, 0.0f, 0.0f );

	float theta = 0.0f;

    for (int j = slices; j >= 0; j--) {			

		theta = j * angleStep;
		vec3 v0 = vec3( cos( theta ) * base, sin( theta ) * base, 0.0f);
		v.push_back( pntVertexData( v0, n, getPlanarTextCoords( v0, base, height )));
		indices.push_back(currentIndex++);

		theta = (j-1)* angleStep;

		vec3 v1 = vec3( cos( theta ) * base, sin( theta ) * base, 0.0f);
		v.push_back( pntVertexData( v1, n, getPlanarTextCoords( v1, base, height )));
		indices.push_back(currentIndex++);

		v.push_back( pntVertexData( ctr, n, getPlanarTextCoords( ctr, base, height )));
		indices.push_back(currentIndex++);
	}

	glGenVertexArrays (1, &vertexArrayObjectForBottom);
	glBindVertexArray( vertexArrayObjectForBottom );

	// Create the buffer to hold interleaved data and bind the data to them
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Buffer for vertex data
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW); //Buffering vertex data

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)sizeof(vec3) );
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) );
	glEnableVertexAttribArray(3);

	// Generate a buffer for the indices
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0] , GL_STATIC_DRAW);

	// store the number of indices for later use
	bottomIndicesCount = indices.size();
 
	v.clear();
	indices.clear();

} // end initializeConeBottom


// Preform drawing operations
void Cone::draw()
{
	glUseProgram(shaderProgram);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelAndFixed));

	material.setShaderMaterialProperties();
	
	// Draw body
	glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, bodyIndicesCount, GL_UNSIGNED_INT, 0);

	// Draw bottom
	glBindVertexArray(vertexArrayObjectForBottom);
	glDrawElements(GL_TRIANGLE_FAN, bottomIndicesCount, GL_UNSIGNED_INT, 0);

	// Draw all children
	VisualObject::draw();

} // end draw


