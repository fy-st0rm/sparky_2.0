#pragma once
#include "dependency.h"
#include "../../texture/texture.h"

namespace Sparky {
	#define TRANSFORM_COMPONENT    "SparkyTransformComponent"
	#define RENDER_COMPONENT       "SparkyRenderComponent"
	#define BOX_COLLIDER_COMPONENT "SparkyBoxColliderComponent"

	enum CompCount
	{
		__TRANSFORM__,
		__RENDER__,
		__BOX_COLLIDER__,
		COMPONENT_AMT
	};

	enum BoxColliderModes
	{
		STATIC_COLLIDER,
		DYNAMIC_COLLIDER
	};

	class Component
	{
	public:
		std::string name;
	};

	class TransformComponent : public Component
	{
	public:
		std::string name = TRANSFORM_COMPONENT;

	public:
		TransformComponent() {}
		TransformComponent(glm::vec3 pos, glm::vec2 size) 
			:pos(pos), size(size)
		{}
		~TransformComponent() {}
	
	public:
		void sync_with_rect(glm::vec4 rect)
		{
			this->pos.x = rect.x;
			this->pos.y = rect.y;
		}
	
	public:
		glm::vec3 get_pos()  const { return this->pos; }
		glm::vec2 get_size() const { return this->size; }

		void set_pos(glm::vec3 pos)   { this->pos = pos; }
		void set_size(glm::vec2 size) { this->size = size; }

	private:
		glm::vec3 pos;
		glm::vec2 size;
	};

	class RenderComponent : public Component
	{
	public:
		std::string name = RENDER_COMPONENT;

	public:
		RenderComponent() {}
		RenderComponent(glm::vec4 color, glm::vec4 tex_cord, Texture* texture) 
			:color(color), tex_cord(tex_cord), texture(texture)
		{}
		~RenderComponent() {}
	
	public:
		glm::vec4 get_color()     const { return this->color; }
		void set_color(glm::vec4 color) { this->color = color; }

		glm::vec4 get_tex_cord()        const { return this->tex_cord; }
		void set_tex_cord(glm::vec4 tex_cord) { this->tex_cord = tex_cord; }

		Texture*  get_texture()      const { return this->texture; }
		void set_texture(Texture* texture) { this->texture = texture; }
	
	private:
		glm::vec4 color;
		glm::vec4 tex_cord;
		Texture* texture;
	};

	class BoxColliderComponent : public Component
	{
	public:
		BoxColliderComponent() 
		{
			this->reset_hits();
		}
		BoxColliderComponent(glm::vec4 rect, int mode)
			:rect(rect), mode(mode)
		{
			this->reset_hits();
		}
		~BoxColliderComponent() {}

	public:
		void reset_hits();
		bool sync_with_transform(TransformComponent* comp);
		bool intersect(BoxColliderComponent* other);
		void resolve_intersection(BoxColliderComponent* other);

	public:
		glm::vec4 get_rect()    const { return this->rect; }
		void set_rect(glm::vec4 rect) { this->rect = rect; }

		std::unordered_map<std::string, bool> get_hits()    const { return this->hits; }
		void set_hits(std::unordered_map<std::string, bool> hits) { this->hits = hits; }

		int get_mode()    const { return this->mode; }
		void set_mode(int mode) { this->mode = mode; }

	private:
		glm::vec4 rect;
		int mode;
		std::unordered_map<std::string, bool> hits;
	};
}

