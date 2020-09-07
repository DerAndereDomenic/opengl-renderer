#ifndef OPENGL_OBJECTS_VERTEX_ARRAY_H
#define OPENGL_OBJECTS_VERTEX_ARRAY_H

#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>
#include <OpenGLObjects/IndexBuffer.h>

/**
*	\brief A class to model a Vertex Array
*/
class VertexArray
{
public:
	/**
	*	\brief Creates an empty Vertex Array
	*/
	VertexArray() = default;

	/**
	*	\brief Creates a Vertex Array
	*	\return The Vertex Array Object
	*/
	static VertexArray createObject();

	/**
	*	\brief Destroys a Vertex Array object
	*	\param[in] vao The Vertex Array object to be destroyed
	*/
	static void destroyObject(VertexArray &vao);

	/**
	*	\brief Bind die Vertex Array object
	*/
	void bind() const;

	/**
	*	\brief Unbinds the Vertex Array object (bind 0)
	*/
	void unbind() const;

	/**
	*	\brief Renders the vao
	*	\note: If the Vertex Attributes where set manually, the number of elements in
	*		   the VBO have to be set via setCount(...) first
	*/
	void render() const;

	/**
	*	\brief Add a Layout for the given Vertex Buffer object
	*	\param[in] vbo The Vertex Buffer
	*	\param[in] layout The Layout for the Vertex Buffer
	*/
	void addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);

	/**
	*	\brief Add an instance array to the vao
	*	\param[in] vbo The instanced array vbo
	*	\param[in] layout The Layout for the Vertex Buffer
	*/
	void addInstanceBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);

	/**
	*	\brief Add a Layout for the given Vertex Buffer object and add an Index buffer to the vao
	*	\param[in] ibo The Index Buffer
	*/
	void setIndexBuffer(const IndexBuffer &ibo);

	/**
	*	\brief Sets the number of elements in the underlying vertex buffer
	*	\param[in] count The number of elements in the underlying VBO
	*/
	void setCount(unsigned int count);
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the Vertex Array*/
	IndexBuffer _ibo; /**<< The Index buffer binded to this vao*/
	unsigned int _count = 0; /**<< The number of elements in the underlying vbo*/
	bool _hasIBO = false; /**<< Checks if this vao has an index buffer*/
	unsigned int _attribCount = 0; /**<< The number of activated attributes*/
};


#endif