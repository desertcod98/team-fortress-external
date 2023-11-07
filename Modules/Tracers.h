#pragma once
#include "Module.h"
#include <iostream>
#include <vector>
#include "../Entity.h"

class Tracers : public Module {
private:
	std::vector<Entity> enemyEntities;
	Entity* player;
public:
	Tracers();
	virtual void tick() const override;
};
