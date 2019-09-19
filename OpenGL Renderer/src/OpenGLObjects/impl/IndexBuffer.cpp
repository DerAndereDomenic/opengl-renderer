#include <OpenGLObjects/IndexBuffer.h>
#include <GL/glew.h>

IndexBuffer 
IndexBuffer::createObject(unsigned int* data, unsigned int count)
{
	IndexBuffer result;

	result._count = count;

	glGenBuffers(0, &result._ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result._ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*count, data, GL_STATIC_DRAW);

	return result;
}

void 
IndexBuffer::destroyObject(IndexBuffer& ibo)
{
	glDeleteBuffers(0, &ibo._ID);
	ibo._count = 0;
}

void 
IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void 
IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}