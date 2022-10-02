#pragma once
#include "dependency.h"
#include "component/component.h"
#include "../renderer/quad_renderer/quad_renderer.h"

namespace Sparky {
	class Entity;

	class EntityManager
	{
	public:
		EntityManager()  {};
		~EntityManager() {};
	
	public:
		void push_entity(std::shared_ptr<Entity> entity);
		void remove_entity(std::shared_ptr<Entity> entity);

		template<typename T>
		void add_entity_to_comp(std::shared_ptr<Entity> entity)
		{
			if (typeid(T) == typeid(TransformComponent))
			{
				this->transform_entity.push_back(entity->get_id());
			}
			else if (typeid(T) == typeid(RenderComponent))
			{
				this->render_entity.push_back(entity->get_id());
			}
			SP_ASSERT(2 == COMPONENT_AMT);
		}

		template<typename T>
		void remove_entity_from_comp(std::shared_ptr<Entity> entity)
		{
			if (typeid(T) == typeid(TransformComponent))
			{
				this->transform_entity.erase(
					std::remove(this->transform_entity.begin(), this->transform_entity.end(), entity->get_id()), 
					this->transform_entity.end()
				);
			}
			else if (typeid(T) == typeid(RenderComponent))
			{
				this->render_entity.erase(
					std::remove(this->render_entity.begin(), this->render_entity.end(), entity->get_id()), 
					this->render_entity.end()
				);
			}
			SP_ASSERT(2 == COMPONENT_AMT);
		}
	
	public:
		void update(std::shared_ptr<QuadRenderer> renderer);
		void print_buffer();
	
	private:
		std::unordered_map<std::string, std::shared_ptr<Entity>> entity_buffer;
		std::vector<std::string> transform_entity;
		std::vector<std::string> render_entity;
	};
}
