#pragma once
#include <windows.h>

extern int GuiMain();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved);
DWORD WINAPI HackThread(LPVOID lpParameter);
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, HackThread, hModule, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;
}

DWORD WINAPI HackThread(LPVOID lpParameter)
{

    FreeLibraryAndExitThread((HMODULE)lpParameter, GuiMain());
}
