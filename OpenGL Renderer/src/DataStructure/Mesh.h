#ifndef DATASTRUCTURE_MESH_H
#define DATASTRUCTURE_MESH_H

#include <Renderer/RenderWindow.h>
#include <glm/glm.hpp>
#include <vector>
#define VERTEX_SIZE 16

/**
*	\brief A class to model a mesh
*	Each mesh has the following vertex layout:
*	3 - float: Position
*	4 - float: Color
*	3 - float: Texture coordinates
*	3 - float: Normal
*	3 - float: Tangent
*
*	The tangent may be (0,0,0) if bool calcTangent = false in Mesh::createObject()
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
	*	\param[in] calcTangent If a tangent should be calculated and added to the vertices (default = false)
	*	\return The mesh
	*/
	static Mesh createObject(const bool calcTangent = false);

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
	*	\note The mesh has to be created via 'create()' before rendering
	*/
	void render();

	/**
	*	\brief Adds a vertex to the mesh
	*	\param[in] position The position of the vertex
	*	\param[in] color The color of the vertex
	*	\param[in] texture The texture coordinate of the vertex
	*	\param[in] normal The normal
	*	\return The number of vertex in the buffer (count)
	*	\note The return can be used for the ibo initialized with 'addTriangle'
	*/
	uint32_t addVertex(glm::vec3 position, glm::vec4 color, glm::vec3 texture, glm::vec3 normal);

	/**
	*	\brief Add a triangle to the ibo
	*	\param[in] vertex1 Id of the first vertex
	*	\param[in] vertex2 Id of the second vertex
	*	\param[in] vertex3 Id of the third vertex
	*	\note The ids are calculated by 'addVertex'
	*/
	void addTriangle(const uint32_t vertex1, const uint32_t vertex2, const uint32_t vertex3);
private:

	/**
	*	\brief Calculate tangent for the current triangle
	*	\param[in] index1 Id of the first vertex
	*	\param[in] index2 Id of the second vertex
	*	\param[in] index3 Id of the third vertex
	*/
	void calculateTangent(const uint32_t index1, const uint32_t index2, uint32_t index3);

	std::vector<float> _vertices; /**<< A buffer to safe vertex information*/
	std::vector<uint32_t> _indices; /**<< A buffer to safe index information*/

	uint32_t _vertex_count; /**<< The count of vertices in the mesh*/

	VertexArray _vao; /**<< The vertex array object of the mesh*/
	VertexBuffer _vbo; /**<< The vertex buffer object of the mesh*/
	IndexBuffer _ibo; /**<< The index buffer object of the mesh*/
	VertexBufferLayout _layout; /**<< The layout of the vertex buffer object*/

	bool _calcTangent = false;
};

#endif