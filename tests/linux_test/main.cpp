#include "sparky.h"

#define IDLE "idle"
#define WALK "walk"
#define LEFT "left"
#define RIGHT "right"

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

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer;

	// Entity manager
	std::shared_ptr<Sparky::EntityManager> manager;

	// Entity
	std::shared_ptr<Sparky::Texture> player_sprite;
	std::shared_ptr<Sparky::Texture> white;

	// Components
	Sparky::TransformComponent* tcomp;
	Sparky::AnimationComponent* acomp;

	// Movement
	float speed = 5.0f;
	float ang = 0.0f;
	bool left, right, up, down;

public:
	Main(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		// Initializing movement
		left = right = up = down = false;

		// Initializing camera
		this->camera = std::make_shared<Sparky::OrthoCamera>(glm::vec3(0,0,0), 0.0f, 800.0f, 0.0f, 600.0f, -1000.0f, 1000.0f);

		// Creating renderer
		this->renderer = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		// Initializing entity manager
		this->manager = std::make_shared<Sparky::EntityManager>();

		// Loading sprite
		this->player_sprite = std::make_shared<Sparky::Texture>("player_2.png");
		this->white = std::make_shared<Sparky::Texture>();

		// Entity
		Sparky::Entity* ent = this->manager->add_entity<Sparky::Entity>(this->manager);
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(this->ang), glm::vec3(0,1,0));
		this->tcomp = ent->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 187), rot);
		ent->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0.0f,0.0f,1.0f,1.0f), this->player_sprite);
		ent->add_component<Sparky::BoxColliderComponent>(glm::vec4(100, 100, 100, 100));
	};
	~Main() {};

public:
	void on_event(SparkyEvent event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_q:
				{
					this->ang += 1.0f;
					glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(this->ang), glm::vec3(0,1,0));
					this->tcomp->set_rotation(rot);
				}
			}
		}
	}

	void on_update(double dt)
	{
		app->clear({0.5f, 0.5f, 0.5f, 1.0f});
		this->manager->update(this->renderer);
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
