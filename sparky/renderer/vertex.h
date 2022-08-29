#pragma once
#include "dependency.h"

#define VERTEX_CNT 3

struct Vertex
{
	glm::vec3 pos;
};

struct Quad
{
	Vertex vertex[4];
};
