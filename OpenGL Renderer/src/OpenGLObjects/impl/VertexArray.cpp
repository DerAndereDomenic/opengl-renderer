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
VertexArray::addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout)
{
	vbo.bind();
	bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < layout.getElements().size(); ++i)
	{
		BufferElement element = layout.getElements()[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element._count, element._type, element._normalized, layout.getVertexSize(), (const void*)offset);
		offset += element._count * BufferElement::getSizeOfType(element._type);
	}
	_count = vbo.getCount();
	_attribCount = layout.getElements().size();
}

void 
VertexArray::addInstanceBuffer(const VertexBuffer& vbo, const BufferElement& element)
{
	bind();
	glEnableVertexAttribArray(_attribCount);
	vbo.bind();
	glVertexAttribPointer(_attribCount, element._count, element._type, element._normalized, element._count*BufferElement::getSizeOfType(element._type), (const void*)0);
	vbo.unbind();
	glVertexAttribDivisor(_attribCount, 1);
	_count += element._count;
	++_attribCount;
}

void 
VertexArray::setIndexBuffer(const IndexBuffer &ibo)
{
	_ibo = ibo;
	_hasIBO = true;
}