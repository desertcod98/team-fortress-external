#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Geom.h"

class Memory {
protected:
	static Memory* instance;
	Memory(const std::string processName);
private:
	DWORD id = 0; //process id
	HANDLE process = NULL;
	uintptr_t moduleAddress;

public:

	/**
	 * Singletons should not be cloneable.
	 */
	Memory(Memory& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const Memory&) = delete;

	static Memory* GetInstance();

	
	~Memory();

	DWORD GetProcessId();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAddress(const std::string moduleName);
	uintptr_t GetterModuleAddress();

	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

	bool isValidAddress(uintptr_t address);
	bool isValidEntity(uint32_t address);

	template <typename T>
	T Read(uintptr_t address, int size = 0) {
		T value;
		const int res = ReadProcessMemory(this->process, (LPCVOID)address, &value, size == 0 ? sizeof(T) : size, NULL);
		return value;
	}

	template <typename T>
	bool Write(uintptr_t address, T value) {
		return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
	}

	std::string ReadString(uintptr_t address, int size);

	Vec3 ReadVec3(uintptr_t address);
};


