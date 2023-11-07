#include "Module.h"
#include <iostream>
#include "Esp.h"
#include "../Geom.h"
#include "../Memory.h"
#include "../Offsets.h"
#include "../GameData.h"

Esp::Esp() : Module("Esp") , player(GameData::GetInstance()->getPlayer()){
    entities = GameData::GetInstance()->getEntities();
}

void Esp::tick() const{
    view_matrix_t vm = memory->Read<view_matrix_t>(engineDllBase + offsets::view_matrix);
    for (int i = 0; i < entities.size(); i++) {
        //if (entities[i].getTeam() == player->getTeam()) continue; //TODO just get GameData::getEnemyEntities()
        if (entities[i].isDead()) continue;

        //ESP
        Vec3 feetPos = entities[i].getFeetPos();
        Vec3 screenFeetPos = WorldToScreen(feetPos, vm);
        Vec3 headPos = feetPos + Vec3{ 0,0,70 };
        Vec3 screenHeadPos = WorldToScreen(headPos, vm);

        float h = screenFeetPos.y - screenHeadPos.y;
        float w = h / 1.3;

        DrawBorderBox(screenHeadPos.x - w / 2, screenHeadPos.y - 20, w, h, 2);
    }
}