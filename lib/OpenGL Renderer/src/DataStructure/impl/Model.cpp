#include <DataStructure/Model.h>
#include <DLogger/Logger.h>

Model::Model(const std::string& path, const bool& calcTangents)
{
	loadModel(path, calcTangents);
}

Model::~Model()
{
	meshes.clear();
	materials.clear();
}

void 
Model::render(const std::shared_ptr<Shader> shader)
{

}

void 
Model::loadModel(const std::string& path, const bool& calcTangents)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOGGER::ERROR("ERROR::ASSIMP::" + std::string(importer.GetErrorString()) + "\n");
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	loadMaterials(scene);
	processNode(scene->mRootNode, scene, calcTangents);
}

void 
Model::processNode(aiNode* node, const aiScene *scene, const bool& calcTangents)
{
	for(uint32_t i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		int32_t matIndex = mesh->mMaterialIndex >= 0 ? mesh->mMaterialIndex : -1;

		meshes.push_back(std::make_pair(processMesh(mesh, scene, calcTangents), matIndex));
	}

	for (uint32_t i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene, calcTangents);
	}
}

std::shared_ptr<Mesh> 
Model::processMesh(aiMesh* mesh, const aiScene* scene, const bool& calcTangents)
{
	std::shared_ptr<Mesh> output_mesh = std::make_shared<Mesh>(calcTangents);
	for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
	{
		glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 uvw(0);
		if(mesh->mTextureCoords[0])
		{
			uvw = glm::vec3(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z);
		}
		glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		output_mesh->addVertex(position, glm::vec4(0), uvw, normal);
	}

	for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		output_mesh->addTriangle(face.mIndices[0], face.mIndices[1], face.mIndices[2]);
	}

	return output_mesh;
}

void
Model::loadMaterials(const aiScene* scene)
{
	for(uint32_t i = 0; i < scene->mNumMaterials; ++i)
	{
		std::shared_ptr<Material> mat = std::make_shared<Material>("materialmap");

		aiMaterial* material = scene->mMaterials[i];

		//Diffuse Texture
		if (material->GetTextureCount(aiTextureType_DIFFUSE) == 1)
		{
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			mat->texture_diffuse = std::make_shared<Texture>(directory + "/" + str.C_Str());
			mat->useTextures = true;
		}

		//Specular Texture
		if (material->GetTextureCount(aiTextureType_SPECULAR) == 1)
		{
			aiString str;
			material->GetTexture(aiTextureType_SPECULAR, 0, &str);
			mat->texture_specular = std::make_shared<Texture>(directory + "/" + str.C_Str());
			mat->useTextures = true;
		}

		//Height Texture
		if (material->GetTextureCount(aiTextureType_HEIGHT) == 1)
		{
			aiString str;
			material->GetTexture(aiTextureType_HEIGHT, 0, &str);
			mat->texture_height = std::make_shared<Texture>(directory + "/" + str.C_Str());
			mat->useTextures = true;
		}

		//Normal Texture
		if (material->GetTextureCount(aiTextureType_NORMALS) == 1)
		{
			aiString str;
			material->GetTexture(aiTextureType_NORMALS, 0, &str);
			mat->texture_normal = std::make_shared<Texture>(directory + "/" + str.C_Str());
			mat->useTextures = true;
		}

		aiColor3D color;
		float shininess;
		aiShadingMode mode;

		material->Get(AI_MATKEY_SHININESS, shininess);
		mat->shininess = shininess;

		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
		mat->ambient = glm::vec3(color.r, color.g, color.b);

		material->Get(AI_MATKEY_SHADING_MODEL, mode);

		if(mode == aiShadingMode_PBR_BRDF)
		{
			mat->_type = GGX;
			float roughness;
			material->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
			mat->roughness = roughness;
		}
		else if(mode == aiShadingMode_Phong)
		{
			mat->_type = PHONG;
		}
		else
		{
			mat->_type = LAMBERT;
		}

		//Load albedos
		if (!mat->useTextures)
		{
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			mat->diffuse = glm::vec3(color.r, color.g, color.b);

			material->Get(AI_MATKEY_COLOR_SPECULAR, color);
			mat->specular = glm::vec3(color.r, color.g, color.b);
		}

		materials.push_back(mat);
	}
}
