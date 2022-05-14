#include <Windows.h>
#include <string>
#include "Memory/Memory.h" //Mem lib
#include <iostream>



int main() {
	SetConsoleTitleA("Why She dont love me no more? :(");

	Memory::pid = Memory::GetProcessId("FiveM_b2545_GTAProcess.exe");
	Memory::modEntry = Memory::GetModule(Memory::pid, "adhesive.dll");
	Memory::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Memory::pid);
	

	if (!Memory::pid) {
		std::cout << "Couldn't find the process! FiveM_GTAProcess.exe\n";
	}
	


	std::string token("Give me som ACID PLEASE"); //Parse your valid Rockstar ID and join the server.
	char* tokens = _strdup(token.c_str());
	WriteProcessMemory(Memory::hProc, (LPVOID)(Memory::modEntry.modBaseAddr + 0x02C22AD9 /*Old: 0x02B11AD0*/), &tokens, sizeof(tokens), NULL);
	CloseHandle(Memory::hProc);

}
