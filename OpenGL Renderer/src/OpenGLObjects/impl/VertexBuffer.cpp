#include <OpenGLObjects/VertexBuffer.h>

VertexBuffer 
VertexBuffer::createObject(const float* data, const unsigned int count, GLenum usage)
{
	VertexBuffer result;
	glGenBuffers(1, &result._ID);
	glBindBuffer(GL_ARRAY_BUFFER, result._ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count, data, usage);

	result._size = count * sizeof(float);
	result._count = count;

	return result;
}

void 
VertexBuffer::destroyObject(VertexBuffer& vbo)
{
	glDeleteBuffers(1, &vbo._ID);
	vbo._size = 0;
}

void 
VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void 
VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
VertexBuffer::bindDefault()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
VertexBuffer::changeData(const float* data, const unsigned int count, const unsigned int offset)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(float), data);
	unbind();
}