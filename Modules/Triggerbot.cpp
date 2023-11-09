#include "Module.h"
#include <iostream>
#include "Triggerbot.h"
#include "../Geom.h"
#include "../Memory.h"
#include "../Offsets.h"
#include "../GameData.h"

INPUT input;

Triggerbot::Triggerbot() : Module("Triggerbot"), player(GameData::GetInstance()->getPlayer()) {
    enemyEntities = GameData::GetInstance()->getEnemyEntities();
    input.type = INPUT_MOUSE;
}

void Triggerbot::tick() const {
    view_matrix_t vm = memory->Read<view_matrix_t>(engineDllBase + offsets::view_matrix);
    for (int i = 0; i < enemyEntities.size(); i++) {
        if (enemyEntities[i].isDead()) continue;

        int screenWidth = getWidth();
        int screenHeight = getHeight();

        Vec3 feetPos = enemyEntities[i].getFeetPos();
        Vec3 screenFeetPos = WorldToScreen(feetPos, vm);
        Vec3 headPos = feetPos + Vec3{ 0,0,65 };
        Vec3 screenHeadPos = WorldToScreen(headPos, vm);

        float h = screenFeetPos.y - screenHeadPos.y;
        float w = h / 1.6;

        if (screenHeadPos.x != 0 && screenHeadPos.y != 0) {
            if (screenWidth / 2.f < screenHeadPos.x + w/2 && screenWidth / 2.f > screenHeadPos.x - w/2
                && screenHeight / 2.f < screenFeetPos.y && screenHeight / 2.f > screenHeadPos.y
                && !player->isDead()) {
                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                SendInput(1, &input, sizeof(INPUT));
                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                SendInput(1, &input, sizeof(INPUT));
                Sleep(10);
            }
        }
    }
}