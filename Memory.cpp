#include "Memory.h"
#include <TlHelp32.h>
#include <vector>
#include "StringUtil.h"

Memory* Memory::instance = nullptr;;

Memory* Memory::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (instance == nullptr) {
		instance = new Memory("hl2.exe");
	}
	return instance;
}

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

Vec3 Memory::ReadVec3(uintptr_t address) {
	byte buf[4 * 3];
	ReadProcessMemory(this->process, (LPCVOID)address, &buf, sizeof(buf), NULL);
	float x;
	float y;
	float z;
	memcpy(&x, buf, 4);
	memcpy(&y, buf + 4, 4);
	memcpy(&z, buf + 8, 4);
	return Vec3{ x,y,z };
}
std::string Memory::ReadString(uintptr_t address, int size) {
	char res[128];
	ReadProcessMemory(this->process, (LPCVOID)address, &res, sizeof(res), NULL);
	res[strlen(res)] = '\0';
	std::string final = std::string(res);
	return final;
}