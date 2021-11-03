#ifndef __OPENGLRENDERER_DATASTRUCTURE_MESH_HELPER
#define __OPENGLRENDERER_DATASTRUCTURE_MESH_HELPER

#include <DataStructure/Mesh.h>
#include <memory>

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
	std::shared_ptr<Mesh> cubeMesh(const glm::vec4& color, const bool& calcTangent = false);

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
	std::shared_ptr<Mesh> cuboidMesh(const glm::vec4& color, const float& lenX, const float& lenY, const float& lenZ, const bool& calcTangent = false);

	/**
	*	\brief Creates a quad at (0,0,0) with sidelength size
	*	\param[in] size The side length of the quad
	*	\param[in] calcTangent If each vertex should hold it's tangent vector (default = false)
	*	\return The quad mesh
	*	\note: The mesh still has to be created
	*/
	std::shared_ptr<Mesh> quadMesh(const float& size, const bool& calcTangent = false);
}

#endif