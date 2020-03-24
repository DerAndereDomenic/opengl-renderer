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


	_vertices.clear();
	_indices.clear();
}

void
Mesh::render(RenderWindow window, Shader shader)
{
	window.render(_vao, _ibo, shader);
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
}