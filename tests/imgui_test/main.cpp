#include "sparky.h"

struct ArgStruct
{
	Sparky::Application* app;
};

class Main : public Sparky::Scene
{
private:
	// Sparky application
	Sparky::Application* app;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;

	// White texture
	std::shared_ptr<Sparky::Texture> white;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity manager
	std::shared_ptr<Sparky::EntityManager> manager;

	// Entity
	Sparky::TransformComponent* tcomp;

public:
	Main(void* arg_struct)
	{
		// Getting the sparky application from the argument
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing the camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Creating white texture
		this->white = std::make_shared<Sparky::Texture>();

		// Initializing the renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Initializing entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		// Entity
		Sparky::Entity* entity = this->manager->add_entity<Sparky::Entity>(this->manager);
		entity->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
		entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->white);
		this->tcomp = entity->get_component<Sparky::TransformComponent>();
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});
		this->manager->update(this->renderer);
	}

	void on_imgui_render()
	{
		glm::vec3 pos = this->tcomp->get_pos();
		ImGui::Begin("Control");
		ImGui::SliderFloat3("Position", &pos.x, 0.0f, app->get_sparky_window()->get_width());
		ImGui::End();
		this->tcomp->set_pos(pos);
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
		// Making debug mode to enable imgui rendering
		set_mode(Sparky::DEBUG_MODE);

		ArgStruct app = {this};

		// Pushing the scene
		add_scene<Main>("Main", &app);

		// Changing the scene
		switch_scene("Main");
	}
};

int main(int argc, char** argv)
{
	App app;
	app.run("Renderer test", 800, 600, 60, 0);
	return 0;
}
