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
#include "Modules/Modules.h"
#include "GameData.h"

int main()
{
    GameData *gameData = GameData::GetInstance();
    modulesInit();

    while (true) {
        tick();
    }

    return 0;
}