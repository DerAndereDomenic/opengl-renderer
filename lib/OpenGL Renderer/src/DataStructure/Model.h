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

		Model(const std::string& path);

		~Model();

		void render(const std::shared_ptr<Shader> shader);

	private:
		void loadModel(const std::string& path);

		void processNode(aiNode* node, const aiScene *scene);

		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

		std::vector<std::shared_ptr<Mesh>> meshes;

		std::string directory;
};

#endif