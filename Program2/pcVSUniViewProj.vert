// Targeting version 3.3 of GLSL. If the compiler does not support 
// 3.3 it will cause an error.
#version 330

layout (std140) uniform projectionViewBlock 
{ 
	mat4 projectionMatrix; 
	mat4 viewMatrix; 
};

uniform mat4 modelMatrix;

layout (location = 0) in vec3 vertexPosition; 
layout (location = 1) in vec3 vertexNormal;
layout (location = 3) in vec2 vertexTexCoord;

out vec3 Normal0;
out vec3 WorldPos0;
out vec2 TexCoord0;

void main()
{
	// Calculate position in world coordinates
	WorldPos0 =(modelMatrix * vec4(vertexPosition, 1.0f)).xyz;
	// Calculate normal in world coordinates
	Normal0 =normalize(mat3(modelMatrix) * vertexNormal);
	// Pass Texture coordinates to the fragment shader 
	TexCoord0 = vertexTexCoord;

	// Calculate the position in clip coordinates
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);


}