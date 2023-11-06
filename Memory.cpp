#include "Memory.h"
#include <TlHelp32.h>
#include <vector>
#include "StringUtil.h"

Memory::Memory(const std::string processName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while(Process32Next(snapshot, &entry)){
		if (!strcmp(processName.c_str(), convertWideToNarrow(entry.szExeFile))) {
			this->id = entry.th32ProcessID;
			this->process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->id);
			break;
		}
	}

	if (snapshot) {
		CloseHandle(snapshot);
	}
};
Memory::~Memory() {
	if (this->process) CloseHandle(this->process);
};


DWORD Memory::GetProcessId() {
	return this->id;
};

HANDLE Memory::GetProcessHandle() {
	return this->process;
};

uintptr_t Memory::GetterModuleAddress() {
	return this->moduleAddress;
};

uintptr_t Memory::GetModuleAddress(const std::string moduleName) {
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);
	
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->id);

	uintptr_t res = 0;

	

	while (Module32Next(snapshot, &entry)) {
		if (!strcmp(moduleName.c_str(), convertWideToNarrow(entry.szModule))) {
			res = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}
	}

	if (snapshot) {
		CloseHandle(snapshot);
	}
	this->moduleAddress = res;
	return res;
};

uintptr_t Memory::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size() -1; ++i)
	{
		addr += offsets[i];
		ReadProcessMemory(this->process, (BYTE*)addr, &addr, sizeof(addr), 0);
		
	}
	addr += offsets[offsets.size() - 1];
	return addr;
}
