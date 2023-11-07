#include "Module.h"
#include <iostream>
#include "Tracers.h"
#include "../Geom.h"
#include "../Memory.h"
#include "../Offsets.h"
#include "../GameData.h"

Tracers::Tracers() : Module("Tracers"), player(GameData::GetInstance()->getPlayer()) {
    enemyEntities = GameData::GetInstance()->getEnemyEntities();
}

void Tracers::tick() const {
    view_matrix_t vm = memory->Read<view_matrix_t>(engineDllBase + offsets::view_matrix);
    for (int i = 0; i < enemyEntities.size(); i++) {
        if (enemyEntities[i].isDead()) continue;

        int screenWidth = getWidth();
        int screenHeight = getHeight();

        Vec3 headPos = enemyEntities[i].getHeadPos();
        Vec3 screenHeadPos = WorldToScreen(headPos, vm);

        if(screenHeadPos.x != 0 && screenHeadPos.y != 0)
        DrawLine(screenWidth / 2.f, screenHeight / 2.f, screenHeadPos.x, screenHeadPos.y);
    }
}