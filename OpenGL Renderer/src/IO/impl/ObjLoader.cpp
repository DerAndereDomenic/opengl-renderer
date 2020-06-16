#include <IO/ObjLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::vector<Mesh>
ObjLoader::loadObj(const char* path, const bool calcTangent)
{
	std::vector<Mesh> meshes;
	Mesh output_mesh = Mesh::createObject(calcTangent);
	

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		meshes.push_back(output_mesh);
		return meshes;
	}

	aiMesh* mesh = scene->mMeshes[0];

	for (unsigned int i = 0; i < mesh->mNumVertices;++i)
	{
		glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec2 uv(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		output_mesh.addVertex(position, glm::vec4(0), uv, normal);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
	{
		aiFace face = mesh->mFaces[i];
		output_mesh.addTriangle(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
	}

	meshes.push_back(output_mesh);
	return meshes;
}