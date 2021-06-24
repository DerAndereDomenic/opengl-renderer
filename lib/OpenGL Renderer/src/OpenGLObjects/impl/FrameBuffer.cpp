#include <OpenGLObjects/FrameBuffer.h>
#include <GL/glew.h>
#include <iostream>
#include <DLogger/Logger.h>

FrameBuffer::FrameBuffer(const uint32_t& width, const uint32_t& height)
{
	_width = width;
	_height = height;

	glGenFramebuffers(1, &_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

FrameBuffer::~FrameBuffer()
{
	_width = 0;
	_height = 0;
	glDeleteFramebuffers(1, &_ID);
	for (uint32_t i = 0; i < _render_textures.size(); ++i) 
	{
		Texture::destroyObject(_render_textures[i]);
	}
	_render_textures.clear();
	RenderBuffer::destroyObject(_depth_stencil);
}

void
FrameBuffer::attachColor()
{
	bind();
	Texture texture = Texture::createObject<void>(_width, _height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _render_textures.size(), GL_TEXTURE_2D, texture.getID(), 0);
	_render_textures.push_back(texture);
}

void
FrameBuffer::attachColor(const Texture& color_buffer)
{
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _render_textures.size(), GL_TEXTURE_2D, color_buffer.getID(), 0);
	_render_textures.push_back(color_buffer);
}

void 
FrameBuffer::attachHDR()
{
	bind();
	Texture texture = Texture::createObject(_width, _height, (void*)NULL, TEXTURE, GL_RGBA16F, RGBA, GL_FLOAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _render_textures.size(), GL_TEXTURE_2D, texture.getID(), 0);
	_render_textures.push_back(texture);
}

void
FrameBuffer::attachRenderBuffer()
{
	bind();
	_depth_stencil = RenderBuffer::createObject(_width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depth_stencil.getID());
}

void
FrameBuffer::attachDepthMap()
{
	bind();
	Texture texture = Texture::createObject(_width, _height, (void*)NULL, TEXTURE, DEPTH, DEPTH, GL_FLOAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.getID(), 0);
	_render_textures.push_back(texture);
}

void FrameBuffer::disableColor()
{
	bind();
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}

bool
FrameBuffer::verify()
{
	bind();
	uint32_t error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (error != GL_FRAMEBUFFER_COMPLETE)
	{
		LOGGER::ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete: " + std::to_string(error) + "\n");
		return false;
	}
	return true;
}

void 
FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

void 
FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void
FrameBuffer::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void
FrameBuffer::clear(const GLclampf& r, const GLclampf& g, const GLclampf& b, const GLclampf& a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}