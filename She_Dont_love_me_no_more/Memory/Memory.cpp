#include "Memory.h"

DWORD Memory::pid = 0;
HANDLE Memory::hProc = 0;
MODULEENTRY32 Memory::modEntry = { 0 };

DWORD Memory::GetProcessId(const char* procName)
{
    DWORD pid = 0;
    HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 ProcEntry;
    ProcEntry.dwSize = sizeof(ProcEntry);

    do
    {
        if (!strcmp(ProcEntry.szExeFile, procName))
        {
            pid = ProcEntry.th32ProcessID;
            CloseHandle(hPID);
            break;
        }
    } while (Process32Next(hPID, &ProcEntry));

    return pid;
}

MODULEENTRY32 Memory::GetModule(DWORD procId, const char* modName)
{
    MODULEENTRY32 modEntry;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!strcmp(modEntry.szModule, modName))
                {
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modEntry;
}

uint64_t Memory::GetActualAddr(uint64_t addr, int off)
{
    uint32_t address = 0x0;
    address = (addr + Read<uint32_t>(addr) + off) - (uint64_t)modEntry.modBaseAddr;
    return address;
}