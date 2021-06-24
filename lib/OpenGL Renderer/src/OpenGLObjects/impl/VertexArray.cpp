#include <OpenGLObjects/VertexArray.h>
 
VertexArray::VertexArray(const Geometry& geometry)
{
	glGenVertexArrays(1, &_ID);
	_geometry = geometry;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_ID);
}

void 
VertexArray::bind() const
{
	glBindVertexArray(_ID);
}

void 
VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void
VertexArray::bindDefault()
{
	glBindVertexArray(0);
}

void
VertexArray::render() const
{
	bind();
	_hasIBO ? glDrawElements(_geometry, _ibo.getCount(), GL_UNSIGNED_INT, (void*)0) :
		glDrawArrays(_geometry, 0, _count);
}

void
VertexArray::renderInstanced(const uint32_t& nr_vertices, const uint32_t& nr_instances) const
{
	bind();
	glDrawArraysInstanced(_geometry, 0, nr_vertices, nr_instances);
}

void
VertexArray::setCount(const uint32_t& count)
{
	_count = count;
}

void 
VertexArray::addBuffer(const std::shared_ptr<VertexBuffer> vbo, const VertexBufferLayout &layout)
{
	vbo->bind();
	bind();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < layout.getElements().size(); ++i)
	{
		BufferElement element = layout.getElements()[i];
		glEnableVertexAttribArray(_attribCount);
		glVertexAttribPointer(_attribCount, element._count, element._type, element._normalized, layout.getVertexSize(), (const void*)offset);
		offset += element._count * BufferElement::getSizeOfType(element._type);
		++_attribCount;
	}
	_count = vbo->getCount();
}

void 
VertexArray::addInstanceBuffer(const std::shared_ptr<VertexBuffer> vbo, const VertexBufferLayout& layout)
{
	addBuffer(vbo, layout);
	for (uint32_t i = 0; i < layout.getElements().size(); ++i)
	{
		glVertexAttribDivisor(_attribCount - 1 - i, 1);
	}
	
}

void 
VertexArray::setIndexBuffer(const IndexBuffer &ibo)
{
	_ibo = ibo;
	_hasIBO = true;
}