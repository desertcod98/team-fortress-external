#pragma once
#include <string>
#include "Memory.h"
#include "Offsets.h"
#include "Geom.h"


class Entity {
	uint32_t address;
	int team;
	std::string name;
	Memory* memory;
	uintptr_t engineDllBase;

public:
	Entity(uint32_t address);

	std::string getName() const{
		return name;
	}

	int getTeam() const {
		return team;
	}

	//int getHealth();
	bool isDead() const;
	Vec3 getFeetPos() const;
	Vec3 getHeadPos() const;
	void setYaw(float yaw);
	void setPitch(float pitch);
};

