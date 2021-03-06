#include <DataStructure/Mesh.h>

Mesh::Mesh(const bool& calcTangent)
{
	_layout.add(GL_FLOAT, 3);	//Position
	_layout.add(GL_FLOAT, 4);	//Color
	_layout.add(GL_FLOAT, 3);	//Texture coordinates
	_layout.add(GL_FLOAT, 3);	//Normal
	_layout.add(GL_FLOAT, 3);	//Tangent
	_vertex_count = 0;
	_calcTangent = calcTangent;
}
 
Mesh::~Mesh()
{
	_vertex_count = 0;
	_indices.clear();
	_vertices.clear();
}

void 
Mesh::create()
{
	_vbo = std::make_shared<VertexBuffer>(_vertices.data(), _vertices.size());
	_vao = std::make_shared<VertexArray>();
	_vao->addBuffer(_vbo, _layout);
	_ibo = std::make_shared<IndexBuffer>(_indices.data(), _indices.size());
	_vao->setIndexBuffer(_ibo);

	_vertices.clear();
	_indices.clear();
}

void
Mesh::render()
{
	_vao->render();
}

uint32_t 
Mesh::addVertex(const glm::vec3& position, const glm::vec4& color, const glm::vec3& texture, const glm::vec3& normal)
{
	_vertices.push_back(position.x);
	_vertices.push_back(position.y);
	_vertices.push_back(position.z);
	
	_vertices.push_back(color.x);
	_vertices.push_back(color.y);
	_vertices.push_back(color.z);
	_vertices.push_back(color.w);
	
	_vertices.push_back(texture.x);
	_vertices.push_back(texture.y);
	_vertices.push_back(texture.z);

	_vertices.push_back(normal.x);
	_vertices.push_back(normal.y);
	_vertices.push_back(normal.z);

	_vertices.push_back(0);
	_vertices.push_back(0);
	_vertices.push_back(0);

	return _vertex_count++;
}

void 
Mesh::addTriangle(const uint32_t& vertex1, const uint32_t& vertex2, const uint32_t& vertex3)
{
	if (_calcTangent)
	{
		calculateTangent(vertex1, vertex2, vertex3);
	}
	_indices.push_back(vertex1);
	_indices.push_back(vertex2);
	_indices.push_back(vertex3);
}

void
Mesh::addFaces(const uint32_t& num_faces, const glm::vec3* positions, const glm::ivec3* faces, const glm::vec3* uvw)
{
	for (uint32_t i = 0; i < num_faces; ++i)
	{
		glm::vec3 point1 = positions[faces[i].x];
		glm::vec3 point2 = positions[faces[i].y];
		glm::vec3 point3 = positions[faces[i].z];

		glm::vec3 uvw1 = uvw[faces[i].x];
		glm::vec3 uvw2 = uvw[faces[i].y];
		glm::vec3 uvw3 = uvw[faces[i].z];

		glm::vec3 normal = glm::normalize(glm::cross(point2 - point1, point3 - point1));

		//TODO: Make color changable
		uint32_t idx1 = this->addVertex(point1, glm::vec4(1), uvw1, normal);
		uint32_t idx2 = this->addVertex(point2, glm::vec4(1), uvw2, normal);
		uint32_t idx3 = this->addVertex(point3, glm::vec4(1), uvw3, normal);

		this->addTriangle(idx1, idx2, idx3);
	}
}

void 
Mesh::calculateTangent(const uint32_t& index1, const uint32_t& index2, const uint32_t& index3)
{
	//Get data for the vertices
	float vertex1[VERTEX_SIZE];
	float vertex2[VERTEX_SIZE];
	float vertex3[VERTEX_SIZE];

	uint32_t id1 = VERTEX_SIZE * index1;
	uint32_t id2 = VERTEX_SIZE * index2;
	uint32_t id3 = VERTEX_SIZE * index3;

	for (uint32_t i = 0; i < VERTEX_SIZE; ++i)
	{
		vertex1[i] = _vertices[id1 + i];
		vertex2[i] = _vertices[id2 + i];
		vertex3[i] = _vertices[id3 + i];
	}

	glm::vec3 pos1(vertex1[0], vertex1[1], vertex1[2]);
	glm::vec3 pos2(vertex2[0], vertex2[1], vertex2[2]);
	glm::vec3 pos3(vertex3[0], vertex3[1], vertex3[2]);

	glm::vec2 uv1(vertex1[7], vertex1[8]);
	glm::vec2 uv2(vertex2[7], vertex2[8]);
	glm::vec2 uv3(vertex3[7], vertex3[8]);

	//Calculating tangent
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;

	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float det = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent;
	tangent.x = det * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = det * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = det * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = glm::normalize(tangent);

	//Write tangent into buffer
	for (uint32_t i = 0; i < 3; ++i)
	{
		//Start of current vertex + position of tangent + current position in vector
		_vertices[id1 + 13 + i] = tangent[i];
		_vertices[id2 + 13 + i] = tangent[i];
		_vertices[id3 + 13 + i] = tangent[i];
	}
}