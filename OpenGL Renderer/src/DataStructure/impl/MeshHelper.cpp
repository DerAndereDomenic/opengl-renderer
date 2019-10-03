#include <DataStructure/MeshHelper.h>

Mesh
MeshHelper::cubeMesh(glm::vec4 color)
{
	Mesh mesh = Mesh::createObject();
	float x = 0.0f, y = 0.0f, z = 0.0f;
	glm::vec4 p1(x - 0.5, y - 0.5, z + 0.5, 1);
	glm::vec4 p2(x + 0.5, y - 0.5, z + 0.5, 1);
	glm::vec4 p3(x + 0.5, y + 0.5, z + 0.5, 1);
	glm::vec4 p4(x - 0.5, y + 0.5, z + 0.5, 1);
	glm::vec4 p5(x + 0.5, y - 0.5, z - 0.5, 1);
	glm::vec4 p6(x - 0.5, y - 0.5, z - 0.5, 1);
	glm::vec4 p7(x - 0.5, y + 0.5, z - 0.5, 1);
	glm::vec4 p8(x + 0.5, y + 0.5, z - 0.5, 1);

	unsigned int v1, v2, v3, v4, v5, v6, v7, v8;

	glm::vec2 tex = glm::vec2(0, 0);
	glm::vec2 right(1.0f, 0);
	glm::vec2 up(0, 1.0f);

	//Front
	v1 = mesh.addVertex(p1, color, tex);
	v2 = mesh.addVertex(p2, color, tex + right);
	v3 = mesh.addVertex(p3, color, tex + up + right);
	v4 = mesh.addVertex(p4, color, tex + up);
	mesh.addTriangle(v1, v2, v3);
	mesh.addTriangle(v1, v3, v4);

	//Back
	v5 = mesh.addVertex(p5, color, tex);
	v6 = mesh.addVertex(p6, color, tex + right);
	v7 = mesh.addVertex(p7, color, tex + up + right);
	v8 = mesh.addVertex(p8, color, tex + up);
	mesh.addTriangle(v5, v6, v7);
	mesh.addTriangle(v5, v7, v8);

	//Right
	v2 = mesh.addVertex(p2, color, tex);
	v5 = mesh.addVertex(p5, color, tex + right);
	v8 = mesh.addVertex(p8, color, tex + up + right);
	v3 = mesh.addVertex(p3, color, tex + up);
	mesh.addTriangle(v2, v5, v8);
	mesh.addTriangle(v2, v8, v3);

	//Left
	v6 = mesh.addVertex(p6, color, tex);
	v1 = mesh.addVertex(p1, color, tex + right);
	v4 = mesh.addVertex(p4, color, tex + up + right);
	v7 = mesh.addVertex(p7, color, tex + up);
	mesh.addTriangle(v6, v1, v4);
	mesh.addTriangle(v6, v4, v7);

	//Top
	v4 = mesh.addVertex(p4, color, tex);
	v3 = mesh.addVertex(p3, color, tex + right);
	v8 = mesh.addVertex(p8, color, tex + up + right);
	v7 = mesh.addVertex(p7, color, tex + up);
	mesh.addTriangle(v4, v3, v8);
	mesh.addTriangle(v4, v8, v7);

	//Bottom
	v6 = mesh.addVertex(p6, color, tex);
	v5 = mesh.addVertex(p5, color, tex + right);
	v2 = mesh.addVertex(p2, color, tex + up + right);
	v1 = mesh.addVertex(p1, color, tex + up);
	mesh.addTriangle(v6, v5, v2);
	mesh.addTriangle(v6, v2, v1);

	return mesh;
}