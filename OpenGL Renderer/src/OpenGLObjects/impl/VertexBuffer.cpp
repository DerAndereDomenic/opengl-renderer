#include <OpenGLObjects/VertexBuffer.h>
#include <GL/glew.h>

VertexBuffer 
VertexBuffer::createObject(float* data, unsigned int size)
{
	VertexBuffer result;
	glGenBuffers(0, &result._ID);
	glBindBuffer(GL_ARRAY_BUFFER, result._ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer 
VertexBuffer::destroyObject(VertexBuffer& vbo)
{
	glDeleteBuffers(0, &vbo._ID);
}

void 
VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void 
VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}