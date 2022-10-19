#include "entity.h"

namespace Sparky {
	Entity::Entity(std::shared_ptr<EntityManager> manager)
		:manager(manager)
	{
		this->id = uuid::generate_uuid_v4();
		this->self = std::shared_ptr<Entity>(this, [](Entity*){}); // Lamba function is to prevent shared_ptr to delete the pointer
	}

	Entity::~Entity()
	{
		this->destroy();
	}

	void Entity::destroy()
	{
		for (auto i : this->components)
		{
			if (i.first == TRANSFORM_COMPONENT)
				this->manager->remove_entity_from_comp<TransformComponent>(this->self);
			else if (i.first == RENDER_COMPONENT)
				this->manager->remove_entity_from_comp<RenderComponent>(this->self);
			else if (i.first == BOX_COLLIDER_COMPONENT)
				this->manager->remove_entity_from_comp<BoxColliderComponent>(this->self);
			else if (i.first == ANIMATION_COMPONENT)
				this->manager->remove_entity_from_comp<AnimationComponent>(this->self);
			assert((5 == COMPONENT_AMT) && "New component needs to be handled here.");
		}

		this->components.clear();
		this->manager->remove_entity(this->self);
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
