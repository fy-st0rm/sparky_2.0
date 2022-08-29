#include "sparky.h"

struct ArgStruct {
	Application* app;
};


class Home : public Scene
{
private:
	Application* app;
	std::shared_ptr<QuadRenderer> renderer;
	
	float x = 0.0f;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		this->renderer = std::make_shared<QuadRenderer>(10);
		std::cout << "Home scene constructed.\n";
	};

	void on_entry()
	{
		std::cout << "Entered home\n";
	}

	void on_event(SparkyEvent event)
	{
	}

	void on_update(double dt)
	{
		renderer->render_begin();
		Quad quad = renderer->create_quad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.5, 0.5));
		renderer->push_quad(quad);
		renderer->render_end();
		x += 0.01f;
	}

	void on_exit()
	{
		std::cout << "Leaving home\n";
	}
};

class Test : public Application
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
