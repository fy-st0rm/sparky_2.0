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
	Sparky::Texture white;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity manager
	std::shared_ptr<Sparky::EntityManager> manager;

	// Entity
	std::shared_ptr<Sparky::Entity> ent_1, ent_2;

	// Movement
	Sparky::TransformComponent* tcomp;
	float speed = 5.0f;
	bool left, right, up, down;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing movement
		left = right = up = down = false;

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

		// Creating renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Initializing entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		// Entity
		this->ent_1 = std::make_shared<Sparky::Entity>(this->manager);
		this->ent_1->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 100));
		this->ent_1->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0,0,1,1), this->white);
		this->ent_1->add_component<Sparky::BoxColliderComponent>(glm::vec4(100, 100, 100, 100));
		this->tcomp = this->ent_1->get_component<Sparky::TransformComponent>();

		int x = 0;
		for (int i = 0; i < 20; i++)
		{
			Sparky::Entity* box = new Sparky::Entity(this->manager);
			box->add_component<Sparky::TransformComponent>(glm::vec3(x, 50, 0), glm::vec2(100, 100));
			box->add_component<Sparky::RenderComponent>(glm::vec4(i % 2,0,1,1), glm::vec4(0,0,1,1), this->white);
			box->add_component<Sparky::BoxColliderComponent>(glm::vec4(x, 50, 100, 100));
			x += 100;
		}

		Sparky::Entity* box = new Sparky::Entity(this->manager);
		box->add_component<Sparky::TransformComponent>(glm::vec3(0, 150, 0), glm::vec2(100, 100));
		box->add_component<Sparky::RenderComponent>(glm::vec4(1,0,1,1), glm::vec4(0,0,1,1), this->white);
		box->add_component<Sparky::BoxColliderComponent>(glm::vec4(0, 150, 100, 100));

	};
	~Main() {};

public:
	void on_event(SparkyEvent event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					this->up = true;
					break;
				case SDLK_s:
					this->down = true;
					break;
				case SDLK_a:
					this->left = true;
					break;
				case SDLK_d:
					this->right = true;
					break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					this->up = false;
					break;
				case SDLK_s:
					this->down = false;
					break;
				case SDLK_a:
					this->left = false;
					break;
				case SDLK_d:
					this->right = false;
					break;
			}
		}
	}

	void on_update(double dt)
	{
		app->clear({0.0f, 0.0f, 0.0f, 1.0f});

		glm::vec3 pos = this->tcomp->get_pos();
		if (this->up)
		{
			pos.y += speed;
		}
		if (this->down)
		{
			pos.y -= speed;
		}
		if (this->left)
		{
			pos.x -= speed;
		}
		if (this->right)
		{
			pos.x += speed;
		}
		this->tcomp->set_pos(pos);

		this->manager->update(this->renderer);
		//this->manager->print_buffer();
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
