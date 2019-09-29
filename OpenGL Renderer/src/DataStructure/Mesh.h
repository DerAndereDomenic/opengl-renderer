#ifndef DATASTRUCTURE_MESH_H
#define DATASTRUCTURE_MESH_H

#include <Renderer/RenderWindow.h>
#include <glm/glm.hpp>
#include <vector>

/**
*	\brief A class to model a mesh
*/
class Mesh
{
public:
	/**
	*	\brief Create an empty mesh
	*/
	Mesh() = default;

	/**
	*	\brief Create a mesh
	*	\return The mesh
	*/
	static Mesh createObject();

	/**
	*	\brief Destroy the mesh
	*	\param[in] The mesh to be destroyed
	*/
	static void destroyObject(Mesh& mesh);

	/**
	*	\brief After adding vertex information with 'addVertex' this method
	*		   initializes the vbo, ibo and vao and makes it ready to be rendered
	*/
	void create();

	/**
	*	\brief Renders the mesh
	*	\param[in] window The window the mesh should be rendered in
	*	\param[in] shader The shader used for the mesh
	*	\note The mesh has to be created via 'create()' before rendering
	*/
	void render(RenderWindow window, Shader shader);

	/**
	*	\brief Adds a vertex to the mesh
	*	\param[in] position The position of the vertex
	*	\param[in] color The color of the vertex
	*	\param[in] texture The texture coordinate of the vertex
	*	\return The number of vertex in the buffer (count)
	*	\note The return can be used for the ibo initialized with 'addTriangle'
	*/
	unsigned int addVertex(glm::vec4 position, glm::vec4 color, glm::vec2 texture);

	/**
	*	\brief Add a triangle to the ibo
	*	\param[in] vertex1 Id of the first vertex
	*	\param[in] vertex2 Id of the second vertex
	*	\param[in] vertex3 Id of the third vertex
	*	\note The ids are calculated by 'addVertex'
	*/
	void addTriangle(const unsigned int vertex1, const unsigned int vertex2, const unsigned int vertex3);
private:
	std::vector<float> _vertices; /**<< A buffer to safe vertex information*/
	std::vector<unsigned int> _indices; /**<< A buffer to safe index information*/

	unsigned int vertex_count; /**<< The count of vertices in the mesh*/

	VertexArray _vao; /**<< The vertex array object of the mesh*/
	VertexBuffer _vbo; /**<< The vertex buffer object of the mesh*/
	IndexBuffer _ibo; /**<< The index buffer object of the mesh*/
	VertexBufferLayout _layout; /**<< The layout of the vertex buffer object*/
};

#endif