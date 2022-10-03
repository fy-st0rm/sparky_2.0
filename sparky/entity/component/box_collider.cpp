#include "component.h"


namespace Sparky {
	void BoxColliderComponent::reset_hits()
	{
		this->hits["left"] = false;
		this->hits["right"] = false;
		this->hits["up"] = false;
		this->hits["down"] = false;
	}

	bool BoxColliderComponent::sync_with_transform(TransformComponent* comp)
	{
		glm::vec3 pos  = comp->get_pos();
		glm::vec2 size = comp->get_size();
		this->set_rect(glm::vec4(pos.x, pos.y, size.x, size.y));
	}

	bool BoxColliderComponent::intersect(BoxColliderComponent* other)
	{
		glm::vec4 rect_b = other->get_rect();
	
		if(this->rect.x < rect_b.x + rect_b.z && this->rect.x + this->rect.z > rect_b.x && 
			this->rect.y < rect_b.y + rect_b.w && this->rect.y + this->rect.w > rect_b.y)
			return true;
		return false;
	}

	void BoxColliderComponent::resolve_intersection(BoxColliderComponent* other)
	{
		// Resolve intersection only for dynamic objects
		if (this->mode == STATIC_COLLIDER) return;

		glm::vec4 rect_b = other->get_rect();

		// Getting left, right, up and down intersections
		float l, r, u, d;
		l = (rect_b.x + rect_b.z) - this->rect.x;
		r = (this->rect.x + this->rect.z) - rect_b.x;
		u = (this->rect.y + this->rect.w) - rect_b.y;
		d = (rect_b.y + rect_b.w) - this->rect.y;
		
		// Setting hits
		this->hits["left"] = l < r && l < u && l < d;
		this->hits["right"] = r < l && r < u && r < d;
		this->hits["up"] = u < l && u < r && u < d;
		this->hits["down"] = d < l && d < r && d < u;

		// Collision resolution
		if (this->hits["left"])
		{
			this->rect.x = rect_b.x + rect_b.z;
		}
		else if (this->hits["right"])
		{
			this->rect.x = rect_b.x - this->rect.z;
		}
		else if (this->hits["up"])
		{
			this->rect.y = rect_b.y - this->rect.w;
		}
		else if (this->hits["down"])
		{
			this->rect.y = rect_b.y + rect_b.w;
		}
	}
}
