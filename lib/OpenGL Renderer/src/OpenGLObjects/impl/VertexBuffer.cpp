#include <OpenGLObjects/VertexBuffer.h>
 
VertexBuffer::VertexBuffer(const float* data, const uint32_t& count, const GLenum& usage)
{
	glGenBuffers(1, &_ID);
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count, data, usage);

	_size = count * sizeof(float);
	_count = count;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_ID);
	_size = 0;
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
VertexBuffer::changeData(const float* data, const uint32_t& count, const uint32_t& offset)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(float), data);
	unbind();
}