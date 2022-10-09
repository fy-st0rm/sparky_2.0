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
	std::shared_ptr<Sparky::Entity> ent;
	std::shared_ptr<Sparky::Texture> player_sprite;

	// Components
	Sparky::TransformComponent* tcomp;
	Sparky::AnimationComponent* acomp;

	// Movement
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

		// Loading sprite
		this->player_sprite = std::make_shared<Sparky::Texture>("player.png");

		// Entity
		this->ent = std::make_shared<Sparky::Entity>(this->manager);
		this->tcomp = this->ent->add_component<Sparky::TransformComponent>(glm::vec3(100, 100, 0), glm::vec2(100, 187));
		this->ent->add_component<Sparky::RenderComponent>(glm::vec4(1,1,1,1), glm::vec4(0.0f,1.0f/2.0f,1.0f/11.0f,1.0f/2.0f), *this->player_sprite.get());
		this->ent->add_component<Sparky::BoxColliderComponent>(glm::vec4(100, 100, 100, 100));
		this->acomp = this->ent->add_component<Sparky::AnimationComponent>();

		this->set_up_animation();
	};
	~Main() {};

public:
	void set_up_animation()
	{
		std::vector<glm::vec4> left_idle_data, left_walk_data;
		for (float i = 0.0f; i < 11; i++)
			left_idle_data.push_back({i / 11.0f, 1.0f/2.0f, 1/11.0f, 1.0f/2.0f});
		for (float i = 0.0f; i < 6; i++)
			left_walk_data.push_back({i / 11.0f, 0.0f, 1/11.0f, 1.0f/2.0f});

		Sparky::AnimationNode idle(IDLE);
		Sparky::AnimationNode walk(WALK);

		Sparky::AnimationNode left_idle(LEFT, left_idle_data, 8.0f);
		Sparky::AnimationNode left_walk(LEFT, left_walk_data, 8.0f);

		idle.add_child(left_idle);
		walk.add_child(left_walk);

		this->acomp->add_node(idle);
		this->acomp->add_node(walk);

		std::vector<std::string> states = { IDLE, LEFT };
		this->acomp->switch_state(states);
	}

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
		app->clear({0.5f, 0.5f, 0.5f, 1.0f});

		glm::vec3 pos = this->tcomp->get_pos();
		if (this->up)
		{
			pos.y += speed;
			std::vector<std::string> states = { WALK, LEFT };
			this->acomp->switch_state(states);
		}
		if (this->down)
		{
			pos.y -= speed;
			std::vector<std::string> states = { WALK, LEFT };
			this->acomp->switch_state(states);
		}
		if (this->left)
		{
			pos.x -= speed;
			std::vector<std::string> states = { WALK, LEFT };
			this->acomp->switch_state(states);
		}
		if (this->right)
		{
			pos.x += speed;
			std::vector<std::string> states = { WALK, LEFT };
			this->acomp->switch_state(states);
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
