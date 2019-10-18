#include "vertex_array.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vao);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vao);

	for (VertexBuffer vertex_buffer : m_vertex_buffers)
	{
		glDeleteBuffers(1, &vertex_buffer.vbo);
	}

}

void VertexArray::CreateBuffer(eAttrib attrib, GLsizei size, GLsizei num_vertex, void* data)
{
	m_vertex_count = num_vertex;
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	VertexBuffer vertex_buffer = { attrib, vbo, num_vertex };
	m_vertex_buffers.push_back(vertex_buffer);
}

void VertexArray::SetAttribute(eAttrib attrib, GLint num_vertex, GLsizei stride, size_t offset)
{
	glEnableVertexAttribArray(attrib);

	glVertexAttribPointer(attrib, num_vertex, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));


}

void VertexArray::Draw(GLenum primitiveType)
{
	glBindVertexArray(m_vao);
	glDrawArrays(primitiveType, 0, m_vertex_count);
	glBindVertexArray(0);
}
