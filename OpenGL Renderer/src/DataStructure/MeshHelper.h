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
	*	\return The cube mesh
	*	\note: The mesh still has to be created
	*/
	Mesh cubeMesh(glm::vec4 color);
}

#endif