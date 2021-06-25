#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H

#include <glad/glad.h>
#include <vector>

/**
*	\brief A struct to model the Layout of a single Element in the buffer
*/
struct BufferElement
{
	uint32_t _type; /**<< The Type of the stored data*/
	uint32_t _count; /**<< The count of types per Element*/
	uint8_t _normalized; /**<< If the value should be normalized*/

	/**
	*	\brief Size of the given input type in bytes
	*	\param[in] The type
	*	\return The size of the type in bytes
	*	\note: Supported for: GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE, GL_INT
	*/
	static uint32_t getSizeOfType(const uint32_t& type)
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
			case GL_INT: return sizeof(GLuint);
		}
		return 0;
	}
};

/**
*	\brief A class to model the Buffer Layout
*/
class VertexBufferLayout
{
public:
	/**
	*	\brief Creates a Vertex Buffer Layout
	*/
	VertexBufferLayout() = default;

	/**
	*	\brief Add Buffer Element to layout
	*	\param[in] type The element type
	*	\param[in] count The count of the values to be added
	*	\param[in] normalized = GL_FALSE
	*	\note: Only supported for: float, uint32_t, uint8_t, int32_t
	*/
	void
	add(const uint32_t& type, const uint32_t& count, const uint8_t& normalized = false)
	{
		_elements.push_back({ type, count, normalized });
		_size_vertex += BufferElement::getSizeOfType(type)*count;
	}

	/**
	*	\brief Get the elements for the Vertex Buffer
	*	\return The elements
	*/
	inline std::vector<BufferElement>
		getElements() const
	{
		return _elements;
	}

	/**
	*	\brief The size of a vertex in byte
	*	\return The size of a vertex in byte
	*/
	inline uint32_t
		getVertexSize() const
	{
		return _size_vertex;
	}

private:
	std::vector<BufferElement> _elements; /**<< The array with the different elements for a vertex*/
	uint32_t _size_vertex = 0; /**<< The size of a vertex in byte*/
};
#endif