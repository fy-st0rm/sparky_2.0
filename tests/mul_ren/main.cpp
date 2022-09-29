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
	std::shared_ptr<Sparky::Texture> texture;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer1;
	std::shared_ptr<Sparky::QuadRenderer> renderer2;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing camera
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		this->camera = std::make_shared<Sparky::OrthoCamera>(pos, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		this->texture = std::make_shared<Sparky::Texture>("Us.png");

		// Initializing renderers
		this->renderer1 = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);
		this->renderer2 = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);
		this->renderer2->switch_shader_from_file("vert.vs", "frag.fs");

		std::cout << "Main scene constructed.\n";
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});

		{
			Sparky::Quad quad = this->renderer1->create_quad(glm::vec3(300.0f, 100.0f, 0.0f), glm::vec2(250, 250), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), this->texture.get());

			this->renderer1->render_begin();
			this->renderer1->push_quad(quad);
			this->renderer1->render_end();
		}

		{
			Sparky::Quad quad = this->renderer2->create_quad(glm::vec3(300.0f, 300.0f, 0.0f), glm::vec2(250, 250), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), this->texture.get());

			this->renderer2->render_begin();
			this->renderer2->push_quad(quad);
			this->renderer2->render_end();
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
