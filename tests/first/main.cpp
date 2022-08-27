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

	void on_entry()
	{
		std::cout << "Entered home\n";
	}

	void on_event(SparkyEvent event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RETURN:
					app->switch_scene("School");
					break;
			}
		}
	}

	void on_update(double dt)
	{
	}

	void on_exit()
	{
		std::cout << "Leaving home\n";
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

	void on_entry()
	{
		std::cout << "Entered school\n";
	}

	void on_event(SparkyEvent event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RETURN:
					app->switch_scene("Home");
					break;
			}
		}
	}
	
	void on_update(double dt)
	{
	}

	void on_exit()
	{
		std::cout << "Leaving School\n";
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
	test.run("Sparky application", 800, 600, 60.0f);
}
