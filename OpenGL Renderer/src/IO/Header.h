#ifndef IO_MESH_READER_H
#define IO_MESH_READER_H

#include <DataStructure/Mesh.h>
#include <string>

/**
*	\brief A namespace to model a Mesh reader
*/
namespace MeshReader
{
	/**
	*	\brief Reads a mesh form file
	*	\param[in] Path to the .obj file
	*	\return The mesh
	*	\note: Mesh still has to be created via create()
	*/
	Mesh readMesh(const std::string& path);
}

#endif