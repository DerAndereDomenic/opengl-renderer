#include <IO/ObjLoader.h>

Mesh
ObjLoader::loadObj(const char* path) 
{
	Mesh output_mesh = Mesh::createObject();

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_uvs;

	FILE* file = fopen(path, "r");
	if (file == NULL) 
	{
		std::cout << "ERROR::LOADOBJ: " << path << " not found!" << std::endl;
		return output_mesh;
	}

	while (true)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}
		else
		{
			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 position;
				fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
				temp_vertices.push_back(position);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9)
				{
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return output_mesh;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i += 3)
	{
		unsigned int index_v1 = vertexIndices[i] - 1;
		unsigned int index_t1 = uvIndices[i] - 1;
		unsigned int index_n1 = normalIndices[i] - 1;

		unsigned int index_v2 = vertexIndices[i+1] - 1;
		unsigned int index_t2 = uvIndices[i+1] - 1;
		unsigned int index_n2 = normalIndices[i+1] - 1;

		unsigned int index_v3 = vertexIndices[i + 2] - 1;
		unsigned int index_t3 = uvIndices[i + 2] - 1;
		unsigned int index_n3 = normalIndices[i + 2] - 1;

		unsigned int id1 = output_mesh.addVertex(temp_vertices[index_v1], glm::vec4(0), temp_uvs[index_t1], temp_normals[index_n1]);
		unsigned int id2 = output_mesh.addVertex(temp_vertices[index_v2], glm::vec4(0), temp_uvs[index_t2], temp_normals[index_n2]);
		unsigned int id3 = output_mesh.addVertex(temp_vertices[index_v3], glm::vec4(0), temp_uvs[index_t3], temp_normals[index_n3]);

		output_mesh.addTriangle(id1, id2, id3);
	}
	fclose(file);
	return output_mesh;
}