#pragma once
#include "dependency.h"
#include "../core/core.h"

namespace Sparky {
	class Scene
	{
	public:
		// Virtual functions
		virtual void on_entry() {};
		virtual void on_update(double dt) {};
		virtual void on_imgui_render() {};
		virtual void on_event(SparkyEvent event) {};
		virtual void on_exit() {};
	};
}
