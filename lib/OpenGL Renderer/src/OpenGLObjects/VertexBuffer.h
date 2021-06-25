#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_BUFFER_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_BUFFER_H

#include <glad/glad.h>
#include <cstdint>

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
	VertexBuffer(const float* data, const uint32_t& count, const GLenum& usage = GL_STATIC_DRAW);

	/**
	*	\brief Destroys the Vertex Buffer object
	*/
	~VertexBuffer();

	/**
	*	\brief Bind the Buffer
	*/
	void bind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*/
	void unbind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault();

	/**
	*	\brief Changes the data in the vertex buffer object
	*	\param[in] data The new data
	*	\param[in] count The count of new elements
	*	\param[in] offset The data offset inside the vbo (default = 0)
	*/
	void changeData(const float* data, const uint32_t& count, const uint32_t& offset = 0);

	/**
	*	\brief Returns the count (number of elements) in the vbo
	*/
	inline uint32_t getCount() const { return _count; }
private:
	uint32_t _ID; /**<< The OpenGL identifier for the Vertex Buffer*/
	uint32_t _size; /**<< The Size of the Buffer in Bytes*/
	uint32_t _count; /**<< The number of elements in the vbo*/
};


#endif