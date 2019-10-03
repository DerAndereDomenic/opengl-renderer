#include <OpenGLObjects/FrameBuffer.h>
#include <GL/glew.h>
#include <iostream>

FrameBuffer 
FrameBuffer::createObject(unsigned int width, unsigned int height)
{
	FrameBuffer result;
	glGenFramebuffers(1, &result._ID);
	glBindFramebuffer(GL_FRAMEBUFFER, result._ID);

	result._render_texture = Texture::createObject(width, height);
	result._depth_stencil = RenderBuffer::createObject(width, height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result._render_texture.getID(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, result._depth_stencil.getID());

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
	}

	return result;
}

void 
FrameBuffer::destroyObject(FrameBuffer& object)
{
	glDeleteFramebuffers(1, &object._ID);
	Texture::destroyObject(object._render_texture);
	RenderBuffer::destroyObject(object._depth_stencil);
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