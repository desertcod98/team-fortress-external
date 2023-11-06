#pragma once
#include "Module.h"
#include <iostream>

class Esp : public Module {
public:
	Esp() : Module("Esp") {}
	virtual void tick() const override;
};
