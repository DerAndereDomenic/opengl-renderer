#ifndef IO_OBJLOADER_H
#define IO_OBJLOADER_H

#include <DataStructure/Mesh.h>

namespace ObjLoader {

	/**
	*	\brief Loads a .obj file into a mesh (BETA: LIMITED)
	*	\param[in] path The path to the obj file
	*	\return The mesh extracted from the file
	*	\note: Mesh still has to be created
	*/
	Mesh loadObj(const char* path)
}

#endif