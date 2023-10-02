#pragma once
#include <vector>
#define IMAGE_BASE 0x00400000   // Default location; NosTale doesn't use ASLR
#define IMAGE_SIZE 0x0050F000   // End of the location of scan.

LPVOID FindPattern(const BYTE *lpPattern, LPCSTR szMask);
DWORD ReadPointer(DWORD address, std::vector<int> offsets);