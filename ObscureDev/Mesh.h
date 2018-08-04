#pragma once
#include <glm.hpp>
#include <ext.hpp>

#include "../glCore/gl_core_4_5.h"

#include <cassert>

class Mesh
{
public:

	Mesh() : m_tri_count(0), m_vao(0), m_vbo(0), m_ibo(0), m_local_matrix(glm::mat4(1)) {}
	virtual ~Mesh();


	//*! Vertex structure
	struct Vertex 
	{
		glm::vec4 m_position;
		glm::vec4 m_normal;
		glm::vec2 m_tex_coord;
	};

	//*! Create a custom Quad
	void initialiseQuad();

	//*! Create a custom Quad - Full Screen
	void initialise_full_screen_quad();

	//*! Set up the mesh
	void initialise(unsigned int a_vertex_count, 
					const Vertex* a_vertices, 
					unsigned int a_index_count = 0,
					unsigned int* a_indices = nullptr);

	//*! Draw call
	virtual void draw();

	//*! Get the local transform matrix
	glm::mat4 const get_local_transform() { return m_local_matrix; };

	//*! Set position
	void set_position(const glm::vec4 a_position) { m_local_matrix[3] = a_position; };

	//*! Set scale
	void set_scale(const glm::vec3 a_scale);

protected:
	
	//*! Total triangle count
	unsigned int m_tri_count;
	//*! Vertex Array Object - Contains the m_vbo and the m_ibo* (Optional)
	unsigned int m_vao;
	//*! Vertex Buffer Object - Verticies positions
	unsigned int m_vbo;
	//*! Vertex Indicies % of 3
	unsigned int m_ibo;

private:
	//*! Local matrix
	glm::mat4 m_local_matrix;
};
