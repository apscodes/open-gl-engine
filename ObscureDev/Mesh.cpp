#include "Mesh.h"
#include <cassert>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}


void Mesh::initialiseQuad()
{
	//*! Check that the mesh is not initialized already
	assert(m_vao == 0);

	//*! Generate Buffers
	//*! New Buffer object
	glGenBuffers(1, &m_vbo);
	//*! New Vertex Array container
	glGenVertexArrays(1, &m_vao);

	//*! Bind the vertex array (Mesh Wrapper) - Outer container
	glBindVertexArray(m_vao);

	//*! Bind the vertex buffer - Inner container - Bound to the outer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);


	//*! Define 6 vertices for 2 triangles
	Vertex vertices[6];
	
	//*! Define the positions of each vertex for the Quad
	vertices[0].m_position = { -0.5f,	0,	0.5f,  1 };
	vertices[1].m_position = { 0.5f,	0,	0.5f,  1 };
	vertices[2].m_position = { -0.5f,	0,	-0.5f, 1 };
	vertices[3].m_position = { -0.5f,	0,	-0.5f, 1 };
	vertices[4].m_position = { 0.5f,	0,	0.5f,  1 };
	vertices[5].m_position = { 0.5f,	0,	-0.5f, 1 };

	//*! Normals
	vertices[0].m_normal = { 0, 1, 0, 1 };
	vertices[1].m_normal = { 0, 1, 0, 1 };
	vertices[2].m_normal = { 0, 1, 0, 1 };
	vertices[3].m_normal = { 0, 1, 0, 1 };
	vertices[4].m_normal = { 0, 1, 0, 1 };
	vertices[5].m_normal = { 0, 1, 0, 1 };
	
	//*! Texture Coords
	vertices[0].m_tex_coord = { 0, 1 };
	vertices[1].m_tex_coord = { 1, 1 };
	vertices[2].m_tex_coord = { 0, 0 };

	vertices[3].m_tex_coord = { 0, 0 };
	vertices[4].m_tex_coord = { 1, 1 };
	vertices[5].m_tex_coord = { 1, 0 };
	

	//*! Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//*! Enable first element as position
	glEnableVertexAttribArray(0);
	//*! -------
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	
	//*! Enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,	sizeof(Vertex), (void*)32);


	//*! Unbind buffers
	glBindVertexArray(0);
	//*! m_vbo unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//*! Quad Tri-angle Count
	m_tri_count = 2;

}

//*! Creating a full Screen quad to stick on the camera
void Mesh::initialise_full_screen_quad()
{
	//*! Check that the mesh is not initialized already
	assert(m_vao == 0);

	//*! Generate Buffers
	//*! New Buffer object
	glGenBuffers(1, &m_vbo);
	//*! New Vertex Array container
	glGenVertexArrays(1, &m_vao);

	//*! Bind the vertex array (Mesh Wrapper) - Outer container
	glBindVertexArray(m_vao);

	//*! Bind the vertex buffer - Inner container - Bound to the outer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);


	float vertices[] = 
	{
		-1,1,	//*! Left top
		-1,-1,	//*! Left bottom
		1,1,	//*! Right top
		-1,-1,	//*! Left bottom
		1,-1,	//*! Right bottom
		1, 1	//*! Right top
	};


	//*! Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

	//*! Enable first element as position
	glEnableVertexAttribArray(0);
	//*! -------
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);

	//*! Unbind buffers
	glBindVertexArray(0);
	//*! m_vbo unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//*! Quad Tri-angle Count
	m_tri_count = 2;


}

//*! General Setup
void Mesh::initialise(unsigned int a_vertex_count, const Vertex * a_vertices, unsigned int a_index_count, unsigned int * a_indices)
{
	//*! This is true - continue
	assert(m_vao == 0);
	
	//*! Generate buffers
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
	
	//*! Bind vertex array aka a mesh wrapper
	glBindVertexArray(m_vao);
	
	//*! Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//*! Fill vertex buffer of the verties
	glBufferData(GL_ARRAY_BUFFER, a_vertex_count * sizeof(Vertex), a_vertices, GL_STATIC_DRAW);
	
	//*! Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,	sizeof(Vertex), 0);

	//*! Enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//*! Enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//*! Enable tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2 + sizeof(glm::vec2)));

	//*! Bind indices if there are any
	if (m_tri_count != 0) {
		glGenBuffers(1, &m_ibo);
		//*! Bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		//*! Fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			a_index_count * sizeof(unsigned int), a_indices, GL_STATIC_DRAW);
			m_tri_count = a_index_count / 3;
	}
	else 
	{
		m_tri_count = a_vertex_count / 3;
	}
	
	//*! Unbind buffers
	glBindVertexArray(0);
	//*! m_ibo unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//*! 
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Mesh::draw()
{
	//*! Bind the vertex array (Mesh Wrapper) - Outer container
	glBindVertexArray(m_vao);
	//*! Using indices or just vertices
	if (m_ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * m_tri_count,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * m_tri_count);
}

void Mesh::set_scale(const glm::vec3 a_scale)
{
	m_local_matrix[0][0] = a_scale.x;
	m_local_matrix[1][1] = a_scale.y;
	m_local_matrix[2][2] = a_scale.z;
}

