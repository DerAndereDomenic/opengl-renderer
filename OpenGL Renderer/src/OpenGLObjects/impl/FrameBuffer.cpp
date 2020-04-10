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
	Texture::destroyObject(object._render_textures[0]);
	RenderBuffer::destroyObject(object._depth_stencil);
}

void
FrameBuffer::attachColor()
{
	bind();
	_render_textures.push_back(Texture::createObject(_width, _height));
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_textures[0].getID(), 0);
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
	_render_textures.push_back(Texture::createObject(_width, _height, DEPTH, GL_FLOAT));
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _render_textures[0].getID(), 0);
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