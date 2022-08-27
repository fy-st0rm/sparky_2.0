#pragma once
#include "dependency.h"
#include "../core/core.h"

class Scene
{
public:
	// Virtual functions
	virtual void on_entry() {};
	virtual void on_update(double dt) {};
	virtual void on_event(SparkyEvent event) {};
	virtual void on_exit() {};
};
