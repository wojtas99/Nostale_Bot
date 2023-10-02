#include "packet_logger.h"
#include <stdlib.h>

const BYTE SEND_PATTERN[] = { 0x53, 0x56, 0x8B, 0xF2, 0x8B, 0xD8, 0xEB, 0x04 };
const BYTE RECV_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xF0, 0x53, 0x56, 0x57, 0x33, 0xC9, 0x89, 0x4D, 0xF4, 0x89, 0x4D, 0xF0, 0x89, 0x55, 0xFC, 0x8B, 0xD8, 0x8B, 0x45, 0xFC };
const BYTE PACKET_THIS_PATTERN[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x33, 0xD2, 0x89, 0x10 };
const BYTE MOVE_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0x00, 0x53, 0x56, 0x57, 0x66, 0x89, 0x00, 0x00, 0x89, 0x55 };
const BYTE MOVE_THIS_PATTERN[] = { 0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x0E };
const BYTE ATTACK_PATTERN[] = { 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x55 };
const BYTE ATTACK_THIS_PATTERN[] = { 0x88, 0xD5, 0x8B, 0x00, 0x2C };


LPCSTR SEND_MASK = "xxxxxxxx";
LPCSTR RECV_MASK = "xxxxxxxxxxxxx?xx?xx?xxxx?";
LPCSTR PACKET_THIS_MASK = "x????xxx????x????xxxxxx";
LPCSTR MOVE_MASK = "xxxxx?xxxxx??xx";
LPCSTR MOVE_THIS_MASK = "xx????x?x";
LPCSTR ATTACK_MASK = "x?x?x?x????xx";
LPCSTR ATTACK_THIS_MASK = "xxxxx";


LPVOID lpvSendAddy;
LPVOID lpvRecvAddy;
LPVOID lpvPacketThis;
LPVOID lpvMove;
LPVOID lpvMoveThis;
LPVOID lpvAttack;
LPVOID lpvAttackThis;


SafeQueue* qSend;
SafeQueue* qRecv;



#pragma managed(push, off)
void MoveTo(void)
{
    _asm
    {
        PUSH 01
        XOR ECX, ECX
        MOV EDX, 0x00780024 // Waypoint
        MOV EAX, [lpvMoveThis]
        CALL lpvMove
    }
}
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
void AttackMonster(uint32_t monster)
{
    _asm
    {
        MOV CX, 0 // Rodzaj ataku
        MOV EDX, monster // Id potworka
        MOV EAX, [lpvAttackThis]
        MOV EAX, [EAX]
        CALL lpvAttack
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
BOOL StartLogger()
{
    return FindAddresses();
}

BOOL StartLogger(SafeQueue* qSendPackets, SafeQueue* qRecvPackets)
{
    qSend = qSendPackets;

    qRecv = qRecvPackets;

    return FindAddresses() && HookSend() && HookRecv();

}

BOOL StopLogger()
{
    return UnhookSend() && UnhookRecv();
}

BOOL FindAddresses()
{
    //lpvSendAddy = FindPattern(SEND_PATTERN, SEND_MASK); // Address to the start of Send Function.

    //lpvRecvAddy = FindPattern(RECV_PATTERN, RECV_MASK); // Address to the start of Recv Function.

    lpvMove = FindPattern(MOVE_PATTERN, MOVE_MASK); // Address to the start of Move Function.

    lpvAttack = FindPattern(ATTACK_PATTERN, ATTACK_MASK); // Address to the start of Attack Function.

    lpvAttackThis = FindPattern(ATTACK_THIS_PATTERN, ATTACK_THIS_MASK);

   // lpvMoveThis = *(LPVOID*)((DWORD)FindPattern(MOVE_THIS_PATTERN, MOVE_THIS_MASK) - 0x1F); // Move This 
    
   // DWORD pThisPacket = (DWORD_PTR)FindPattern(PACKET_THIS_PATTERN, PACKET_THIS_MASK) + 0x1;
    //lpvPacketThis = (LPVOID)*(DWORD*)pThisPacket;

    return lpvMove && lpvMoveThis && lpvAttack && lpvAttackThis;
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

