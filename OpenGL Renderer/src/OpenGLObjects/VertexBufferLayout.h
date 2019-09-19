#ifndef OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H
#define OPENGL_OBJECTS_VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>

/**
*	\brief A struct to model the Layout of a single Element in the buffer
*/
struct BufferElement
{
	unsigned int _type; /**<< The Type of the stored data*/
	unsigned int _count; /**<< The count of types per Element*/
	unsigned char _normalized; /**<< If the value should be normalized*/

	/**
	*	\brief Size of the given input type in bytes
	*	\param[in] The type
	*	\return The size of the type in bytes
	*	\note: Supported for: GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE, GL_INT
	*/
	static unsigned int getSizeOfType(unsigned int type)
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

#endif