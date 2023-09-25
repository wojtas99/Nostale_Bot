//#include <SDKDDKVer.h>
#include "packet_logger.h"


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
    FILE* f;
    LPSTR packet;
    SafeQueue qSend, qRecv;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            cout << "Attack Send" << endl;
            Vestia();
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            cout << "Move Send" << endl;
            Ruch();
        }
    }
    
    StartLogger(&qSend, &qRecv);

    while (true)
    {
        
        if (!qSend.empty())
        {
            packet = qSend.front();
            cout << packet << endl;
            qSend.pop();
        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            cout << "Send" << endl;
            TargetMonster(221170880);
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            cout << "Send" << endl;
            AttackMonster(221170880);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            cout << "Send Move" << endl;
            MoveTo();
        }

    }
    if (f != NULL)
    {
        fclose(f);
    }
    FreeLibraryAndExitThread((HMODULE)lpParameter, NULL);

}
