#include "entity_manager.h"
#include "entity.h"

namespace Sparky {
	void EntityManager::remove_entity(std::shared_ptr<Entity> entity)
	{
		this->entity_buffer.erase(entity->get_id());
	}

	void EntityManager::remove_entity_by_id(const std::string& id)
	{
		if (this->entity_buffer.find(id) == this->entity_buffer.end())
			Log::error("Entity with id `" + id + "` cannot be found.", SPARKY_NULL);
		this->entity_buffer[id].reset();
	}

	void EntityManager::clear_buffer()
	{
		for (auto i: this->entity_buffer)
			i.second.reset();
		this->transform_entity.clear();
		this->render_entity.clear();
		this->box_collider_entity.clear();
		this->animation_entity.clear();
	}

	void EntityManager::update(std::shared_ptr<QuadRenderer> renderer)
	{
		this->update_collision(renderer);
		this->update_render(renderer);
	}

	void EntityManager::update_render(std::shared_ptr<QuadRenderer> renderer)
	{
		// Rendering entities
		renderer->render_begin();
		for (auto& i: this->render_entity)
		{
			std::shared_ptr<Entity> entity = this->entity_buffer[i];
			if (!entity->has_component<TransformComponent>())
			{
				// TODO: Add usage here
				Log::error("Entity having `RenderComponent` should also have `TransformComponent`.", SPARKY_NULL);
			}

			TransformComponent* tcomp = entity->get_component<TransformComponent>();
			RenderComponent* rcomp = entity->get_component<RenderComponent>();

			// Creating the quad
			glm::vec4 tex_cord = rcomp->get_tex_cord();
			if (entity->has_component<AnimationComponent>())
			{
				AnimationComponent* acomp = entity->get_component<AnimationComponent>();
				tex_cord = acomp->get_current_frame();
			}

			Quad quad = renderer->create_quad(tcomp->get_pos(), tcomp->get_size(), tcomp->get_rotation(), rcomp->get_color(), tex_cord, rcomp->get_texture());
			renderer->push_quad(quad);
		}
		renderer->render_end();
	}

	void EntityManager::update_collision(std::shared_ptr<QuadRenderer> renderer)
	{
		// Updating box colliders
		for (auto& i: this->box_collider_entity)
		{
			for (auto& j: this->box_collider_entity)
			{
				if (i == j) continue;

				// Getting the targets `a` and `b`
				std::shared_ptr<Entity> a = this->entity_buffer[i];
				std::shared_ptr<Entity> b = this->entity_buffer[j];

				if (!a->has_component<TransformComponent>() || !b->has_component<TransformComponent>())
				{
					// TODO: Add usage here
					Log::error("Entity having `RenderComponent` should also have `TransformComponent`.", SPARKY_NULL);
				}

				// Getting transform component of both
				TransformComponent* a_trans = a->get_component<TransformComponent>();
				TransformComponent* b_trans = b->get_component<TransformComponent>();

				// Getting box colliders of both
				BoxColliderComponent* a_comp = a->get_component<BoxColliderComponent>();
				BoxColliderComponent* b_comp = b->get_component<BoxColliderComponent>();

				// Syncing box collider with transform component
				a_comp->sync_with_transform(a_trans);
				b_comp->sync_with_transform(b_trans);

				// Getting rects
				glm::vec4 rect_a = a_comp->get_rect();
				glm::vec4 rect_b = b_comp->get_rect();

				// Reseting the hit results of target `a`
				a_comp->reset_hits();
				std::unordered_map<std::string, bool> hits = a_comp->get_hits();

				// Resolvuing the intersection
				if (a_comp->intersect(b_comp))
				{
					a_comp->resolve_intersection(b_comp);
				}

				// Syncing transform with box collider
				a_trans->sync_with_rect(a_comp->get_rect());
				b_trans->sync_with_rect(b_comp->get_rect());
			}
		}
	}

	void EntityManager::print_buffer()
	{
		std::cout << "\nTransform entites: " << this->transform_entity.size() << " entities\n";
		for (auto& i: this->transform_entity)
			std::cout << i << std::endl;
		std::cout << "\nRender entities: " << this->render_entity.size() << " entites\n";
		for (auto& i: this->render_entity)
			std::cout << i << std::endl;
		std::cout << "\nBoxCollider entities: " << this->box_collider_entity.size() << " entites\n";
		for (auto& i: this->box_collider_entity)
			std::cout << i << std::endl;
		std::cout << "\nAnimation entities: " << this->animation_entity.size() << " entites\n";
		for (auto& i: this->animation_entity)
			std::cout << i << std::endl;
	
		std::cout << "\nMain entity buffers: " << this->entity_buffer.size() << " total entities\n";
		for (auto i: this->entity_buffer)
			std::cout << i.first << std::endl;
	}
}
