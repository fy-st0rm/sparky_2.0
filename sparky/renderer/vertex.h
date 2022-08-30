#pragma once
#include "dependency.h"

enum VertexData
{
	X,
	Y,
	Z,
	R,
	G,
	B,
	A,
	VERTEX_SIZE
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 color;
};

struct Quad
{
	Vertex vertex[4];
};
