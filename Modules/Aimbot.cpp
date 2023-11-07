#include "Module.h"
#include <iostream>
#include "Aimbot.h"
#include "../Geom.h"
#include "../Memory.h"
#include "../Offsets.h"
#include "../GameData.h"

constexpr double PI = 3.14159265358979323846;

Aimbot::Aimbot() : Module("Aimbot"), player(GameData::GetInstance()->getPlayer()) {
    enemyEntities = GameData::GetInstance()->getEnemyEntities();
}

void Aimbot::tick() const {
    if (GetAsyncKeyState(VK_RBUTTON)) {
        int closestEntityIdx = getClosestEntityIdx();
        if (closestEntityIdx == -1) return;

        Vec3 enemyHead = enemyEntities[closestEntityIdx].getHeadPos();
        Vec3 playerHead = player->getHeadPos();
        Vec3 distance = enemyHead - playerHead;

        float yaw = (float)std::atan2(distance.y, distance.x) * 180 / PI;
        float pitch = (float)std::atan2(distance.z, std::sqrt(distance.x * distance.x + distance.y * distance.y)) * 180 / PI;

        player->setPitch(-pitch);
        player->setYaw(yaw);
    }
}

int Aimbot::getClosestEntityIdx() const{
    int closestEntityIdx = -1;
    int closestEntitySquareDistance = -1;
    for (int i = 0; i < enemyEntities.size(); i++) {
        if (enemyEntities[i].isDead()) continue;

        if (closestEntityIdx == -1) {
            closestEntityIdx = i;
            closestEntitySquareDistance = Vec3SquareDistance(player->getFeetPos(), enemyEntities[i].getFeetPos());
        }
        else {
            int entityDistance = Vec3SquareDistance(player->getFeetPos(), enemyEntities[i].getFeetPos());
            if (entityDistance < closestEntitySquareDistance) {
                closestEntityIdx = i;
                closestEntitySquareDistance = entityDistance;
            }
        }
    }
    return closestEntityIdx;
}