#include "sparky.h"

struct ArgStruct
{
	Sparky::Application* app;
};

class Button : public Sparky::UIElement
{
public:
	glm::vec3 pos;
	glm::vec2 size;
	std::shared_ptr<Sparky::Texture> white;

public:
	Button(std::shared_ptr<Sparky::UIRenderer> ui_renderer, glm::vec3 pos, glm::vec2 size)
		:pos(pos), size(size)
	{
		this->white = std::make_shared<Sparky::Texture>();
		std::shared_ptr<Sparky::EntityManager> manager = ui_renderer->get_entity_manager();

		this->ui_entity = manager->add_entity<Sparky::Entity>(manager);
		this->ui_entity->add_component<Sparky::TransformComponent>(pos, size, glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1,0,0)));
		this->ui_entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->white);
	}

	void on_hover()
	{
		Sparky::RenderComponent* rcomp = this->ui_entity->get_component<Sparky::RenderComponent>();
		glm::vec4 color = {0.5, 0.5, 0.5, 1};
		rcomp->set_color(color);
	}

	void on_update()
	{
		Sparky::RenderComponent* rcomp = this->ui_entity->get_component<Sparky::RenderComponent>();
		glm::vec4 color = {1, 1, 1, 1};
		rcomp->set_color(color);
	}

	void on_left_click()
	{
		Sparky::Log::sucess("Left click", Sparky::SPARKY_NULL);
	}

	void on_right_click()
	{
		Sparky::Log::sucess("Right click", Sparky::SPARKY_NULL);
	}
};

class Main : public Sparky::Scene
{
private:
	Sparky::Application* app;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;

	// UI Renderer
	std::shared_ptr<Sparky::UIRenderer> ui_renderer;

public:
	Main(Sparky::Application* app)
		:app(app)
	{

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Initializing ui renderer
		this->ui_renderer = std::make_shared<Sparky::UIRenderer>(10, camera);

		// Creating a button
		this->ui_renderer->add_ui_element<Button>(this->ui_renderer, glm::vec3(100, 100, 0), glm::vec2(300, 50));
	};
	~Main() {};

public:
	void on_event(SparkyEvent event)
	{
		this->ui_renderer->handle_event(event);
	}

	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});
		this->ui_renderer->update();
	}
};

class App : public Sparky::Application
{
public:
	App()  {}
	~App() {}

public:
	void on_start()
	{
		ArgStruct app = {this};
		add_scene<Main>("Main", this);
		switch_scene("Main");
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Renderer test", 800, 600, 60, 0);
	return 0;
}
