#ifndef __OPENGLRENDERER_DATASTRUCTURE_MESH_H
#define __OPENGLRENDERER_DATASTRUCTURE_MESH_H

#include <Renderer/RenderWindow.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
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
*	The tangent may be (0,0,0) if bool calcTangent = false in Mesh()
*/
class Mesh
{
public:

	/**
	*	\brief Create a mesh
	*	\param[in] calcTangent If a tangent should be calculated and added to the vertices (default = false)
	*/
	Mesh(const bool& calcTangent = false);

	/**
	*	\brief Destroy the mesh
	*/
	~Mesh();

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
	*	\brief Add several faces at once.
	*	Vertex normals will be calculated by the given points in a face.
	*	\param[in] num_faces The number of faces to add
	*	\param[in] positions The positions of the vertices
	*	\param[in] faces An index set of faces
	*	\param[in] uvw The uvw coordinates responsible for the vertices
	*/
	void addFaces(const uint32_t& num_faces, const glm::vec3* positions, const glm::ivec3* faces, const glm::vec3* uvw);

	/**
	*	\brief Adds a vertex to the mesh
	*	\param[in] position The position of the vertex
	*	\param[in] color The color of the vertex
	*	\param[in] texture The texture coordinate of the vertex
	*	\param[in] normal The normal
	*	\return The number of vertex in the buffer (count)
	*	\note The return can be used for the ibo initialized with 'addTriangle'
	*/
	uint32_t addVertex(const glm::vec3& position, const glm::vec4& color, const glm::vec3& texture, const glm::vec3& normal);

	/**
	*	\brief Add a triangle to the ibo
	*	\param[in] vertex1 Id of the first vertex
	*	\param[in] vertex2 Id of the second vertex
	*	\param[in] vertex3 Id of the third vertex
	*	\note The ids are calculated by 'addVertex'
	*/
	void addTriangle(const uint32_t& vertex1, const uint32_t& vertex2, const uint32_t& vertex3);
private:

	/**
	*	\brief Calculate tangent for the current triangle
	*	\param[in] index1 Id of the first vertex
	*	\param[in] index2 Id of the second vertex
	*	\param[in] index3 Id of the third vertex
	*/
	void calculateTangent(const uint32_t& index1, const uint32_t& index2, const uint32_t& index3);

	std::vector<float> _vertices;			/**<< A buffer to safe vertex information*/
	std::vector<uint32_t> _indices;			/**<< A buffer to safe index information*/

	uint32_t _vertex_count;					/**<< The count of vertices in the mesh*/

	std::shared_ptr<VertexArray> _vao;		/**<< The vertex array object of the mesh*/
	std::shared_ptr<VertexBuffer> _vbo;		/**<< The vertex buffer object of the mesh*/
	std::shared_ptr<IndexBuffer> _ibo;		/**<< The index buffer object of the mesh*/
	VertexBufferLayout _layout;				/**<< The layout of the vertex buffer object*/

	bool _calcTangent = false;
};

#endif