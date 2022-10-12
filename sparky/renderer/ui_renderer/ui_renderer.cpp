#include "ui_renderer.h"

namespace Sparky {
	UIRenderer::UIRenderer(int max_quad_cnt, std::shared_ptr<OrthoCamera> camera)
		:camera(camera)
	{
		this->entity_manager = std::make_shared<EntityManager>();
		this->quad_renderer  = std::make_shared<QuadRenderer>(max_quad_cnt, camera);
	}

	UIRenderer::~UIRenderer()
	{
	}

	void UIRenderer::print_buffer()
	{
		std::cout << "UI Elements: " << this->elements.size() << " elements\n";
		for (auto& i : this->elements)
			std::cout << i.second->ui_entity->get_id() << std::endl;
	}

	UIElement* UIRenderer::get_focused_ui()
	{
		// Getting mouse position
		int new_x, new_y;
		glm::vec2 m_pos = Util::get_mouse_pos(this->camera);
		new_x = m_pos.x;
		new_y = m_pos.y;

		for (auto& i : this->elements)
		{
			TransformComponent* tcomp = i.second->ui_entity->get_component<TransformComponent>();
			glm::vec3 pos  = tcomp->get_pos();
			glm::vec2 size = tcomp->get_size();

			// Checking for intersection
			if (pos.x < new_x && new_x < pos.x + size.x)
				if (pos.y < new_y && new_y < pos.y + size.y)
					return i.second.get();
		}
		return nullptr;
	}

	void UIRenderer::update()
	{
		// Handling updating
		for (auto& i : this->elements)
			i.second->on_update();

		// Handle hover
		this->focused_ui = this->get_focused_ui();
		if (this->focused_ui != nullptr)
			this->focused_ui->on_hover();

		// Handle rendering
		this->entity_manager->update(this->quad_renderer);
	}

	void UIRenderer::handle_event(SparkyEvent& event)
	{
		// Handle click
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (event.button.button)
			{
				case SDL_BUTTON_LEFT:
					if (this->focused_ui)
						this->focused_ui->on_left_click();
					break;
				case SDL_BUTTON_RIGHT:
					if (this->focused_ui)
						this->focused_ui->on_right_click();
					break;
			}
		}
	}
}
