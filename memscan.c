#include "memscan.h"
#include <Psapi.h>
LPVOID FindPattern(const BYTE* lpPattern, LPCSTR szMask)
{
    HMODULE hModule = GetModuleHandle(NULL);
    DWORD image_base = (DWORD)hModule;
    DWORD image_size = 0;
    MODULEINFO moduleInfo;
    if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)))
    {
        image_size = moduleInfo.SizeOfImage;
    }
    DWORD dwLength = strlen(szMask);
    DWORD dwImageEnd = image_base + image_size - dwLength;
    DWORD_PTR i, j;
    for (j = image_base; j < dwImageEnd; ++j)
    {
        for (i = 0; i < dwLength && (szMask[i] == '?' || *(BYTE*)(j + i) == lpPattern[i]); ++i);
        if (i == dwLength) return (LPVOID)j;
    }

    return NULL;
}

DWORD ReadPointer(DWORD address, std::vector<int> offsets)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    HMODULE hModule = GetModuleHandle(NULL);
    DWORD image_base = (DWORD)hModule;
    address += image_base;
    ReadProcessMemory(hProcess, (LPCVOID)address, &address, sizeof(address), NULL);
    for (int i = 0; i < offsets.size() - 1; ++i)
    {
        ReadProcessMemory(hProcess, (LPCVOID)(address + offsets.at(i)), &address, sizeof(address), NULL);
    }
    address += offsets.back();
    return address;
}