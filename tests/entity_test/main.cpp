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

	// White texture
	std::shared_ptr<Sparky::Texture> white;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity manager
	std::shared_ptr<Sparky::EntityManager> manager;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Creating white texture
		this->white = std::make_shared<Sparky::Texture>();

		// Creating renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Initializing entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		// Entity
		Sparky::Entity* entity = this->manager->add_entity<Sparky::Entity>(this->manager);
		entity->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
		entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->white);
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});
		this->manager->update(this->renderer);
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
