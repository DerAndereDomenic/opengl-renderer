#ifndef OPENGL_OBJECTS_VERTEX_BUFFER_H
#define OPENGL_OBJECTS_VERTEX_BUFFER_H

#include <GL/glew.h>

/**
*	\brief Class to model a Vertex Buffer
*/
class VertexBuffer
{
public:
	/**
	*	\brief Create an empty Vertex Buffer Object
	*/
	VertexBuffer() = default;

	/**
	*	\brief Create a Vertex Buffer Object
	*	\param[in] data The Vertices Data
	*	\param[in] count The count of elements in the array
	*/
	static VertexBuffer createObject(const float* data, const unsigned int count, GLenum usage = GL_STATIC_DRAW);

	/**
	*	\brief Destroys the Vertex Buffer object
	*	\param[in] vbo The object
	*/
	static void destroyObject(VertexBuffer& vbo);

	/**
	*	\brief Bind the Buffer
	*/
	void bind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*/
	void unbind() const;

	/**
	*	\brief Changes the data in the vertex buffer object
	*	\param[in] data The new data
	*	\param[in] count The count of new elements
	*	\param[in] offset The data offset inside the vbo (default = 0)
	*/
	void changeData(const float* data, const unsigned int count, const unsigned int offset = 0);

	/**
	*	\brief Returns the count (number of elements) in the vbo
	*/
	inline unsigned int getCount() const { return _count; }
private:
	unsigned int _ID; /**<< The OpenGL identifier for the Vertex Buffer*/
	unsigned int _size; /**<< The Size of the Buffer in Bytes*/
	unsigned int _count; /**<< The number of elements in the vbo*/
};


#endif