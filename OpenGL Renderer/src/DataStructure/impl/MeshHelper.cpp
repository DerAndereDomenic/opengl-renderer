#include <DataStructure/MeshHelper.h>

Mesh
MeshHelper::cubeMesh(glm::vec4 color, const bool calcTangent)
{
	Mesh mesh = Mesh::createObject(calcTangent);
	float x = 0.0f, y = 0.0f, z = 0.0f;
	glm::vec3 p1(x - 0.5, y - 0.5, z + 0.5);
	glm::vec3 p2(x + 0.5, y - 0.5, z + 0.5);
	glm::vec3 p3(x + 0.5, y + 0.5, z + 0.5);
	glm::vec3 p4(x - 0.5, y + 0.5, z + 0.5);
	glm::vec3 p5(x + 0.5, y - 0.5, z - 0.5);
	glm::vec3 p6(x - 0.5, y - 0.5, z - 0.5);
	glm::vec3 p7(x - 0.5, y + 0.5, z - 0.5);
	glm::vec3 p8(x + 0.5, y + 0.5, z - 0.5);

	unsigned int v1, v2, v3, v4, v5, v6, v7, v8;

	glm::vec2 tex = glm::vec2(0, 0);
	glm::vec2 right(1.0f, 0);
	glm::vec2 up(0, 1.0f);

	//Front
	v1 = mesh.addVertex(p1, color, tex, glm::vec3(0,0,1));
	v2 = mesh.addVertex(p2, color, tex + right, glm::vec3(0, 0, 1));
	v3 = mesh.addVertex(p3, color, tex + up + right, glm::vec3(0, 0, 1));
	v4 = mesh.addVertex(p4, color, tex + up, glm::vec3(0, 0, 1));
	mesh.addTriangle(v1, v2, v3);
	mesh.addTriangle(v1, v3, v4);

	//Back
	v5 = mesh.addVertex(p5, color, tex, glm::vec3(0, 0, -1));
	v6 = mesh.addVertex(p6, color, tex + right, glm::vec3(0, 0, -1));
	v7 = mesh.addVertex(p7, color, tex + up + right, glm::vec3(0, 0, -1));
	v8 = mesh.addVertex(p8, color, tex + up, glm::vec3(0, 0, -1));
	mesh.addTriangle(v5, v6, v7);
	mesh.addTriangle(v5, v7, v8);

	//Right
	v2 = mesh.addVertex(p2, color, tex, glm::vec3(1, 0, 0));
	v5 = mesh.addVertex(p5, color, tex + right, glm::vec3(1, 0, 0));
	v8 = mesh.addVertex(p8, color, tex + up + right, glm::vec3(1, 0, 0));
	v3 = mesh.addVertex(p3, color, tex + up, glm::vec3(1, 0, 0));
	mesh.addTriangle(v2, v5, v8);
	mesh.addTriangle(v2, v8, v3);

	//Left
	v6 = mesh.addVertex(p6, color, tex, glm::vec3(-1, 0, 0));
	v1 = mesh.addVertex(p1, color, tex + right, glm::vec3(-1, 0, 0));
	v4 = mesh.addVertex(p4, color, tex + up + right, glm::vec3(-1, 0, 0));
	v7 = mesh.addVertex(p7, color, tex + up, glm::vec3(-1, 0, 0));
	mesh.addTriangle(v6, v1, v4);
	mesh.addTriangle(v6, v4, v7);

	//Top
	v4 = mesh.addVertex(p4, color, tex, glm::vec3(0, 1, 0));
	v3 = mesh.addVertex(p3, color, tex + right, glm::vec3(0, 1, 0));
	v8 = mesh.addVertex(p8, color, tex + up + right, glm::vec3(0, 1, 0));
	v7 = mesh.addVertex(p7, color, tex + up, glm::vec3(0, 1, 0));
	mesh.addTriangle(v4, v3, v8);
	mesh.addTriangle(v4, v8, v7);

	//Bottom
	v6 = mesh.addVertex(p6, color, tex, glm::vec3(0, -1, 0));
	v5 = mesh.addVertex(p5, color, tex + right, glm::vec3(0, -1, 0));
	v2 = mesh.addVertex(p2, color, tex + up + right, glm::vec3(0, -1, 0));
	v1 = mesh.addVertex(p1, color, tex + up, glm::vec3(0, -1, 0));
	mesh.addTriangle(v6, v5, v2);
	mesh.addTriangle(v6, v2, v1);

	return mesh;
}

