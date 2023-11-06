#pragma once
#include <string>

class Module {
private:
	bool active = true;
	std::string name;
public:
	Module(std::string nameP) {
		name = nameP;
	}
	
	void toggle() {
		active = !active;
	}
	
	bool isActive() {
		return active;
	}

	virtual void tick() const = 0;
};