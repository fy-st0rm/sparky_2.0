#pragma once
#include "dependency.h"

namespace Sparky {
	enum VertexData
	{
		X,
		Y,
		Z,
		R,
		G,
		B,
		A,
		TEX_X,
		TEX_Y,
		TEX_ID,
		VERTEX_SIZE
	};
	
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 tex_cord;
		float tex_id;
	};
	
	struct Quad
	{
		Vertex vertex[4];
	};
}
