#include <windows.h>
#include "memscan.h"
#include <iostream>

LPVOID FindPattern(const BYTE *lpPattern, LPCSTR szMask)
{
    DWORD dwLength = strlen(szMask);
    DWORD dwImageEnd = IMAGE_BASE + IMAGE_SIZE - dwLength;
    DWORD_PTR i, j;

    // Scan the whole image for the pattern
    for (j = IMAGE_BASE; j < dwImageEnd; ++j)
    {
        // If the pattern is found, return the address at which it begins
        for (i = 0; i < dwLength && (szMask[i] == '?' || *(BYTE*)(j + i) == lpPattern[i]); ++i);
        if (i == dwLength) return (LPVOID)j;
    }

    return NULL;
}

DWORD ReadPointer(DWORD address, std::vector<int> offsets)
{
    FILE* f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    ReadProcessMemory(hProcess, (LPCVOID)address, &address, sizeof(address), NULL);
    std::cout << std::hex << address << std::endl;
    system("pause");
    for (int i = 0; i < offsets.size() - 1; ++i)
    {
        ReadProcessMemory(hProcess, (LPCVOID)(address + offsets.at(i)), &address, sizeof(address), NULL);
        std::cout << std::hex << address << std::endl;
        system("pause");
    }
    address += offsets.back();
    std::cout << std::hex << address << std::endl;
    return address;
}