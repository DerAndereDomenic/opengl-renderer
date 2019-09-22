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
}