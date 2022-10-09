#pragma once
#include "../../entity/entity.h"

namespace Sparky {
	class UIElement
	{
	public:
		std::shared_ptr<Entity> ui_entity;
	public:
		virtual void on_update() {};
		virtual void on_hover()  {};
		virtual void on_left_click()  {};
		virtual void on_right_click() {};
	};
}