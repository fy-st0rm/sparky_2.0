#include "sparky.h"

struct ArgStruct {
	Sparky::Application* app;
};


class Home : public Sparky::Scene
{
private:
	Sparky::Application* app;
	std::shared_ptr<Sparky::QuadRenderer> renderer;
	std::shared_ptr<Sparky::Texture> texture;
	Sparky::Texture white;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000);
		this->texture = std::make_shared<Sparky::Texture>("Us.png");
		std::cout << "Home scene constructed.\n";
	};

	void on_entry(){}
	void on_exit(){}
	void on_event(SparkyEvent event) {}

	void on_update(double dt)
	{
		renderer->render_begin();
		Sparky::Quad quad1 = renderer->create_quad(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec2(0.5, 0.5), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), *texture);
		Sparky::Quad quad2 = renderer->create_quad(glm::vec3(0.1f, 0.0f, 0.0f), glm::vec2(0.5, 0.5), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), white);
		renderer->push_quad(quad1);
		renderer->push_quad(quad2);
//		renderer->print_buffer();
		renderer->render_end();
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

int main()
{
	Test test;
	test.run("Sparky application", 800, 600, 60.0f);
}
