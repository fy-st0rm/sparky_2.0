#include "ortho_cam.h"

namespace Sparky {
	OrthoCamera::OrthoCamera(glm::vec3& pos, float left, float right, float bottom, float top, float near, float far)
		:pos(pos)
	{
		this->set_projection(left, right, bottom, top, near, far);
		this->calculate_matrix();
	}

	OrthoCamera::~OrthoCamera()
	{
	}

	void OrthoCamera::set_projection(float left, float right, float bottom, float top, float near, float far)
	{
		this->proj_mat = glm::ortho(left, right, bottom, top, near, far);
	}

	void OrthoCamera::calculate_matrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->pos) * glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0, 0, 1));
		this->view_mat = glm::inverse(transform);
		this->mvp = this->proj_mat * this->view_mat;
	}

	void OrthoCamera::update(Shader* shader)
	{
		int loc = shader->get_uniform_location("mvp");
		GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &this->mvp[0][0]));
	}
}