Mesh
MeshHelper::cuboidMesh(glm::vec4 color, float lenX, float lenY, float lenZ, const bool calcTangent)
{
	Mesh mesh = Mesh::createObject(calcTangent);
	float x = 0.0f, y = 0.0f, z = 0.0f;
	glm::vec3 p1(x - lenX/2.0, y - lenY/2.0, z + lenZ/2.0);
	glm::vec3 p2(x + lenX/2.0, y - lenY/2.0, z + lenZ/2.0);
	glm::vec3 p3(x + lenX/2.0, y + lenY/2.0, z + lenZ/2.0);
	glm::vec3 p4(x - lenX/2.0, y + lenY/2.0, z + lenZ/2.0);
	glm::vec3 p5(x + lenX/2.0, y - lenY/2.0, z - lenZ/2.0);
	glm::vec3 p6(x - lenX/2.0, y - lenY/2.0, z - lenZ/2.0);
	glm::vec3 p7(x - lenX/2.0, y + lenY/2.0, z - lenZ/2.0);
	glm::vec3 p8(x + lenX/2.0, y + lenY/2.0, z - lenZ/2.0);

	unsigned int v1, v2, v3, v4, v5, v6, v7, v8;

	glm::vec2 tex = glm::vec2(0, 0);
	glm::vec2 right(1.0f, 0);
	glm::vec2 up(0, 1.0f);

	//Front
	v1 = mesh.addVertex(p1, color, tex, glm::vec3(0, 0, 1));
	v2 = mesh.addVertex(p2, color, tex + right, glm::vec3(0, 0, 1));
	v3 = mesh.addVertex(p3, color, tex + up + right, glm::vec3(0, 0, 1));
	v4 = mesh.addVertex(p4, color, tex + up, glm::vec3(0, 0, 1));
	mesh.addTriangle(v1, v2, v3);
	mesh.addTriangle(v1, v3, v4);

	//Back
	v5 = mesh.addVertex(p5, color, tex, glm::vec3(0, 0, -1));
	v6 = mesh.addVertex(p6, color, tex + right, glm::vec3(0, 0, -1));
	v7 = mesh.addVertex(p7, color, tex + up + right, glm::vec3(0, 0, -1));
	v8 = mesh.addVertex(p8, color, tex + up, glm::vec3(0, 0, -1));
	mesh.addTriangle(v5, v6, v7);
	mesh.addTriangle(v5, v7, v8);

	//Right
	v2 = mesh.addVertex(p2, color, tex, glm::vec3(1, 0, 0));
	v5 = mesh.addVertex(p5, color, tex + right, glm::vec3(1, 0, 0));
	v8 = mesh.addVertex(p8, color, tex + up + right, glm::vec3(1, 0, 0));
	v3 = mesh.addVertex(p3, color, tex + up, glm::vec3(1, 0, 0));
	mesh.addTriangle(v2, v5, v8);
	mesh.addTriangle(v2, v8, v3);

	//Left
	v6 = mesh.addVertex(p6, color, tex, glm::vec3(-1, 0, 0));
	v1 = mesh.addVertex(p1, color, tex + right, glm::vec3(-1, 0, 0));
	v4 = mesh.addVertex(p4, color, tex + up + right, glm::vec3(-1, 0, 0));
	v7 = mesh.addVertex(p7, color, tex + up, glm::vec3(-1, 0, 0));
	mesh.addTriangle(v6, v1, v4);
	mesh.addTriangle(v6, v4, v7);

	//Top
	v4 = mesh.addVertex(p4, color, tex, glm::vec3(0, 1, 0));
	v3 = mesh.addVertex(p3, color, tex + right, glm::vec3(0, 1, 0));
	v8 = mesh.addVertex(p8, color, tex + up + right, glm::vec3(0, 1, 0));
	v7 = mesh.addVertex(p7, color, tex + up, glm::vec3(0, 1, 0));
	mesh.addTriangle(v4, v3, v8);
	mesh.addTriangle(v4, v8, v7);

	//Bottom
	v6 = mesh.addVertex(p6, color, tex, glm::vec3(0, -1, 0));
	v5 = mesh.addVertex(p5, color, tex + right, glm::vec3(0, -1, 0));
	v2 = mesh.addVertex(p2, color, tex + up + right, glm::vec3(0, -1, 0));
	v1 = mesh.addVertex(p1, color, tex + up, glm::vec3(0, -1, 0));
	mesh.addTriangle(v6, v5, v2);
	mesh.addTriangle(v6, v2, v1);

	return mesh;
}

Mesh 
MeshHelper::quadMesh(float size, const bool calcTangent)
{
	const float halfSize = size / 2;
	Mesh quad = Mesh::createObject();

	unsigned int id1, id2, id3, id4;

	id1 = quad.addVertex(glm::vec3(-halfSize, -halfSize, 0), glm::vec4(1), glm::vec2(0), glm::vec3(0, 0, 1));
	id2 = quad.addVertex(glm::vec3(halfSize, -halfSize, 0), glm::vec4(1), glm::vec2(1, 0), glm::vec3(0, 0, 1));
	id3 = quad.addVertex(glm::vec3(halfSize, halfSize, 0), glm::vec4(1), glm::vec2(1, 1), glm::vec3(0, 0, 1));
	id4 = quad.addVertex(glm::vec3(-halfSize, halfSize, 0), glm::vec4(1), glm::vec2(0, 1), glm::vec3(0, 0, 1));

	quad.addTriangle(id1, id2, id3);
	quad.addTriangle(id1, id3, id4);

	return quad;
}