#ifndef DATA_STRUCTURE_MESH_HELPER
#define DATA_STRUCTURE_MESH_HELPER

#include <DataStructure/Mesh.h>

/**
*	\brief A namespace to hold mesh utility functions
*/
namespace MeshHelper
{
	/**
	*	\brief Creates a 1x1x1 cube at (0,0,0)
	*	\param[in] color The color of the cube
	*	\param[in] calcTangent If each vertex should hold it's tangent vector (default = false)
	*	\return The cube mesh
	*	\note: The mesh still has to be created
	*/
	Mesh cubeMesh(glm::vec4 color, const bool calcTangent = false);

	/**
	*	\brief Creates a lenXxlenYxlenZ cuboid at (0,0,0)
	*	\param[in] color The color of the cuboid
	*	\param[in] lenX The length in x direction
	*	\param[in] lenY The length in y direction
	*	\param[in] lenZ The length in z direction
	*	\param[in] calcTangent If each vertex should hold it's tangent vector (default = false)
	*	\return The cuboid mesh
	*	\note: The mesh still has to be created
	*/
	Mesh cuboidMesh(glm::vec4 color, float lenX, float lenY, float lenZ, const bool calcTangent = false);

	/**
	*	\brief Creates a quad at (0,0,0) with sidelength size
	*	\param[in] size The side length of the quad
	*	\param[in] calcTangent If each vertex should hold it's tangent vector (default = false)
	*	\return The quad mesh
	*	\note: The mesh still has to be created
	*/
	Mesh quadMesh(float size, const bool calcTangent = false);
}

#endif