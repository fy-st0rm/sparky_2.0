#include "sparky.h"

struct ArgStruct {
	Application* app;
};

class Home : public Scene
{
private:
	Application* app;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;
		std::cout << "Home scene constructed.\n";
	};

	void on_start()
	{
		std::cout << "Entered home\n";
	}

	void on_update()
	{
		app->switch_scene("School");
	}
};

class School : public Scene
{
private:
	Application* app;

public:
	School(void* arg_struct) 
	{
		app = ((ArgStruct*)arg_struct)->app;
		std::cout << "School scene constructed.\n";
	};

	void on_start()
	{
		std::cout << "Entered school\n";
	}
	
	void on_update()
	{
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
		add_scene<School>("School", &arg);
		switch_scene("Home");
	}
};

int main()
{
	Test test;
	test.run("Sparky application", 800, 600);
}
