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
	Sparky::Texture white;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

public:
	Main(void* arg_struct)
	{
		// Getting the sparky application from the argument
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing the camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Initializing the renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});

		{
			Sparky::Quad quad = this->renderer->create_quad(glm::vec3(300.0f, 100.0f, 0.0f), glm::vec2(250, 250), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &this->white);


			// Rendering
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
