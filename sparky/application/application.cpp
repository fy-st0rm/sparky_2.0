#include "application.h"

void Application::run(const std::string& title, int width, int height)
{
	this->window = std::make_shared<Window>(title, width, height);

	// Calling application startup
	on_start();

	// Checking if scene has been initialize or not
	if (this->curr_scene == "")
		Log::error("Current scene hasn`t been initialized.", SPARKY_SCENE_EMPTY);

	// Calling application main loop
	this->app_loop();
}

void Application::destroy()
{
	this->window->destroy();
}

void Application::switch_scene(const std::string& name)
{
	if (this->scenes.find(name) == this->scenes.end())
		Log::error("Scene with name `" + name + "` doesn`t exists.", SPARKY_NULL);

	this->curr_scene = name;
	this->scenes[this->curr_scene]->on_start();
}

void Application::app_event()
{
	while (SDL_PollEvent(&this->event))
	{
		if (this->event.type == SDL_QUIT) this->destroy();
	}
}

void Application::app_loop()
{
	while (!this->window->is_closed())
	{
		// Calling application event loop
		this->app_event();
		this->scenes[this->curr_scene]->on_update();
	}
}

