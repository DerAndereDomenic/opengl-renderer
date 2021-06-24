#include <OpenGLObjects/IndexBuffer.h>
#include <GL/glew.h>

 
IndexBuffer::IndexBuffer(const uint32_t* data, const uint32_t& count)
{
	_count = count;

	glGenBuffers(1, &_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_ID);
	_count = 0;
}

void 
IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void 
IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
IndexBuffer::bindDefault()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}