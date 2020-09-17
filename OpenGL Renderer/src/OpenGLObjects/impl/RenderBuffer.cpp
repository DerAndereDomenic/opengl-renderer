#include <OpenGLObjects/RenderBuffer.h>

#include <GL/glew.h>

RenderBuffer 
RenderBuffer::createObject(unsigned int width, unsigned int height)
{
	RenderBuffer result;

	glGenRenderbuffers(1, &result._ID);
	glBindRenderbuffer(GL_RENDERBUFFER, result._ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	return result;
}

void 
RenderBuffer::destroyObject(RenderBuffer& rbo)
{
	glDeleteRenderbuffers(1, &rbo._ID);
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