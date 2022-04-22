#include <Windows.h>
#include <TlHelp32.h>
#include <stdint.h>

namespace Memory
{
	extern DWORD pid;
	extern HANDLE hProc;
	extern MODULEENTRY32 modEntry;

	DWORD GetProcessId(const char* procName);
	MODULEENTRY32 GetModule(DWORD procId, const char* modName);
	uint64_t GetActualAddr(uint64_t addr, int off = 4);

	template<typename T> T Read(uint64_t address)
	{
		T buffer;
		ReadProcessMemory(hProc, (void*)address, &buffer, sizeof(T), nullptr);
		return buffer;
	}

	template<typename T> void Write(HANDLE hProcess, uintptr_t address, T buffer)
	{
		WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	}
}