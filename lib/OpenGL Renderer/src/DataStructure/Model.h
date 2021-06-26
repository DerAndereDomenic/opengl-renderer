#ifndef __OPENGLRENDERER_DATASTRUCTURE_MODEL_H
#define __OPENGLRENDERER_DATASTRUCTURE_MODEL_H

#include <string>
#include <Shader/Shader.h>
#include <DataStructure/Mesh.h>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Model
{
	public:
		Model() = default;

		Model(const std::string& path, const bool& calcTangents = false);

		~Model();

		void 
		render(const std::shared_ptr<Shader> shader);

	private:
		void 
		loadModel(const std::string& path, const bool& calcTangents);

		void 
		processNode(aiNode* node, const aiScene *scene, const bool& calcTangents);

		std::shared_ptr<Mesh> 
		processMesh(aiMesh* mesh, const aiScene* scene, const bool& calcTangents);

		void
		loadMaterials(const aiScene* scene);

		std::vector<std::pair<std::shared_ptr<Mesh>, int32_t>> meshes;

		std::vector<std::shared_ptr<Material>> materials;

		std::string directory;
};

#endif