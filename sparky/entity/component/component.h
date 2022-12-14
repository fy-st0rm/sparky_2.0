#pragma once
#include "dependency.h"
#include "../../texture/texture.h"

namespace Sparky {
	class Entity;

	#define TRANSFORM_COMPONENT    "SparkyTransformComponent"
	#define RENDER_COMPONENT       "SparkyRenderComponent"
	#define BOX_COLLIDER_COMPONENT "SparkyBoxColliderComponent"
	#define ANIMATION_COMPONENT    "SparkyAnimationComponent"
	#define TAG_COMPONENT          "SparkyTagComponent"

	enum CompCount
	{
		__TRANSFORM__,
		__RENDER__,
		__BOX_COLLIDER__,
		__ANIMATION__,
		__TAG__,
		COMPONENT_AMT
	};

	class Component
	{
	public:
		std::string name;
	};


	/*
	 * Transform Component:
	 *   - Position of the object
	 *   - Size of the object
	 */

	class TransformComponent : public Component
	{
	public:
		std::string name = TRANSFORM_COMPONENT;

	public:
		TransformComponent() {}
		TransformComponent(glm::vec3 pos, glm::vec2 size, glm::mat4 rotation) 
			:pos(pos), size(size), rotation(rotation)
		{}
		~TransformComponent() {}
	
	public:
		void sync_with_rect(glm::vec4 rect)
		{
			this->pos.x = rect.x;
			this->pos.y = rect.y;
		}
	
	public:
		glm::vec3 get_pos()      const { return this->pos;      }
		glm::vec2 get_size()     const { return this->size;     }
		glm::mat4 get_rotation() const { return this->rotation; }

		void set_pos(glm::vec3 pos)           { this->pos = pos;           }
		void set_size(glm::vec2 size)         { this->size = size;         }
		void set_rotation(glm::mat4 rotation) { this->rotation = rotation; }

	private:
		glm::vec3 pos;
		glm::vec2 size;
		glm::mat4 rotation;
	};

	/*
	 * Render Component:
	 *    - Color of the object
	 *    - Texture of the object
	 *    - Texture coordinate of the object
	 */

	class RenderComponent : public Component
	{
	public:
		std::string name = RENDER_COMPONENT;

	public:
		RenderComponent() {}
		RenderComponent(glm::vec4 color, glm::vec4 tex_cord, std::shared_ptr<Texture> texture) 
			:color(color), tex_cord(tex_cord), texture(texture)
		{}
		~RenderComponent() {}
	
	public:
		glm::vec4 get_color()     const { return this->color; }
		void set_color(glm::vec4 color) { this->color = color; }

		glm::vec4 get_tex_cord()        const { return this->tex_cord; }
		void set_tex_cord(glm::vec4 tex_cord) { this->tex_cord = tex_cord; }

		Texture* get_texture() { return this->texture.get(); }
		void set_texture(std::shared_ptr<Texture> texture) { this->texture = texture; }
	
	private:
		glm::vec4 color;
		glm::vec4 tex_cord;
		std::shared_ptr<Texture> texture;
	};

	/*
	 * Box Collider Component:
	 *    - Box Rect of the object
	 */

	class BoxColliderComponent : public Component
	{
	public:
		std::string name = BOX_COLLIDER_COMPONENT;
		bool trigger = false;

	public:
		BoxColliderComponent() 
		{
			this->reset_hits();
		}
		BoxColliderComponent(glm::vec4 rect)
			:rect(rect)
		{
			this->reset_hits();
		}

		BoxColliderComponent(glm::vec4 rect, bool trigger)
			:rect(rect), trigger(trigger)
		{
			this->reset_hits();
		}
		~BoxColliderComponent() {}

	public:
		void reset_hits();
		void sync_with_transform(TransformComponent* comp);
		bool intersect(BoxColliderComponent* other, Entity* entity);
		void resolve_intersection(BoxColliderComponent* other);

	public:
		glm::vec4 get_rect()    const { return this->rect; }
		void set_rect(glm::vec4 rect) { this->rect = rect; }

		std::unordered_map<std::string, bool> get_hits()    const { return this->hits; }
		void set_hits(std::unordered_map<std::string, bool> hits) { this->hits = hits; }

		Entity* get_collided_entity()
		{
			if (this->collided_entity) return this->collided_entity;
			return nullptr;
		}

	private:
		glm::vec4 rect;
		std::unordered_map<std::string, bool> hits;
		Entity* collided_entity = nullptr;
	};
	

	/*
	 * Animation node:
	 *    - Node name
	 *    - Node data
	 *    - Children nodes
	 */
	class AnimationNode
	{
	public:
		AnimationNode() 
		{
			this->id = uuid::generate_uuid_v4();
		}

		AnimationNode(const std::string& name)
			:name(name)
		{
			this->id = uuid::generate_uuid_v4();
		}

		AnimationNode(const std::string& name, std::vector<glm::vec4> data, float speed)
			:name(name), data(data), speed(speed)
		{
			this->id = uuid::generate_uuid_v4();
		}

		~AnimationNode() {}

		void add_child(AnimationNode& node)
		{
			this->child.push_back(node);
		}

	public:
		std::string get_name() const { return this->name; }
		std::string get_id() const { return this->id; }
		std::vector<glm::vec4> get_data() const { return this->data; }
		std::vector<AnimationNode> get_child() const { return this->child; }
		float get_speed() const { return this->speed; }

	private:
		std::string id;
		std::string name;
		std::vector<glm::vec4> data;
		float speed = 0.0f;
		std::vector<AnimationNode> child;
	};

	class AnimationComponent : public Component
	{
	public:
		std::string name = ANIMATION_COMPONENT;

	public:
		AnimationComponent()  {}
		~AnimationComponent() {}

		void switch_state(std::vector<std::string>& states);
		glm::vec4 get_current_frame();

	public:
		void add_node(AnimationNode& node);
		void print_node(AnimationNode& node);
		void print_buffer();

	private:
		AnimationNode find_curr_node(AnimationNode& primary, std::vector<std::string>& state);

	private:
		float anime_idx = 0.0f;
		std::unordered_map<std::string, AnimationNode> state_register;
		AnimationNode curr_node;
	};


	class TagComponent : public Component
	{
	public:
		std::string name = TAG_COMPONENT;
		std::string tag = "ENTITY";

	public:
		TagComponent() {}
		TagComponent(const std::string& tag): tag(tag) {}
		~TagComponent() {}
	};
}

