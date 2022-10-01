#include "entity_manager.h"
#include "entity.h"

namespace Sparky {
	void EntityManager::push_entity(Entity* entity)
	{
		this->entity_buffer[entity->get_id()] = entity;
	}

	void EntityManager::remove_entity(Entity* entity)
	{
		this->entity_buffer.erase(entity->get_id());
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
