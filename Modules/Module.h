#pragma once
#include <string>
#include "../Memory.h"

class Module {
protected:
	bool active = true;
	std::string name; 
	Memory* memory;
	uintptr_t engineDllBase;
public:
	Module(std::string nameP) {
		name = nameP;
		memory = Memory::GetInstance();
		engineDllBase = memory->GetModuleAddress("engine.dll");
	}
	
	void toggle() {
		active = !active;
	}
	
	bool isActive() {
		return active;
	}

	virtual void tick() const = 0;
};