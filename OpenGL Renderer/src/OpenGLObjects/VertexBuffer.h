#ifndef OPENGL_OBJECTS_VERTEX_BUFFER_H
#define OPENGL_OBJECTS_VERTEX_BUFFER_H

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
	static VertexBuffer createObject(const float* data, const unsigned int count);

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
private:
	unsigned int _ID; /**<< The OpenGL identifier for the Vertex Buffer*/
	unsigned int _size; /**<< The Size of the Buffer in Bytes*/
};


#endif