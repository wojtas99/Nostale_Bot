#include "packet_logger.h"
#include "Nostale_Entity.h"
#include <string>

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
    //EntityList* monsters = (EntityList*)0x0BDEDC20;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    uint32_t x;
    int i = 1;
    //x = monsters->monsterID;
    string monsterName;;
    cout << "Lista Potworkow na mapie to :" << endl;
    /*
    while (x > 4153968)
    {
        x = *(uint32_t*)(x + 0x1BC);
        x = *(uint32_t*)(x + 0x04);
        monsterName = (const char*)x;
        cout << hex << x << " " <<monsterName << endl;
        x = (monsters + i)->monsterID;
        ++i;
    }
    */
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
