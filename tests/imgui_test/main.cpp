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
	Sparky::TransformComponent* tcomp1;
	Sparky::TransformComponent* tcomp2;

public:
	Main(void* arg_struct)
	{
		// Getting the sparky application from the argument
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing the camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1000.0f, 1000.0f);

		// Creating white texture
		this->white = std::make_shared<Sparky::Texture>();

		// Initializing the renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Initializing entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		// Entity
		Sparky::Entity* entity_1 = this->manager->add_entity<Sparky::Entity>(this->manager);
		this->tcomp1 = entity_1->add_component<Sparky::TransformComponent>(glm::vec3(200, 100, 0), glm::vec2(100, 100));
		entity_1->add_component<Sparky::RenderComponent>(glm::vec4(1,0,1,1), glm::vec4(0,0,1,1), this->white);

		Sparky::Entity* entity = this->manager->add_entity<Sparky::Entity>(this->manager);
		this->tcomp2 = entity->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
		entity->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->white);
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
		glm::vec3 pos1 = this->tcomp1->get_pos();
		glm::vec3 pos2 = this->tcomp2->get_pos();
		ImGui::Begin("Control");
		ImGui::SliderFloat3("Position 1:", &pos1.x, 0.0f, app->get_sparky_window()->get_width());
		ImGui::SliderFloat3("Position 2:", &pos2.x, 0.0f, app->get_sparky_window()->get_width());
		ImGui::End();
		this->tcomp1->set_pos(pos1);
		this->tcomp2->set_pos(pos2);
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
