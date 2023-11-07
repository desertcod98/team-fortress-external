#pragma once
#include "Module.h"
#include <iostream>
#include <vector>
#include "../Entity.h"

class Esp : public Module {
private:
	std::vector<Entity> enemyEntities;
	Entity* player;
public:
	Esp();
	virtual void tick() const override;
};
