#pragma once

#include "texture.h"
#include "../framework/resource.h"

class Framebuffer : public Resource
{
public:
	OBJECT_DECLARATION(Framebuffer, Resource)
	~Framebuffer();

	bool Create(const Name& name) override;
	void AttachTexture(const std::shared_ptr<Texture>& texture, GLenum attachment = GL_COLOR_ATTACHMENT0);
	void CreateDepthbuffer(u32 width, u32 height);
	
	void Bind();
	void Unbind();

public:
	GLuint m_framebuffer = 0;
	GLuint m_depthbuffer = 0;

	std::shared_ptr<Texture> m_texture;
};