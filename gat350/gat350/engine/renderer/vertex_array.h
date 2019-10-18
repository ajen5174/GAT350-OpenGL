#pragma once
#include "../engine.h"

class VertexArray
{
public:
	enum eAttrib
	{
		POSITION = 0,
		COLOR,
		TEXCOORD,
		MULTI
	};

	struct VertexBuffer
	{
		eAttrib attrib;
		GLuint vbo;
		GLsizei num;
	};

	VertexArray();
	~VertexArray();

	void CreateBuffer(eAttrib attrib, GLsizei size, GLsizei num_vertex, void* data);
	void SetAttribute(eAttrib attrib, GLint num_vertex, GLsizei stride, size_t offset);

	virtual void Draw(GLenum primitiveType = GL_TRIANGLES);

	void Bind() { glBindVertexArray(m_vao); }

protected:
	GLuint m_vao = 0;
	GLuint m_vertex_count = 0;
	std::vector<VertexBuffer> m_vertex_buffers;
};

