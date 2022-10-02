#pragma once
#include "dependency.h"
#include "../../texture/texture.h"

namespace Sparky {
	#define TRANSFORM_COMPONENT "SparkyTransformComponent"
	#define RENDER_COMPONENT    "SparkyRenderComponent"

	enum CompCount
	{
		__TRANSFORM__,
		__RENDER__,
		COMPONENT_AMT
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
		RenderComponent(glm::vec4 color, Texture* texture) 
			:color(color), texture(texture)
		{}
		~RenderComponent() {}
	
	public:
		glm::vec4 get_color() const   { return this->color; }
		Texture*  get_texture() const { return this->texture; }
	
	private:
		glm::vec4 color;
		Texture* texture;
	};
}

