#include <DataStructure/Mesh.h>

Mesh
Mesh::createObject(const bool calcTangent)
{
	Mesh result;

	result._layout.add<float>(3);
	result._layout.add<float>(4);
	result._layout.add<float>(2);
	result._layout.add<float>(3);
	result._layout.add<float>(3);
	result._vertex_count = 0;
	result._calcTangent = calcTangent;

	return result;
}

void 
Mesh::destroyObject(Mesh& mesh)
{
	VertexArray::destroyObject(mesh._vao);
	VertexBuffer::destroyObject(mesh._vbo);
	IndexBuffer::destroyObject(mesh._ibo);
	mesh._vertex_count = 0;
	mesh._indices.clear();
	mesh._vertices.clear();
}

void 
Mesh::create()
{
	_vbo = VertexBuffer::createObject(_vertices.data(), _vertices.size());
	_vao = VertexArray::createObject();
	_vao.addBuffer(_vbo, _layout);
	_ibo = IndexBuffer::createObject(_indices.data(), _indices.size());
	_vao.setIndexBuffer(_ibo);

	_vertices.clear();
	_indices.clear();
}

void
Mesh::render()
{
	_vao.render();
}

unsigned int 
Mesh::addVertex(glm::vec3 position, glm::vec4 color, glm::vec2 texture, glm::vec3 normal)
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

	_vertices.push_back(normal.x);
	_vertices.push_back(normal.y);
	_vertices.push_back(normal.z);

	_vertices.push_back(0);
	_vertices.push_back(0);
	_vertices.push_back(0);

	return _vertex_count++;
}

void 
Mesh::addTriangle(const unsigned int vertex1, const unsigned int vertex2, const unsigned int vertex3)
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
Mesh::calculateTangent(const unsigned int index1, const unsigned int index2, unsigned int index3)
{
	//Get data for the vertices
	float vertex1[VERTEX_SIZE];
	float vertex2[VERTEX_SIZE];
	float vertex3[VERTEX_SIZE];

	unsigned int id1 = VERTEX_SIZE * index1;
	unsigned int id2 = VERTEX_SIZE * index2;
	unsigned int id3 = VERTEX_SIZE * index3;

	for (unsigned int i = 0; i < VERTEX_SIZE; ++i)
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
	for (unsigned int i = 0; i < 3; ++i)
	{
		//Start of current vertex + position of tangent + current position in vector
		_vertices[id1 + 12 + i] = tangent[i];
		_vertices[id2 + 12 + i] = tangent[i];
		_vertices[id3 + 12 + i] = tangent[i];
	}
}