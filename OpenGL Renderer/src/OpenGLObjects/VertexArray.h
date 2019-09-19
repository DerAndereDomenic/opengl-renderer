#ifndef OPENGL_OBJECTS_VERTEX_ARRAY_H
#define OPENGL_OBJECTS_VERTEX_ARRAY_H

#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>

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
	void bind();

	/**
	*	\brief Unbinds the Vertex Array object (bind 0)
	*/
	void unbind();

	/**
	*	\brief Add a Layout for the given Vertex Buffer object
	*	\param[in] vbo The Vertex Buffer
	*	\param[in] layout The Layout for the Vertex Buffer
	*/
	void addBuffer(VertexBuffer &vbo, VertexBufferLayout &layout);
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the Vertex Array*/
};


#endif