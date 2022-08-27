#include "log.h"

// Initializing colors
std::string Color::PURPLE    = "\033[95m";
std::string Color::BLUE      = "\033[94m";
std::string Color::CYAN      = "\033[96m";
std::string Color::GREEN     = "\033[92m";
std::string Color::YELLOW    = "\033[93m";
std::string Color::RED       = "\033[91m";
std::string Color::BLACK     = "\033[30m";
std::string Color::DEFAULT   = "\033[0m";
std::string Color::BOLD      = "\033[1m";
std::string Color::UNDERLINE = "\033[4m";

// Initializing usages
std::unordered_map<int, std::string> Log::usage_msg = {
	{ SPARKY_SCENE_EMPTY, "[Usage]: use `switch_scene(const std::string& scene_name)` to switch to required scene.\n"}
};

// Log functions
void Log::usage(int tag)
{
	if (tag == SPARKY_NULL) return;
	std::cout << Color::GREEN << Log::usage_msg[tag] << Color::DEFAULT << std::endl;
}

void Log::error(const std::string& msg, int tag)
{
	std::cerr << Color::RED << msg << Color::DEFAULT << std::endl;
	Log::usage(tag);
	exit(1);
}

void Log::sucess(const std::string& msg, int tag)
{
	std::cout << Color::GREEN << msg << Color::DEFAULT << std::endl;
	Log::usage(tag);
}

void Log::warning(const std::string& msg, int tag)
{
	std::cerr << Color::YELLOW << msg << Color::DEFAULT << std::endl;
	Log::usage(tag);
}
