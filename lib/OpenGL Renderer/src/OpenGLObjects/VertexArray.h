#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_ARRAY_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_VERTEX_ARRAY_H

#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>
#include <OpenGLObjects/IndexBuffer.h>
#include <memory>

using Geometry = GLenum;

/**
*	\brief A class to model a Vertex Array
*/
class VertexArray
{
public:
	/**
	*	\brief Creates a Vertex Array
	*	\param[in] geometry The type of geometry that should be rendered (default = GL_TRIANGLES)
	*/
	VertexArray(const Geometry& geometry = GL_TRIANGLES);

	/**
	*	\brief Destroys a Vertex Array object
	*/
	~VertexArray();

	/**
	*	\brief Bind die Vertex Array object
	*/
	void bind() const;

	/**
	*	\brief Unbinds the Vertex Array object (bind 0)
	*/
	void unbind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault();

	/**
	*	\brief Renders the vao
	*	\note: If the Vertex Attributes where set manually, the number of elements in
	*		   the VBO have to be set via setCount(...) first
	*/
	void render() const;

	/**
	*	\brief Batch renderes the vao
	*	\param[in] nr_vertices The number of vertices of one primitive
	*	\param[in] nr_instances The number of instances that should be rendered
	*/
	void renderInstanced(const uint32_t& nr_vertices, const uint32_t& nr_instances) const;

	/**
	*	\brief Add a Layout for the given Vertex Buffer object
	*	\param[in] vbo The Vertex Buffer
	*	\param[in] layout The Layout for the Vertex Buffer
	*/
	void addBuffer(const std::shared_ptr<VertexBuffer> vbo, const VertexBufferLayout &layout);

	/**
	*	\brief Add an instance array to the vao
	*	\param[in] vbo The instanced array vbo
	*	\param[in] layout The Layout for the Vertex Buffer
	*/
	void addInstanceBuffer(const std::shared_ptr<VertexBuffer> vbo, const VertexBufferLayout& layout);

	/**
	*	\brief Add a Layout for the given Vertex Buffer object and add an Index buffer to the vao
	*	\param[in] ibo The Index Buffer
	*/
	void setIndexBuffer(const IndexBuffer &ibo);

	/**
	*	\brief Sets the number of elements in the underlying vertex buffer
	*	\param[in] count The number of elements in the underlying VBO
	*/
	void setCount(const uint32_t& count);
private:
	uint32_t _ID; /**<< The internal OpenGL handle for the Vertex Array*/
	IndexBuffer _ibo; /**<< The Index buffer binded to this vao*/
	uint32_t _count = 0; /**<< The number of elements in the underlying vbo*/
	bool _hasIBO = false; /**<< Checks if this vao has an index buffer*/
	uint32_t _attribCount = 0; /**<< The number of activated attributes*/
	Geometry _geometry = GL_TRIANGLES; /**<< The geometry type that should be rendered*/
};


#endif