#pragma once
#include "dependency.h"
#include "shader/shader.h"

namespace Sparky {
	class OrthoCamera
	{
	public:
		OrthoCamera(glm::vec3 pos, float left, float right, float bottom, float top, float near, float far);
		~OrthoCamera();
	
	public:
		void update(Shader* shader);

	public:
		// Getters and setters
		glm::mat4 get_mvp() const { return this->mvp; }
		glm::vec3 get_position() const { return this->pos; }
		float get_rotation() const { return this->rotation; }

		void set_projection(float left, float right, float bottom, float top, float near, float far);
		void set_position(glm::vec3 pos)
		{
			this->pos = pos; 
			this->calculate_matrix();
		}
		void set_rotation(float rotation)
		{
			this->rotation = rotation;
			this->calculate_matrix();
		}

	private:
		void calculate_matrix();
	
	private:
		float rotation = 0.0f;
		glm::vec3 pos;
		glm::mat4 proj_mat;
		glm::mat4 view_mat;
		glm::mat4 mvp;
	};
}
