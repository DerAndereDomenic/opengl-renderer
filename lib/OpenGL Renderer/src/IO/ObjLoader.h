#ifndef __OPENGLRENDERER_IO_OBJLOADER_H
#define __OPENGLRENDERER_IO_OBJLOADER_H

#include <DataStructure/Mesh.h>

namespace ObjLoader 
{

	/**
	*	\brief Loads any assimp supported 3D file into a Mesh class
	*	\param[in] path The path to the obj file
	*	\param[in] calcTangent If the tangents should be calculated
	*	\return The mesh extracted from the file
	*	\note: Mesh still has to be created
	*/
	std::vector<Mesh> loadObj(const std::string& path, const bool calcTangent = false);
}

#endif