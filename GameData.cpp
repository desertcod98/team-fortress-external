#include "GameData.h"
#include <vector>
#include <iostream>

GameData* GameData::instance = nullptr;;

GameData* GameData::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameData();
	}
	return instance;
}

GameData::GameData() : memory(Memory::GetInstance()) {
    player = new Entity(getPlayerAddress());
    auto engineDllAddress = memory->GetModuleAddress("engine.dll");

    auto entityListBase = memory->Read<uintptr_t>(engineDllAddress + offsets::entitylist_ptr);
    const auto firstEntityPtr = entityListBase + offsets::first_entity_ptr;
    Entity firstEntity = Entity(memory->Read<uintptr_t>(firstEntityPtr));
    entities.push_back(firstEntity);

    for (int i = 0; i < 32; i++) {
        const uintptr_t entityPtr = firstEntityPtr + ((i + 1) * offsets::entity_ptr_offset);
        const auto entityBase = memory->Read<uintptr_t>(entityPtr);

        if (entityBase == 0x0) break;

        Entity entity = Entity(entityBase);
        entities.push_back(entity);
        
        if (entity.getTeam() != player->getTeam()) {
            enemyEntities.push_back(entity);
        }
    }
}

Entity* GameData::getPlayer() {
	return this->player;
}

std::vector<Entity> GameData::getEntities() {
	return this->entities;
}

std::vector<Entity> GameData::getEnemyEntities() {
	return this->enemyEntities;
}

uintptr_t GameData::getPlayerAddress() {
    auto engineDllAddress = memory->GetModuleAddress("engine.dll");
    auto entityListBase = memory->Read<uintptr_t>(engineDllAddress + offsets::entitylist_ptr);
    auto playerBase = memory->Read<uintptr_t>(entityListBase + offsets::player_ptr);
    return playerBase;
}