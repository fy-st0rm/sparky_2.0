#pragma once
#include "dependency.h"
#include "../window/window.h"

namespace Sparky {
	class Gui
	{
	public:
		static void init(std::shared_ptr<Window> window);
		static void shutdown();
	
		static void begin_frame();
		static void end_frame();
	};
}
