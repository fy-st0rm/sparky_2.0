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
	std::shared_ptr<Sparky::QuadRenderer> qr;
	std::shared_ptr<Sparky::TextRenderer> tr;

	// File
	std::stringstream file_data;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing camera
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		this->camera = std::make_shared<Sparky::OrthoCamera>(pos, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		this->texture = std::make_shared<Sparky::Texture>("Us.png");

		// Initializing renderers
		this->qr = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);
		this->tr = std::make_shared<Sparky::TextRenderer>("consola.ttf", 15, 1000, this->camera);

		// Reading a file
		std::ifstream file("test.txt");
		std::string line;
		while (std::getline(file, line))
			this->file_data << line;

		std::cout << "Main scene constructed.\n";
	};
	~Main() {};

public:
	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});

		{
			Sparky::Quad quad = this->qr->create_quad(glm::vec3(300.0f, 300.0f, 0.0f), glm::vec2(150,150), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), this->texture.get());

			this->qr->render_begin();
			this->qr->push_quad(quad);
			this->qr->render_end();
		}

		{
			this->tr->render_begin();
			this->tr->push_text(file_data.str(), glm::vec3(100.0f, 100.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			this->tr->render_end();
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
