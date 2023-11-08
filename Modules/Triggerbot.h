#pragma once
#include "Module.h"
#include <iostream>
#include <vector>
#include "../Entity.h"

class Triggerbot : public Module {
private:
	std::vector<Entity> enemyEntities;
	Entity* player;
public:
	Triggerbot();
	virtual void tick() const override;
};
