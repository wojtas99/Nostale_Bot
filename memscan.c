#include "memscan.h"
#include <Psapi.h>
LPVOID FindPattern(const BYTE* lpPattern, LPCSTR szMask)
{
    HMODULE hModule = GetModuleHandle(NULL);
    DWORD image_base = (DWORD)hModule;  // Default location
    DWORD image_size = 0;
    MODULEINFO moduleInfo;
    if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)))
    {
        image_size = moduleInfo.SizeOfImage;
    }
    DWORD dwLength = strlen(szMask);
    DWORD dwImageEnd = image_base + image_size - dwLength; // End of location
    DWORD_PTR i, j;

    // Scan the whole image for the pattern
    for (j = image_base; j < dwImageEnd; ++j)
    {
        // If the pattern is found, return the address at which it begins
        for (i = 0; i < dwLength && (szMask[i] == '?' || *(BYTE*)(j + i) == lpPattern[i]); ++i);
        if (i == dwLength) return (LPVOID)j;
    }

    return NULL;
}

DWORD ReadPointer(DWORD address, std::vector<int> offsets)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    ReadProcessMemory(hProcess, (LPCVOID)address, &address, sizeof(address), NULL);
    for (int i = 0; i < offsets.size() - 1; ++i)
    {
        ReadProcessMemory(hProcess, (LPCVOID)(address + offsets.at(i)), &address, sizeof(address), NULL);
    }
    address += offsets.back();
    return address;
}