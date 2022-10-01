#include "sparky.h"

struct ArgStruct
{
	Sparky::Application* app;
};

class Main : public Sparky::Scene
{
private:
	Sparky::Application* app;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;
	Sparky::Texture white;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity manager
	std::shared_ptr<Sparky::EntityManager> entity_manager;

	// Entity
	std::shared_ptr<Sparky::Entity> entity;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Creating renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Creating entity manager
		this->entity_manager = std::make_shared<Sparky::EntityManager>();

		// Creating entity
		this->entity = std::make_shared<Sparky::Entity>(this->entity_manager);
		this->entity->add_component<Sparky::TransformComponent>(glm::vec3(100,100,0), glm::vec2(100, 100));
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});

		{
			Sparky::Quad quad = this->renderer->create_quad(glm::vec3(300.0f, 100.0f, 0.0f), glm::vec2(250, 250), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &this->white);

			this->renderer->render_begin();
			this->renderer->push_quad(quad);
			this->renderer->render_end();
		}
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
		add_scene<Main>("Main", &app);
		switch_scene("Main");
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Renderer test", 800, 600, 60, 0);
	return 0;
}
