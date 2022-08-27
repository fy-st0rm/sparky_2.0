#pragma once
#include "dependency.h"

// Sparky tags
enum tags
{
	SPARKY_NULL,
	SPARKY_SCENE_EMPTY
};

// Color codes
class Color
{
public:
	static std::string PURPLE;
	static std::string BLUE;
	static std::string CYAN;
	static std::string GREEN;
	static std::string YELLOW;
	static std::string RED;
	static std::string BLACK;
	static std::string DEFAULT;
	static std::string BOLD;
	static std::string UNDERLINE;
};


// Static class to print logs
class Log
{
public:
	static std::unordered_map<int, std::string> usage_msg;

public:
	static void usage(int tag);
	static void error(const std::string& msg, int tag);
	static void sucess(const std::string& msg, int tag);
	static void warning(const std::string& msg, int tag);
};
