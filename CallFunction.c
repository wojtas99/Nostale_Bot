#include "CallFunction.h"

const BYTE MOVE_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0x00, 0x53, 0x56, 0x57, 0x66, 0x89, 0x00, 0x00, 0x89, 0x55 };
const BYTE MOVE_THIS_PATTERN[] = { 0x80, 0x26, 0x00, 0x00, 0x00, 0x00 , 0x00, 0x00, 0x58 };

const BYTE ATTACK_PATTERN[] = { 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x55};
const BYTE ATTACK_THIS_PATTERN[] = { 0x88, 0xD5, 0x8B, 0x00, 0x2C };

const BYTE COLLECT_PATTERN[] = { 0x53, 0x56, 0x57, 0x55, 0x8B, 0xF2, 0x8B, 0xF8, 0x33, 0xDB, 0x8B , 0xC7 };
const BYTE COLLECT_THIS_PATTERN[] = { 0x80, 0x26, 0x00, 0x00, 0x00, 0x00 , 0x00, 0x00, 0x58};


LPCSTR SEND_MASK = "xxxxxxxx";
LPCSTR RECV_MASK = "xxxxxxxxxxxxx?xx?xx?xxxx?";
LPCSTR PACKET_THIS_MASK = "x????xxx????x????xxxxxx";

LPCSTR MOVE_MASK = "xxxxx?xxxxx??xx";
LPCSTR MOVE_THIS_MASK = "xx??????x";

LPCSTR ATTACK_MASK = "x?x?x?x????xx";
LPCSTR ATTACK_THIS_MASK = "xxxxx";

LPCSTR COLLECT_MASK = "xxxxxxxxxxxx";
LPCSTR COLLECT_THIS_MASK = "xx??????x";

LPVOID lpvMove;
LPVOID lpvMoveThis;
LPVOID lpvAttack;
LPVOID lpvAttackThis;
LPVOID lpvCollect;
LPVOID lpvCollectThis;
#pragma managed(push, off)
void MoveTo(uint32_t waypoint)
{
    _asm
    {
        PUSH 01
        XOR ECX, ECX
        MOV EDX, waypoint // Waypoint
        MOV EAX, [lpvMoveThis]
        CALL lpvMove
    }
}

void AttackMonster(uint32_t monster, short skill)
{
    _asm
    {
        MOV CX, skill // Rodzaj ataku
        MOV EDX, monster // Id potworka
        MOV EAX, [lpvAttackThis]
        CALL lpvAttack
    }
}
#pragma managed(pop)
BOOL StartBot()
{
    return FindAddresses();
}

BOOL FindAddresses()
{
    lpvAttack = FindPattern(ATTACK_PATTERN, ATTACK_MASK); // Address to the start of Attack Function.

    lpvAttackThis = *(LPVOID*)FindPattern(ATTACK_THIS_PATTERN, ATTACK_THIS_MASK); // Attack This.

    lpvMove = FindPattern(MOVE_PATTERN, MOVE_MASK); // Address to the start of Move Function.

    //lpvMoveThis = *(LPVOID*)FindPattern(MOVE_THIS_PATTERN, MOVE_THIS_MASK); // Move This.
    lpvMoveThis = (LPVOID)0X008BD524;

    return lpvMove && lpvMoveThis && lpvAttack && lpvAttackThis;
}

