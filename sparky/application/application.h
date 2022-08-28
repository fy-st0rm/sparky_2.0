#pragma once
#include "dependency.h"
#include "../core/core.h"
#include "scene.h"
#include "../window/window.h"

//TODO: [ ] Buffers
//TODO: [ ] Shaders
//TODO: [ ] Renderers
//TODO: [ ] Cameras


class Application
{
public:
	// Virtual functions
	virtual void on_start() {};

	// Entry point
	void run(const std::string& title, int width, int height, float fps);
	void destroy();

	// Function to add new scenes
	template<typename T>
	void add_scene(const std::string& name, void* arg_struct)
	{
		this->scenes.insert({name, std::make_shared<T>(arg_struct)});
	}

	void switch_scene(const std::string& name);

public:
	// Getters
	inline int get_win_width()  const { return window->get_width();  }
	inline int get_win_height() const { return window->get_height(); }

private:
	// Window
	std::shared_ptr<Window> window;
	SparkyEvent event;

private:
	// Stores scenes
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
	std::string curr_scene;

	// Delta Time
	float fps;
	double dt;

private:
	void app_loop();
	void app_event();
};
