#include <OpenGLObjects/FrameBuffer.h>
#include <GL/glew.h>
#include <iostream>

FrameBuffer 
FrameBuffer::createObject(unsigned int width, unsigned int height)
{
	FrameBuffer result;
	result._width = width;
	result._height = height;


	glGenFramebuffers(1, &result._ID);
	glBindFramebuffer(GL_FRAMEBUFFER, result._ID);

	return result;
}

void 
FrameBuffer::destroyObject(FrameBuffer& object)
{
	object._width = 0;
	object._height = 0;
	glDeleteFramebuffers(1, &object._ID);
	Texture::destroyObject(object._render_texture);
	RenderBuffer::destroyObject(object._depth_stencil);
}

void
FrameBuffer::attachColor()
{
	bind();
	_render_texture = Texture::createObject(_width, _height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_texture.getID(), 0);
}

void
FrameBuffer::attachRenderBuffer()
{
	bind();
	_depth_stencil = RenderBuffer::createObject(_width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depth_stencil.getID());
}

bool
FrameBuffer::verify()
{
	bind();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
		return false;
	}
	return true;
}

void 
FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _ID);
}

void 
FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}