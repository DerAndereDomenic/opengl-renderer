#include <IO/ObjLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <DLogger/Logger.h>

std::vector<std::shared_ptr<Mesh>>
ObjLoader::loadObj(const std::string& path, const bool& calcTangent)
{
	std::vector<std::shared_ptr<Mesh>> meshes;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOGGER::ERROR("ERROR::ASSIMP::" + std::string(importer.GetErrorString()) + "\n");
		return meshes;
	}

	for (uint32_t k = 0; k < scene->mNumMeshes; ++k)
	{
		aiMesh* mesh = scene->mMeshes[k];
		std::shared_ptr<Mesh> output_mesh = std::make_shared<Mesh>(calcTangent);
		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			glm::vec3 uvw(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z);
			glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			output_mesh->addVertex(position, glm::vec4(0), uvw, normal);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			output_mesh->addTriangle(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
		}

		meshes.push_back(output_mesh);
	}
	
	return meshes;
}