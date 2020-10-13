#ifndef OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H
#define OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>
#include <vector>

/**
*	\brief A struct to model the Layout of a single Element in the buffer
*/
struct BufferElement
{
	uint32_t _type; /**<< The Type of the stored data*/
	uint32_t _count; /**<< The count of types per Element*/
	unsigned char _normalized; /**<< If the value should be normalized*/

	/**
	*	\brief Size of the given input type in bytes
	*	\param[in] The type
	*	\return The size of the type in bytes
	*	\note: Supported for: GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE, GL_INT
	*/
	static uint32_t getSizeOfType(uint32_t type)
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
	*	\tparam The type that should be added
	*	\param[in] count The count of the values to be added
	*	\param[in] normalized = GL_FALSE
	*	\note: Only supported for: float, uint32_t, unsigned char, int
	*/
	template<typename T>
	void add(uint32_t count, unsigned char normalized = GL_FALSE)
	{
		static_assert(false);
	}

	template<>
	void
		add<float>(uint32_t count, unsigned char normalized)
	{
		_elements.push_back({ GL_FLOAT, count, normalized });
		_size_vertex += BufferElement::getSizeOfType(GL_FLOAT)*count;
	}

	template<>
	void
		add<uint32_t>(uint32_t count, unsigned char normalized)
	{
		_elements.push_back({ GL_UNSIGNED_INT, count, normalized });
		_size_vertex += BufferElement::getSizeOfType(GL_UNSIGNED_INT)*count;
	}

	template<>
	void
		add<unsigned char>(uint32_t count, unsigned char normalized)
	{
		_elements.push_back({ GL_UNSIGNED_BYTE, count, normalized });
		_size_vertex += BufferElement::getSizeOfType(GL_UNSIGNED_BYTE)*count;
	}

	template<>
	void
		add<int>(uint32_t count, unsigned char normalized)
	{
		_elements.push_back({ GL_INT, count, normalized });
		_size_vertex += BufferElement::getSizeOfType(GL_INT)*count;
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