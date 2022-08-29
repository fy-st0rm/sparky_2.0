#include "sparky.h"

struct ArgStruct {
	Application* app;
};


class Home : public Scene
{
private:
	Application* app;
	std::shared_ptr<BoxRenderer> renderer;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		this->renderer = std::make_shared<BoxRenderer>(10);
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
		renderer->render();
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
