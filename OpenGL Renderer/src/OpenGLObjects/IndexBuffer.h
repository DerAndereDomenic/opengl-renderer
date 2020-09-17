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
	static IndexBuffer createObject(const unsigned int* data, const unsigned int count);

	/**
	*	\brief Destroys the Index Buffer object
	*	\param[in] ibo The Index Buffer object
	*/
	static void destroyObject(IndexBuffer& ibo);

	/**
	*	\brief Binds the Index Buffer
	*/
	void bind() const;

	/**
	*	\brief Unbinds the Index Buffer (bind 0)
	*/
	void unbind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault();

	/**
	*	\brief Gives the Element count
	*	\return The Element count
	*/
	inline unsigned int
	getCount() const { return _count; }

private:
	unsigned int _ID; /**<< The internal OpenGL handle for the Buffer*/
	unsigned int _count; /**<< The Index count*/
};

#endif