#include <vector>
#include "Module.h"
#include "Esp.h";
#include "Modules.h"

std::vector<Module*> modules;

void modulesInit() {
	modules.push_back(new Esp);
}

void tick() {
	for (int i = 0; i < modules.size(); i++) {
		if (modules[i]->isActive()) {
			modules[i]->tick();
		}
	}
}