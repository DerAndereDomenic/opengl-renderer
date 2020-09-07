#include <OpenGLObjects/VertexArray.h>

VertexArray 
VertexArray::createObject()
{
	VertexArray result;
	glGenVertexArrays(1, &result._ID);
	return result;
}

void 
VertexArray::destroyObject(VertexArray &vao)
{
	glDeleteVertexArrays(1, &vao._ID);
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
VertexArray::render() const
{
	bind();
	_hasIBO ? glDrawElements(GL_TRIANGLES, _ibo.getCount(), GL_UNSIGNED_INT, (void*)0) :
		glDrawArrays(GL_TRIANGLES, 0, _count);
}

void
VertexArray::setCount(unsigned int count)
{
	_count = count;
}

void 
VertexArray::addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
	vbo.bind();
	bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < layout.getElements().size(); ++i)
	{
		BufferElement element = layout.getElements()[i];
		glEnableVertexAttribArray(_attribCount);
		glVertexAttribPointer(_attribCount, element._count, element._type, element._normalized, layout.getVertexSize(), (const void*)offset);
		offset += element._count * BufferElement::getSizeOfType(element._type);
		++_attribCount;
	}
	_count = vbo.getCount();
}

void 
VertexArray::addInstanceBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	addBuffer(vbo, layout);
	for (unsigned int i = 0; i < layout.getElements().size(); ++i)
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