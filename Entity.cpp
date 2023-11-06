#include "Entity.h"
#include "Geom.h"
#include "Memory.h"


Entity::Entity(Memory* memory_p, uint32_t address_p) {
	address = address_p;
	memory = memory_p;
	name = memory->ReadString(address + offsets::entity_name, 32);
	//MessageBoxA(NULL, name.c_str(), "Dll injected", MB_OK);
	//team = memory->Read<uint32_t>(address + offsets::entity_team);
}

Vec3 Entity::getFeetPos() {
	return memory->ReadVec3(address + offsets::entity_coords);
}

//int Entity::getHealth() {
//	return memory->Read<uint32_t>(address + offsets::entity_health);
//}

bool Entity::isDead() {
	return memory->Read<uint32_t>(address + offsets::entity_is_dead);
}

//void Entity::setYaw(float yaw) {
//	float readonly_yaw = memory->Read<float>(address + offsets::readonly_yaw);
//	float delta_yaw = yaw - readonly_yaw;
//	uintptr_t writeable_yaw_addr = memory->FindDMAAddy(memory->GetterModuleAddress(), offsets::writeable_yaw);
//	float writeable_yaw = memory->Read<float>(writeable_yaw_addr);
//	memory->Write(writeable_yaw_addr, writeable_yaw + delta_yaw);
//}
//
//void Entity::setPitch(float pitch) {
//	float readonly_pitch = memory->Read<float>(address + offsets::readonly_pitch);
//	float delta_pitch =  pitch - readonly_pitch;
//	uintptr_t writeable_pitch_addr = memory->FindDMAAddy(memory->GetterModuleAddress(), offsets::writeable_pitch);
//	float writeable_pitch = memory->Read<float>(writeable_pitch_addr);
//	memory->Write(writeable_pitch_addr, writeable_pitch + delta_pitch);
//}
//
