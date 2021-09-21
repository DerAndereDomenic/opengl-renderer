#include <OpenGLObjects/RenderBuffer.h>

#include <glad/glad.h>

RenderBuffer::RenderBuffer(const uint32_t& width, const uint32_t& height)
{
	glGenRenderbuffers(1, &_ID);
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &_ID);
}

void 
RenderBuffer::setResolution(const uint32_t& width, const uint32_t& height)
{
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void 
RenderBuffer::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, _ID);
}

void 
RenderBuffer::unbind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void
RenderBuffer::bindDefault()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}