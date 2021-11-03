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
		/**
		*	\brief Default constructor
		*/
		Model() = default;

		/**
		*	\brief Create a model
		*	\param[in] path The path to the file (gltf works best)
		*	\param[in] calcTangents If tangents (for normal mapping) should be calculated
		*/
		Model(const std::string& path, const glm::mat4& model = glm::mat4(1), const bool& calcTangents = false);

		/**
		*	\brief Destructor
		*/
		~Model();

		/**
		*	\brief Renders the model
		*	\param[in] shader The shader
		*/
		void 
		render(const std::shared_ptr<Shader>& shader);

		/**
		*	\brief Get the model matrix
		*	\return The model matrix
		*/
		inline glm::mat4
		getModel() { return _model; }

	private:
		/**
		*	\brief Load the model
		* 	\param[in] path The path to the file (gltf works best)
		*	\param[in] calcTangents If tangents (for normal mapping) should be calculated
		*/
		void 
		loadModel(const std::string& path, const bool& calcTangents);

		/**
		*	\brief Process a assimp node
		*	\param[in] node The node to process
		*	\param[in] scene The scene
		*	\param[in] calcTangents If tangents (for normal mapping) should be calculated
		*/
		void 
		processNode(aiNode* node, const aiScene *scene, const bool& calcTangents);

		/**
		*	\brief Processes a mesh
		*	\param[in] mesh The mesh to be processed
		*	\param[in] scene The scene
		*	\param[in] calcTangents If tangents (for normal mapping) should be calculated
		*	\return A pointer to the mesh
		*/
		std::shared_ptr<Mesh> 
		processMesh(aiMesh* mesh, const aiScene* scene, const bool& calcTangents);

		/**
		*	\brief Load the mateiral of a scene
		*	\param[in] scene The scene to process
		*/
		void
		loadMaterials(const aiScene* scene);

		std::vector<std::pair<std::shared_ptr<Mesh>, int32_t>> meshes;		/**<< A vector with meshes and index to the material */
		std::vector<std::shared_ptr<Material>> materials;					/**<< A vector with materials */
		std::string directory;												/**<< The model directory */
		glm::mat4 _model;													/**<< The model matrix */
};

#endif