#include "application.h"

void Application::run(const std::string& title, int width, int height, float fps)
{
	this->fps = fps;
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

	if (this->curr_scene != "")
		this->scenes[this->curr_scene]->on_exit();
	this->curr_scene = name;
	this->scenes[this->curr_scene]->on_entry();
}

void Application::app_event()
{
	while (SDL_PollEvent(&this->event))
	{
		if (this->event.type == SDL_QUIT) this->destroy();

		// Passing event to the current scene
		this->scenes[this->curr_scene]->on_event(this->event);
	}
}

void Application::app_loop()
{
	float req_frame = 1000.0f / this->fps;
	while (!this->window->is_closed())
	{
		this->clear({0.0f, 0.0f, 0.0f, 1.0f});
		auto start_t = std::chrono::high_resolution_clock::now();

		// Calling application event loop
		this->app_event();

		// Updating current scene
		this->scenes[this->curr_scene]->on_update(this->dt);

		// Calculating delta time
		auto end_t = std::chrono::high_resolution_clock::now();
		this->dt = std::chrono::duration<double, std::milli>(end_t - start_t).count();

		// Capping frame rate
		if (req_frame > this->dt)
			SDL_Delay(req_frame - this->dt);

		// Updating window
		this->window->update();
	}
}

