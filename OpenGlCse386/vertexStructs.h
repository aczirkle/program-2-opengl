#ifndef ___VERTEX_STRUCTS_H___
#define ___VERTEX_STRUCTS_H___

#define GLM_SWIZZLE
 
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/swizzle.hpp>
//#include <glm/gtc/constants.hpp>
 
struct pcVertexData
{
    glm::vec3 m_pos;
    glm::vec4 m_color;

    pcVertexData() {}

    pcVertexData(glm::vec3 pos, glm::vec4 col)
    {
        m_pos    = pos;
        m_color  = col;

    }
};

struct pnVertexData
{
    glm::vec3 m_pos;
    glm::vec3 m_normal;

    pnVertexData() {}

    pnVertexData(glm::vec3 pos, glm::vec3 norm)
    {
        m_pos    = pos;
        m_normal  = norm;
    }
};

struct pntVertexData
{
    glm::vec3 m_pos;
    glm::vec3 m_normal;
	glm::vec2 m_text;

    pntVertexData() {}

    pntVertexData(glm::vec3 pos, glm::vec3 norm, glm::vec2 text)
    {
        m_pos    = pos;
        m_normal  = norm;
		m_text = text;
    }
};

struct pncVertexData
{
	glm::vec3 m_pos;
	glm::vec3 m_normal;
	glm::vec4 m_color;
	
	pncVertexData() {}
	
	pncVertexData(glm::vec3 pos, glm::vec3 norm, glm::vec4 col)
	{
		m_pos = pos;
		m_normal = norm;
		m_color = col;
	}
};



#endif /* ___VERTEX_STRUCTS_H___ */