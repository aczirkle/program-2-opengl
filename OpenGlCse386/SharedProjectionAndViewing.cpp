#include "SharedProjectionAndViewing.h"


SharedProjectionAndViewing::SharedProjectionAndViewing(void)
	:blockSizeAndOffetsSet(false), projViewBlockSize(0), worldEyeBlockSize(0)
{
}


SharedProjectionAndViewing::~SharedProjectionAndViewing(void)
{
} 


bool checkLocationFound(const GLchar* locationName, GLuint indice )
{
	if (indice == GL_INVALID_INDEX ) {
		cout << locationName << " not found in shader." << endl;

		return false;
	}
	else {

		//cout << locationName << " index is " <<  indice << endl; 
		return true;
	}
}


void SharedProjectionAndViewing::setUniformBlockForShader(GLuint shaderProgram)
{
	findBlockSizeSetBindingPoint(shaderProgram);

	// Set up the buffer
	if ( blockSizeAndOffetsSet == false ) {

		findOffets( shaderProgram );

		GLuint uniformIndices[2] = {0};
		GLint uniformOffsets[2] = {0};

		const GLchar * charStringNames[] = { "projectionMatrix", "viewMatrix" }; 

		glGetUniformIndices(shaderProgram, 2, (const GLchar **)charStringNames, uniformIndices);

		if ( uniformIndices[0] != GL_INVALID_INDEX && uniformIndices[1] != GL_INVALID_INDEX ) {
			//for(int i = 0; i < 2; i++ ) {

			//	checkLocationFound(charStringNames[i], uniformIndices[i] );
			//}

			//Get the offsets of the uniforms. The offsets in the buffer will be the same.
			glGetActiveUniformsiv(shaderProgram, 2, uniformIndices, GL_UNIFORM_OFFSET, uniformOffsets);

			//for(int i = 0; i < 2; i++ ) {

			//	cout << charStringNames[i] << " offset is " <<  uniformOffsets[i] << endl; 
			//}

			// Save locations
			projectionLocation = uniformOffsets[0];
			viewLocation = uniformOffsets[1];
		}

		GLuint uniformEyeIndice = 0;
		GLint uniformEyeOffset = 0;

		const GLchar * eyeName[]  = {"worldEyePosition"};

		glGetUniformIndices(shaderProgram, 1, eyeName, &uniformEyeIndice);

		if (uniformEyeIndice != GL_INVALID_INDEX) {

			//Get the offsets of the uniforms. The offsets in the buffer will be the same.
			glGetActiveUniformsiv(shaderProgram, 1, &uniformEyeIndice, GL_UNIFORM_OFFSET, &uniformEyeOffset);
		
			//cout << "worldEyePosition" << " offset is " <<  uniformEyeOffset << endl; 

			// Save location
			eyePositionLocation = uniformEyeOffset;
		}
	}

	checkOpenGLErrors("setUniformBlockForShader");

} // end setUniformBlockForShader

void SharedProjectionAndViewing::findOffets( GLuint shaderProgram )
{
	if ( projViewBlockSize > 0 ) {

		// Get an identifier for a buffer
		glGenBuffers(1, &projViewBuffer);

		// Bind the buffer
		glBindBuffer(GL_UNIFORM_BUFFER, projViewBuffer);
 
		// Allocate the buffer. Does not load data. Note the use of NULL where the data would normally be.
		// Data is not loaded because the above struct will not be byte alined with the uniform block.
		glBufferData(GL_UNIFORM_BUFFER, projViewBlockSize, NULL, GL_DYNAMIC_DRAW);

		// Assign the buffer to a binding point to be the same as the uniform in the shader(s). In this case 1.
		glBindBufferBase(GL_UNIFORM_BUFFER, projectionViewBlockBindingPoint, projViewBuffer);

	}
		
	if ( worldEyeBlockSize > 0 ) {

		// Get an identifier for a buffer
		glGenBuffers(1, &worldEyeBuffer);

		// Bind the buffer
		glBindBuffer(GL_UNIFORM_BUFFER, worldEyeBuffer);
 
		// Allocate the buffer. Does not load data. Note the use of NULL where the data would normally be.
		// Data is not loaded because the above struct will not be byte alined with the uniform block.
		glBufferData(GL_UNIFORM_BUFFER, worldEyeBlockSize, NULL, GL_DYNAMIC_DRAW);

		// Assign the buffer to a binding point to be the same as the uniform in the shader(s). In this case 1.
		glBindBufferBase(GL_UNIFORM_BUFFER, worldEyeBlockBindingPoint, worldEyeBuffer);

		blockSizeAndOffetsSet = true;
	}

	checkOpenGLErrors("findOffets");

} // end findOffets

void SharedProjectionAndViewing::findBlockSizeSetBindingPoint( GLuint shaderProgram )
{
	// Get the index of the "projectionViewBlock"
	projViewBlockIndex = glGetUniformBlockIndex(shaderProgram, "projectionViewBlock"); 
	//cout << "projectionViewBlock index is " << projViewBlockIndex << endl;

	if ( checkLocationFound( "projectionViewBlock", projViewBlockIndex ) ) {

		// Determine the size in bytes of the uniform block.
		glGetActiveUniformBlockiv(shaderProgram, projViewBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &projViewBlockSize);
		//cout << "projectionViewBlock size is " << projViewBlockSize << endl;

		// Assign the block to a binding point. In this case 2.
		glUniformBlockBinding(shaderProgram, projViewBlockIndex, projectionViewBlockBindingPoint);
	}

	// Get the index of the "EyeBlock"
	worldEyeBlockIndex = glGetUniformBlockIndex(shaderProgram, "worldEyeBlock"); 
	//cout << "worldEyeBlock index is " << worldEyeBlockIndex << endl;

	if ( checkLocationFound( "worldEyeBlock", worldEyeBlockIndex  ) ) {

		// Determine the size in bytes of the uniform block.
		glGetActiveUniformBlockiv(shaderProgram, worldEyeBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &worldEyeBlockSize);
		//cout << "worldEyeBlock size is " << worldEyeBlockSize << endl;

		// Assign the block to a binding point. In this case 3.
		glUniformBlockBinding(shaderProgram, worldEyeBlockIndex, worldEyeBlockBindingPoint);
	}

	checkOpenGLErrors("findBlockSizeSetBindingPoint");

} // end findBlockSizeSetBindingPoint

void SharedProjectionAndViewing::setViewMatrix( glm::mat4 viewMatrix)
{
	if (projViewBlockSize > 0  ) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, projViewBuffer);

		this->viewMatrix = viewMatrix;

		glBufferSubData(GL_UNIFORM_BUFFER, viewLocation, sizeof(glm::mat4), glm::value_ptr(viewMatrix));
	}

	if (worldEyeBlockSize > 0 ) {

		// Bind the buffer.
		glBindBuffer(GL_UNIFORM_BUFFER, worldEyeBuffer);

		glm::vec3 viewPoint = (glm::inverse(viewMatrix)[3]).xyz;

		glBufferSubData(GL_UNIFORM_BUFFER, eyePositionLocation, sizeof(glm::vec3), glm::value_ptr(viewPoint));
	}

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	checkOpenGLErrors("setViewMatrix");

} // end setViewMatrix

void SharedProjectionAndViewing::setProjectionMatrix( glm::mat4 projectionMatrix)
{

	if (projViewBlockSize > 0  ) {
	
		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, projViewBuffer);

		this->projectionMatrix = projectionMatrix;

		glBufferSubData(GL_UNIFORM_BUFFER, projectionLocation, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	checkOpenGLErrors("setProjectionMatrix");

} // end setProjectionMatrix
