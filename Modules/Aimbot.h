#pragma once
#include "Module.h"
#include <iostream>
#include <vector>
#include "../Entity.h"

class Aimbot : public Module {
private:
	std::vector<Entity> enemyEntities;
	Entity* player;

	int getClosestEntityIdx() const;
public:
	Aimbot();
	virtual void tick() const override;
};
