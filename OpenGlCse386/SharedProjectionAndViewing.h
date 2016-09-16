#ifndef _SHARED_PROJECTION_AND_VIEWING_H_
#define	_SHARED_PROJECTION_AND_VIEWING_H_

#include "VisualObject.h"

#define projectionViewBlockBindingPoint 2
#define worldEyeBlockBindingPoint 3

class SharedProjectionAndViewing
{
	public:
	SharedProjectionAndViewing(void);
	~SharedProjectionAndViewing(void);

	void setUniformBlockForShader(GLuint shaderProgram);

	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	void setProjectionMatrix( glm::mat4 projectionMatrix);

	glm::mat4 getViewMatrix() { return viewMatrix; }
	void setViewMatrix( glm::mat4 viewMatrix);

	protected:

	void findOffets( GLuint shaderProgram );

	void findBlockSizeSetBindingPoint( GLuint shaderProgram );

	GLuint projectionLocation; 
	glm::mat4 projectionMatrix;

	GLuint viewLocation;
	glm::mat4 viewMatrix;

	GLuint eyePositionLocation; 
	GLuint eyePositionPoint; 
		
	GLuint projViewBuffer; // Identifier for the buffer. There would only be one buffer to feed several uniform blocks.
	GLint projViewBlockSize; // Size in bytes of both the buffer and the uniform blocks in all the the shaders. 
	GLuint projViewBlockIndex; // Identifier for the uniform block.

	GLuint worldEyeBuffer; // Identifier for the buffer. There would only be one buffer to feed several uniform blocks.
	GLint worldEyeBlockSize; // Size in bytes of both the buffer and the uniform blocks in all the the shaders. 
	GLuint worldEyeBlockIndex; // Identifier for the uniform block. 

	bool blockSizeAndOffetsSet;
};

#endif // _SHARED_PROJECTION_AND_VIEWING_H_

