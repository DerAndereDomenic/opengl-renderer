#ifndef OPENGL_OBJECTS_INDEX_BUFFER_H
#define OPENGL_OBJECTS_INDEX_BUFFER_H

/**
*	\brief A class to model an Index Buffer
*/
class IndexBuffer
{
public:
	/**
	*	\brief Creates an empty Index Buffer
	*/
	IndexBuffer() = default;

	/**
	*	\brief Creates an Index Buffer
	*	\param[in] data The data for the indices
	*	\param[in] count The indice count
	*	return The Index Buffer Object
	*/
	static IndexBuffer createObject(unsigned int* data, unsigned int count);

	/**
	*	\brief Destroys the Index Buffer object
	*	\param[in] ibo The Index Buffer object
	*/
	static void destroyObject(IndexBuffer& ibo);

	/**
	*	\brief Binds the Index Buffer
	*/
	void bind();

	/**
	*	\brief Unbinds the Index Buffer (bind 0)
	*/
	void unbind();
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the Buffer*/
	unsigned int _count; /**<< The Index count*/
};

#endif