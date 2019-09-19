#include <OpenGLObjects/VertexBuffer.h>
#include <GL/glew.h>

VertexBuffer 
VertexBuffer::createObject(float* data, unsigned int count)
{
	VertexBuffer result;
	glGenBuffers(0, &result._ID);
	glBindBuffer(GL_ARRAY_BUFFER, result._ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count, data, GL_STATIC_DRAW);

	result._size = count * sizeof(float);

	return result;
}

void 
VertexBuffer::destroyObject(VertexBuffer& vbo)
{
	glDeleteBuffers(0, &vbo._ID);
	vbo._size = 0;
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