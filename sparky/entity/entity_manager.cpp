#include "entity_manager.h"
#include "entity.h"

namespace Sparky {
	void EntityManager::push_entity(std::shared_ptr<Entity> entity)
	{
		this->entity_buffer[entity->get_id()] = entity;
	}

	void EntityManager::remove_entity(std::shared_ptr<Entity> entity)
	{
		this->entity_buffer.erase(entity->get_id());
	}

	void EntityManager::update(std::shared_ptr<QuadRenderer> renderer)
	{
		// Rendering entities
		renderer->render_begin();
		for (auto& i: this->render_entity)
		{
			std::shared_ptr<Entity> entity = this->entity_buffer[i];
			if (!entity->has_component<TransformComponent>())
				// TODO: Add usage here
				Log::error("Entity having `RenderComponent` should also have `TransformComponent`.", SPARKY_NULL);

			TransformComponent* tcomp = entity->get_component<TransformComponent>();
			RenderComponent* rcomp = entity->get_component<RenderComponent>();

			// Creating the quad
			// TODO: Change texture cord according to animation component
			Quad quad = renderer->create_quad(tcomp->get_pos(), tcomp->get_size(), rcomp->get_color(), rcomp->get_tex_cord(), rcomp->get_texture());
			renderer->push_quad(quad);
		}
		renderer->render_end();
	}

	void EntityManager::print_buffer()
	{
		std::cout << "\nTransform entites: \n";
		for (auto& i: this->transform_entity)
			std::cout << i << std::endl;
		std::cout << "\nRender entities: \n";
		for (auto& i: this->render_entity)
			std::cout << i << std::endl;
		std::cout << "\nMain entity buffers: \n";
		for (auto i: entity_buffer)
			std::cout << i.first << std::endl;
	}
}
