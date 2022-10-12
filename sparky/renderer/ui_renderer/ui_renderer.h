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
		void add_ui_element(Args&&... args)
		{
			std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(args)...);
			this->elements.push_back(element);
		}

		void update();
		void handle_event(SparkyEvent& event);
		void print_buffer();

	public:
		std::shared_ptr<EntityManager> get_entity_manager() const { return this->entity_manager; }

	private:
		UIElement* get_focused_ui();

	private:
		std::shared_ptr<OrthoCamera> camera;
		std::shared_ptr<EntityManager> entity_manager;
		std::shared_ptr<QuadRenderer> quad_renderer;
		std::vector<std::shared_ptr<UIElement>> elements;
		UIElement* focused_ui = nullptr;
	};
}
