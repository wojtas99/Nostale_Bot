#include "packet_logger.h"
#include <stdlib.h>

const BYTE SEND_PATTERN[] = { 0x53, 0x56, 0x8B, 0xF2, 0x8B, 0xD8, 0xEB, 0x04 };
const BYTE RECV_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xF0, 0x53, 0x56, 0x57, 0x33, 0xC9, 0x89, 0x4D, 0xF4, 0x89, 0x4D, 0xF0, 0x89, 0x55, 0xFC, 0x8B, 0xD8, 0x8B, 0x45, 0xFC };
const BYTE PACKET_THIS_PATTERN[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x33, 0xD2, 0x89, 0x10 };

LPCSTR SEND_MASK = "xxxxxxxx";
LPCSTR RECV_MASK = "xxxxxxxxxxxxx?xx?xx?xxxx?";
LPCSTR PACKET_THIS_MASK = "x????xxx????x????xxxxxx";

LPVOID lpvSendAddy;
LPVOID lpvRecvAddy;
LPVOID lpvPacketThis;

LPVOID monsterTargetThis = (LPVOID)0x0072DB64;
LPVOID targetMonster = (LPVOID)0x006BE17C;

LPVOID attackMonster = (LPVOID)0x006BD5FC;
LPVOID monsterAttackThis = (LPVOID)0x0072DB64;
LPVOID monsterAttackThis2 = (LPVOID)0x0072B14C;


LPVOID sendMessage = (LPVOID)0x006BEC80;
LPVOID xd = (LPVOID)0x0072DB64;
LPVOID moveFunc = (LPVOID)0x004B2084;

SafeQueue* qSend;
SafeQueue* qRecv;


LPVOID mapThis = (LPVOID)0x0072EB64;
LPVOID mapMove = (LPVOID)0x006BDE94;

//LPVOID mapThis2 = *(LPVOID*)0X008BD524;
LPVOID mapMove2 = (LPVOID)0X00550328;



LPVOID atak = (LPVOID)0x00408F20;
LPVOID atak2 = (LPVOID)0x0045D860;

LPVOID ruch = (LPVOID)0x004D0E20;

LPVOID ruch2 = (LPVOID)0x00464070;
//004EE92C
LPVOID postac = (LPVOID)0x0019EC8C;
void Ruch()
{
    /*
MOV EAX, 0X10E
PUSH 00
PUSH 00
PUSH 01
call ruch
*/
    DWORD z = (DWORD)0x07;
    DWORD x = (DWORD)0x3DC;
    DWORD y = (DWORD)0x405;
    _asm
    {
        MOV EDX, z
        PUSH EDX
        MOV EAX, x
        PUSH EAX
        MOV ECX, y
        PUSH ECX
        CALL ruch2
    }
    system("pause");
}
void Vestia()
{
    _asm
    {
        PUSH EAX
        MOV EAX, 0X40005075
        CALL atak
    }
}


void MoveTo()
{
    DWORD wpt = (DWORD)0x00780024;
    //        MOV EAX, [EAX]
    //MOV EAX, [mapThis2]
    _asm
    {
        PUSH 01
        XOR ECX, ECX
        MOV EDX, wpt// Waypoint.

        CALL mapMove2
    }
    /*
    _asm
    {
        MOV EAX, [mapThis]
        MOV EAX, [EAX]
        MOV CX, 0x0077
        MOV DX, 0X0020
        CALL mapMove
    }
    */
}


#pragma managed(push, off)
void CustomSend()
{
    LPSTR szPacket;
    _asm
    {
        MOV szPacket, EDX
    }

    qSend->push(szPacket);
}

void CustomRecv()
{
    LPSTR szPacket;

    _asm
    {
        MOV szPacket, EDX
    }

    qRecv->push(szPacket);
}

void SendPacket(LPCSTR szPacket)
{
    NostaleStringA str(szPacket);
    char* packet = str.get();
    _asm
    {
        MOV EAX, DWORD PTR DS : [lpvPacketThis]
        MOV EAX, DWORD PTR DS : [EAX]
        MOV EAX, DWORD PTR DS : [EAX]
        MOV EDX, packet
        CALL lpvSendAddy
    }
}
void TargetMonster(uint32_t monster)
{
    _asm
    {
        MOV EDX, monster
        MOV EAX, [monsterTargetThis]
        MOV EAX, [EAX]
        CALL targetMonster
    }
}
void AttackMonster(uint32_t monster)
{
    _asm
    {
        //        MOV EAX, [0x19FC7C] // Rodzaj Ataku
        MOV CX, 0 // Rodzaj ataku
        MOV EAX, [monsterAttackThis2]
        MOV EAX, [EAX]
        MOV EDX, monster // Id potworka
        MOV EAX, [monsterAttackThis]
        MOV EAX, [EAX]
        CALL attackMonster
    }
}

void SendMessagex(LPCSTR szPacket)
{
    NostaleStringW str(L"Mocne");
    const wchar_t* packet = str.get();
    _asm
    {
        MOV EDX, packet
        MOV EAX, DWORD PTR DS : [xd]
        MOV EAX, DWORD PTR DS : [EAX]
        CALL sendMessage
    }
}
void ReceivePacket(LPCSTR szPacket)
{
    NostaleStringA str(szPacket);
    char* packet = str.get();

    _asm
    {
        MOV EAX, DWORD PTR DS : [lpvPacketThis]
        MOV EAX, DWORD PTR DS : [EAX]
        MOV EAX, DWORD PTR DS : [EAX]
        MOV EAX, [EAX + 0x34]
        MOV EDX, packet
        CALL lpvRecvAddy
    }
}
#pragma managed(pop)

BOOL StartLogger(SafeQueue* qSendPackets, SafeQueue* qRecvPackets)
{
    qSend = qSendPackets;

    qRecv = qRecvPackets;

    return FindAddresses() && HookSend() && HookRecv();

   // return FindAddresses() && HookRecv();
}

BOOL StopLogger()
{

    return UnhookRecv();
    return UnhookSend() && UnhookRecv();
}

BOOL FindAddresses()
{
    lpvSendAddy = FindPattern(SEND_PATTERN, SEND_MASK); // Address to the start of Send Function.

    lpvRecvAddy = FindPattern(RECV_PATTERN, RECV_MASK); // Address to the start of Recv Function.

    DWORD pThisPacket = (DWORD_PTR)FindPattern(PACKET_THIS_PATTERN, PACKET_THIS_MASK) + 0x1;
    lpvPacketThis = (LPVOID)*(DWORD*)pThisPacket;

    return lpvSendAddy && lpvRecvAddy && lpvPacketThis;
}

BOOL HookSend()
{
    return HookFunction(lpvSendAddy, CustomSend);
}

BOOL HookRecv()
{
    return HookFunction(lpvRecvAddy, CustomRecv);
}

BOOL UnhookSend()
{
    return UnhookFunction(lpvSendAddy);
}

BOOL UnhookRecv()
{
    return UnhookFunction(lpvRecvAddy);
}

