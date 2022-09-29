#include "sparky.h"

struct ArgStruct {
	Sparky::Application* app;
};

class Home : public Sparky::Scene
{
private:
	Sparky::Application* app;

	// Textures
	std::shared_ptr<Sparky::Texture> texture;
	Sparky::Texture white;

	// Camera
	std::shared_ptr<Sparky::OrthoCamera> camera;

	// Renderer
	std::shared_ptr<Sparky::QuadRenderer> renderer1;
	std::shared_ptr<Sparky::QuadRenderer> renderer2;

	float speed = 5;

public:
	Home(void* arg_struct)
	{
		app = ((ArgStruct*)arg_struct)->app;

		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		this->camera = std::make_shared<Sparky::OrthoCamera>(pos, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		this->texture = std::make_shared<Sparky::Texture>("Us.png");

		this->renderer1 = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);
		this->renderer2 = std::make_shared<Sparky::QuadRenderer>(1000, this->camera);

		std::cout << "Home scene constructed.\n";
	};

	void on_entry(){}
	void on_exit(){}
	void on_event(SparkyEvent event) 
	{
		if (event.type == SDL_KEYDOWN)
		{
			glm::vec3 pos = this->camera->get_position();
			float rotation = this->camera->get_rotation();
			switch (event.key.keysym.sym)
			{
				// Camera movement
				case SDLK_w:
					this->camera->set_position({ pos.x, speed + pos.y, pos.z });
					break;
				case SDLK_a:
					this->camera->set_position({ pos.x - speed, pos.y, pos.z });
					break;
				case SDLK_s:
					this->camera->set_position({ pos.x, pos.y - speed, pos.z });
					break;
				case SDLK_d:
					this->camera->set_position({ pos.x + speed, pos.y, pos.z });
					break;

				// Camera rotation
				case SDLK_q:
					this->camera->set_rotation(rotation - speed);
					break;
				case SDLK_e:
					this->camera->set_rotation(rotation + speed);
					break;

				// Shader switch
				case SDLK_r:
					this->renderer2->switch_shader_from_file("vert.vs", "frag.fs");
					break;
				case SDLK_t:
					this->renderer2->switch_shader_from_string(Sparky::SPARKY_DEFAULT_VERT_SHADER, Sparky::SPARKY_DEFAULT_FRAG_SHADER);
					break;
			}
		}
	}

	void on_update(double dt)
	{
		{
			Sparky::Quad quad1 = this->renderer1->create_quad(glm::vec3(100.0f, 100.0f, 0.0f), glm::vec2(200, 200), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.get());
			this->renderer1->render_begin();
			this->renderer1->push_quad(quad1);
			this->renderer1->render_end();
		}
		{
			Sparky::Quad quad2 = this->renderer2->create_quad(glm::vec3(300.0f, 100.0f, 0.0f), glm::vec2(50, 50), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &white);
			this->renderer2->render_begin();
			this->renderer2->push_quad(quad2);
			this->renderer2->render_end();
		}
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

int main(int argc, char** argv)
{
	Test test;
	test.run("Sparky application", 800, 600, 60.0f, 0);
	return 0;
}
