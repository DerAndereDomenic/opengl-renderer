#include <DataStructure/Mesh.h>

Mesh
Mesh::createObject()
{
	Mesh result;

	result._layout.add<float>(3);
	result._layout.add<float>(4);
	result._layout.add<float>(2);
	result._layout.add<float>(3);
	result._vertex_count = 0;

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

	return _vertex_count++;
}

void 
Mesh::addTriangle(const unsigned int vertex1, const unsigned int vertex2, const unsigned int vertex3)
{
	_indices.push_back(vertex1);
	_indices.push_back(vertex2);
	_indices.push_back(vertex3);
}