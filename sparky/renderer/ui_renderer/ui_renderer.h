#pragma once
#include "dependency.h"
#include "../../core/core.h"
#include "../../core/util.h"
#include "../quad_renderer/quad_renderer.h"
#include "../../entity/entity.h"
#include "ui_element.h"

namespace Sparky {
	class UIRenderer
	{
	public:
		UIRenderer(int max_quad_cnt, std::shared_ptr<OrthoCamera> camera);
		~UIRenderer();

	public:
		template<typename T, typename... Args>
		T* add_ui_element(Args&&... args)
		{
			std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(args)...);
			this->elements[element->name] = element;
			return element.get();
		}

		UIElement* get_ui_element(const std::string& name)
		{
			if (this->elements.find(name) == this->elements.end())
				Log::error("UI element with name`" + name + "` doesnt exsits.", SPARKY_NULL);
			return this->elements[name].get();
		}

		void remove_ui_element(const std::string& name)
		{
			if (this->elements.find(name) == this->elements.end())
				Log::error("UI element with name `" + name + "` cannot be found.", SPARKY_NULL);

			// Removing from entity manager and ui registry
			std::shared_ptr<UIElement> element = this->elements[name];
			this->entity_manager->remove_entity_by_id(element->ui_entity->get_id());
			this->elements.erase(name);
		}

		void update();
		void handle_event(SparkyEvent& event);
		void clear_buffer()
		{
			this->entity_manager->clear_buffer();
			this->elements.clear();
		}
		void print_buffer();

	public:
		std::shared_ptr<OrthoCamera> get_camera() const { return this->camera; }
		std::shared_ptr<EntityManager> get_entity_manager()    const { return this->entity_manager; }
		std::shared_ptr<QuadRenderer> get_quad_renderer() const { return this->quad_renderer; }
		std::unordered_map<std::string, std::shared_ptr<UIElement>> get_elements() const { return this->elements; }
		UIElement* get_focused_ui();

	private:
		std::shared_ptr<OrthoCamera> camera;
		std::shared_ptr<EntityManager> entity_manager;
		std::shared_ptr<QuadRenderer> quad_renderer;
		std::unordered_map<std::string, std::shared_ptr<UIElement>> elements;
		UIElement* focused_ui = nullptr;
	};
}
