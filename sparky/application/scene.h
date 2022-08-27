#pragma once
#include "dependency.h"

class Scene
{
public:
	// Virtual functions
	virtual void on_start() {};
	virtual void on_update() {};
	virtual void on_event() {};
	virtual void on_destroy() {};
};
