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
    /*
    FILE* f;
    LPSTR packet;
    SafeQueue qSend, qRecv;
    EntityList* monsters = (EntityList*)0x0B4D54D0;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    uint32_t x;
    string monsterName;
    cout << "Lista Potworkow na mapie to :" << endl;
    for (int i = 0; i< 303 ; ++i)
    {
        x = (monsters + i)->monsterID;
        x = *(uint32_t*)(x + 0x1BC);
        x = *(uint32_t*)(x + 0x04);
        monsterName = (const char*)x;
        cout << hex << x << " " <<monsterName << endl;
        printf("%d\n", i);
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
    */
    FreeLibraryAndExitThread((HMODULE)lpParameter, GuiMain());
    
}
