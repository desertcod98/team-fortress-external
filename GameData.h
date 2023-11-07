#pragma once
#include <string>
#include <vector>
#include "Entity.h"

class GameData {
protected:
	static GameData* instance;
	GameData();
private:
	Entity* player;
	std::vector<Entity> entities;
	std::vector<Entity> enemyEntities;
	Memory* memory;

	uintptr_t getPlayerAddress();
public:
	GameData(GameData& other) = delete;
	void operator=(const GameData&) = delete;
	static GameData* GetInstance();

	Entity* getPlayer();
	std::vector<Entity> getEntities();
	std::vector<Entity> getEnemyEntities();
};