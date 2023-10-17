#pragma once
#include <windows.h>
#include <vector>
LPVOID FindPattern(const BYTE *lpPattern, LPCSTR szMask);
DWORD ReadPointer(DWORD address, std::vector<int> offsets);