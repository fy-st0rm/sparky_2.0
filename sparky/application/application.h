#pragma once
#include "dependency.h"
#include "../core/core.h"
#include "scene.h"
#include "../window/window.h"
#include "../gui/gui.h"

// TODO: Add opencv support for textures -lopencv_core "-lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lprotobuf -lopencv_videoio"
// TODO: Text rendering
// TODO: Simple UI library or utilize imgui

namespace Sparky {
	class Application
	{
	public:
		// Virtual functions
		virtual void on_start() {};
	
		// Entry point
		void run(const std::string& title, int width, int height, float fps, int flag);
		void destroy();
	
		// Function to add new scenes
		template<typename T>
		void add_scene(const std::string& name, void* arg_struct)
		{
			this->scenes.insert({name, std::make_shared<T>(arg_struct)});
		}
	
		void switch_scene(const std::string& name);
	
	public:
		// Overriddens
		inline void clear(glm::vec4 color) { this->window->clear(color); }
	
	public:
		// Getters
		inline int get_win_width()  const { return window->get_width();  }
		inline int get_win_height() const { return window->get_height(); }

		std::shared_ptr<Window> get_sparky_window() const { return this->window; }

		void set_mode(int mode) { this->mode = mode; }
	
	private:
		// Window
		std::shared_ptr<Window> window;
		SparkyEvent event;
	
	private:
		// Stores scenes
		std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
		std::string curr_scene;

		// Mode
		int mode = RELEASE_MODE;
	
		// Delta Time
		float fps;
		double dt;
	
	private:
		void app_loop();
		void app_event();
	};
}
