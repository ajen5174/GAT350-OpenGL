#include "vertex_index_array.h"

VertexIndexArray::VertexIndexArray()
{
}

VertexIndexArray::~VertexIndexArray()
{
	glDeleteBuffers(1, &m_ibo);
}

void VertexIndexArray::CreateIndexBuffer(GLenum index_type, GLsizei num_index, void* data)
{
	m_index_type = index_type;
	m_index_count = num_index;
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	size_t index_size = (m_index_type == GL_UNSIGNED_SHORT) ? sizeof(GLushort) : sizeof(GLuint);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size * num_index, data, GL_STATIC_DRAW);
}

void VertexIndexArray::Draw(GLenum primitiveType)
{
	glBindVertexArray(m_vao);
	glDrawElements(primitiveType, m_index_count, m_index_type, 0);
	glBindVertexArray(0);
}
