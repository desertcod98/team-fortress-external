#include "Entity.h"


Entity::Entity(uint32_t address_p) {
	address = address_p;
	memory = Memory::GetInstance();
	engineDllBase = memory->GetModuleAddress("engine.dll");
	name = memory->ReadString(address + offsets::entity_name, 32);
	team = memory->Read<int>(address + offsets::entity_team);
	//MessageBoxA(NULL, name.c_str(), "Dll injected", MB_OK);
	//team = memory->Read<uint32_t>(address + offsets::entity_team);
}

Vec3 Entity::getFeetPos() const {
	return memory->ReadVec3(address + offsets::entity_coords);
}

Vec3 Entity::getHeadPos() const {
	return memory->ReadVec3(address + offsets::entity_coords) + Vec3{0,0,70};
}


//int Entity::getHealth() {
//	return memory->Read<uint32_t>(address + offsets::entity_health);
//}

bool Entity::isDead() const {
	return memory->Read<uint32_t>(address + offsets::entity_is_dead);
}

void Entity::setYaw(float yaw) {
	memory->Write(engineDllBase + offsets::writeable_yaw, yaw);
}

void Entity::setPitch(float pitch) {
	memory->Write(engineDllBase + offsets::writeable_pitch, pitch);
}

