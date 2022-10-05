#include "component.h"

namespace Sparky {
	void AnimationComponent::add_node(AnimationNode& node)
	{
		this->state_register[node.get_name()] = node;
	}

	AnimationNode AnimationComponent::find_curr_node(AnimationNode& primary, std::vector<std::string>& state)
	{
		for (auto& name : state)
		{
			// Getting the child of primary nodes
			std::vector<AnimationNode> child = primary.get_child();
			if (child.size() == 0)
				Log::error(primary.get_name() + " doesnt have a child nodes. And you tried to access them", SPARKY_NULL);

			// Scanning through the child for the matching name
			for (auto i : child)
			{
				if (i.get_name() == name)
				{
					if (state.size() > 1)
					{
						// If more path is left then searching for the childs of child
						state.erase(state.begin());
						return this->find_curr_node(i, state);
					}
					return i;
				}
			}
		}

		// If none of the name match
		std::string error;
		for (auto i : state)
			error += i + " ";
		Log::error("Cannot find the state from the given path `" + error + "`", SPARKY_NULL);
	}

	void AnimationComponent::switch_state(std::vector<std::string>& state)
	{
		if (state.size() == 0) return;
		if (this->state_register.find(state[0]) == this->state_register.end())
			Log::error("State with name " + state[0] + " doesnt exists in register.", SPARKY_NULL);

		// Getting primary node
		AnimationNode& node = this->state_register[state[0]];
		state.erase(state.begin());

		// Scanning through the childs
		AnimationNode found_node = this->find_curr_node(node, state);

		// Reseting the index of the frame if the state is new
		if (this->curr_node.get_name() == "null")
		{
			this->curr_node = found_node;
			return;
		}

		if (found_node.get_id() != this->curr_node.get_id())
		{
			this->curr_node = found_node;
			this->anime_idx = 0.0f;
		}
	}

	glm::vec4 AnimationComponent::get_current_frame()
	{
		if (this->curr_node.get_name() == "null")
			Log::error("Default animation state is not defined.", SPARKY_NULL); // TODO: Add usage here

		// Getting the data from the node and extracting the current coordinates
		std::vector<glm::vec4> data = this->curr_node.get_data();
		glm::vec4 cords = data.at((int)round(this->anime_idx));

		// Increasing the animation index according to the speed of the node
		this->anime_idx += 1.0f / this->curr_node.get_speed();

		// Reseting the index if it exists the buffer
		if ((int)round(this->anime_idx) >= data.size())
			this->anime_idx = 0.0f;
		return cords;
	}

	void AnimationComponent::print_node(AnimationNode& node)
	{
		std::cout << node.get_name() << ": " << std::endl;
		std::cout << "\t--Data: [";
		std::vector<glm::vec4> data = node.get_data();
		if (data.size())
		{
			for (auto& j : data)
				std::cout << " { " << j.x << ", " << j.y << ", " << j.z << ", " << j.w << " } ";
		}
		else
			std::cout << "null";
		std::cout << "]" << std::endl;
		std::cout << "\t--Speed: " << node.get_speed() << std::endl;
		std::cout << "\t--Child: [";
		std::vector<AnimationNode> child = node.get_child();
		if (child.size())
		{
			for (auto& j : child)
				std::cout << j.get_name() << ", ";
		}
		else
			std::cout << "null";
		std::cout << "]" << std::endl;
	}

	void AnimationComponent::print_buffer()
	{
		for (auto& i : this->state_register)
		{
			AnimationNode n = i.second;
			this->print_node(n);
			auto child = n.get_child();
			if (child.size())
			{
				for (auto& j : child)
					this->print_node(j);
			}
		}
	}
}
