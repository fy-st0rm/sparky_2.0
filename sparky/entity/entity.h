#pragma once
#include "dependency.h"
#include "component/component.h"
#include "../core/core.h"
#include "../texture/texture.h"
#include "entity_manager.h"

namespace Sparky {
	class Entity
	{
	public:
		Entity(std::shared_ptr<EntityManager> manager);
		~Entity();
		void destroy();

	public:
		template<typename T, typename... Args>
		T* add_component(Args&&... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
			this->components[component->name] = component;

			// Assigning the entity to its component in the entity manager
			this->manager->add_entity_to_comp<T>(this->self); 
			return component.get();
		}

		template<typename T>
		bool has_component()
		{
			T comp;
			if (this->components.find(comp.name) != this->components.end())
				return true;
			return false;
		}

		template <typename T>
		T* get_component()
		{
			T comp;
			if (has_component<T>())
				return (T*) this->components[comp.name].get();
			Log::error("Component " + comp.name + " doesn`t exists in the entity (" + this->id + ")", SPARKY_NULL);
		}

		template <typename T>
		void remove_component()
		{
			T comp;
			if (has_component<T>())
			{
				this->components.erase(comp.name);

				// Removing the entity from the component list in entity manager
				this->manager->remove_entity_from_comp<T>(this->self);
			}
			else
			{
				Log::error("Component " + comp.name + " doesn`t exists in the entity (" + this->id + ")", SPARKY_NULL);
			}
		}

	public:
		std::string get_id() const { return id; }
		void print_components();

	private:
		std::string id;
		std::shared_ptr<Entity> self;
		std::shared_ptr<EntityManager> manager;
		std::unordered_map<std::string, std::shared_ptr<Component>> components;
	};
}
