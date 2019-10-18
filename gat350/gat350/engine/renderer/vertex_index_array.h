#pragma once
#include "vertex_array.h"

class VertexIndexArray : public VertexArray
{
public:
	VertexIndexArray();
	virtual ~VertexIndexArray();

	void CreateIndexBuffer(GLenum index_type, GLsizei num_index, void* data);

	void Draw(GLenum primitiveType = GL_TRIANGLES) override;

protected:
	GLuint m_ibo = 0;
	GLuint m_index_count = 0;
	GLenum m_index_type = 0;
};