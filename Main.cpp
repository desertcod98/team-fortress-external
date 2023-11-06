#include <iostream>
#include <iomanip>
#include <sstream>
#include "Memory.h"
#include "Offsets.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "Entity.h"
#include <vector>
#include <algorithm>

const double PI = 3.14159265358979323846;
int screenXa = GetSystemMetrics(SM_CXSCREEN);
int screenYa = GetSystemMetrics(SM_CYSCREEN);

int main()
{
    auto memory = Memory("hl2.exe");
    auto engineDllAddress = memory.GetModuleAddress("engine.dll");

    auto entityListBase = memory.Read<uintptr_t>(engineDllAddress + offsets::entitylist_ptr);

    auto playerBase = memory.Read<uintptr_t>(entityListBase + offsets::player_ptr);
    Entity player = Entity(&memory, playerBase);
    std::vector<Entity> entities;
    const auto firstEntityPtr = entityListBase + offsets::first_entity_ptr;
    Entity firstEntity = Entity(&memory, memory.Read<uintptr_t>(firstEntityPtr));
    entities.push_back(firstEntity);

    for (int i = 0; i < 32; i++) {
        const uintptr_t entityPtr = firstEntityPtr + ((i + 1) * offsets::entity_ptr_offset);
        const auto entityBase = memory.Read<uintptr_t>(entityPtr);

        if (entityBase == 0x0) break;

        Entity entity = Entity(&memory, entityBase);
        entities.push_back(entity);
    }
    
    setRect();
    while (true) {
        view_matrix_t vm = memory.Read<view_matrix_t>(engineDllAddress + offsets::view_matrix);

        for (int i = 0; i < entities.size(); i++) {
            /*if (entities[i].getTeam() == player.getTeam()) continue;
            if (entities[i].isDead()) continue;*/

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

    return 0;
}