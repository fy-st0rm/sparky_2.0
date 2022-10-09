#include "sparky.h"

struct ArgStruct {
	Sparky::Application* app;
};

class Home : public Sparky::Scene
{
private:
	Sparky::Application* app;

	// Textures
	std::shared_ptr<Sparky::Texture> white;
	std::shared_ptr<Sparky::Texture> texture;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity Manager
	std::shared_ptr<Sparky::EntityManager> manager;

	float speed = 5;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		this->camera = std::make_shared<Sparky::OrthoCamera>(pos, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		this->white = std::make_shared<Sparky::Texture>();
		this->texture = std::make_shared<Sparky::Texture>("Us.png");

		this->renderer = std::make_shared<Sparky::QuadRenderer>(10, this->camera);

		this->manager = std::make_shared<Sparky::EntityManager>();

		// Creating entity
		Sparky::Entity* ent = this->manager->add_entity<Sparky::Entity>(this->manager);
		ent->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
		ent->add_component<Sparky::RenderComponent>(glm::vec4(1,1,0,1), glm::vec4(0,0,1,1), texture);
	};

	void on_update(double dt)
	{
		this->manager->update(this->renderer);
	}
};

class Test : public Sparky::Application
{
public:
	Test() {};

	void on_start()
	{
		ArgStruct arg = {this};
		add_scene<Home>("Home", &arg);
		switch_scene("Home");
	}
};

int main(int argc, char** argv)
{
	Test test;
	test.run("Sparky application", 800, 600, 60.0f, 0);
	return 0;
}
