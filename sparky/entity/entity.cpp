#include "entity.h"

namespace Sparky {
	Entity::Entity(std::shared_ptr<EntityManager> manager)
		:manager(manager)
	{
		this->id = uuid::generate_uuid_v4();
		this->self = std::shared_ptr<Entity>(this, [](Entity*){}); // Lamba function is to prevent shared_ptr to delete the pointer
		this->manager->push_entity(this->self);
	}

	Entity::~Entity()
	{
		this->destroy();
	}

	void Entity::destroy()
	{
		for (auto i : this->components)
		{
			this->components.erase(i.first);

			if (i.first == TRANSFORM_COMPONENT)
				this->manager->remove_entity_from_comp<TransformComponent>(this->self);
			if (i.first == RENDER_COMPONENT)
				this->manager->remove_entity_from_comp<RenderComponent>(this->self);
			SP_ASSERT(2 == COMPONENT_AMT);

			this->manager->remove_entity(this->self);
		}
	}

	void Entity::print_components()
	{
		std::cout << "Components of entity ( " << this->id << " ):\n";
		for (auto i : this->components)
		{
			std::cout << i.first << std::endl;
		}
	}
}
