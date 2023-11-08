#include <vector>
#include "Module.h"
#include "Modules.h"
#include "Esp.h";
#include "Aimbot.h"
#include "Tracers.h"
#include "Triggerbot.h"

std::vector<Module*> modules;

void modulesInit() {
	modules.push_back(new Esp);
	modules.push_back(new Aimbot);
	modules.push_back(new Tracers);
	modules.push_back(new Triggerbot);
}

void tick() {
	for (int i = 0; i < modules.size(); i++) {
		if (modules[i]->isActive()) {
			modules[i]->tick();
		}
	}
}