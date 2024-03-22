#include "CallFunction.h"
#include <iostream>

const BYTE MOVE_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0x00, 0x53, 0x56, 0x57, 0x66, 0x89, 0x00, 0x00, 0x89, 0x55 };
const BYTE MOVE_THIS_PATTERN[] = { 0xE0, 0x00, 0x00, 0x0E, 0x00, 0x4A };

const BYTE ATTACK_PATTERN[] = { 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x55};
const BYTE ATTACK_THIS_PATTERN[] = { 0x48, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x8C };


const BYTE COLLECT_PATTERN[] = { 0x55, 0x8B, 0xEC, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x53, 0x56, 0x8B, 0XD9, 0X8B, 0xF2, 0X33, 0XC0, 0X55, 0X68, 0X00, 0X00, 0X00, 0X00, 0X64, 0XFF, 0X00, 0X64, 0X89, 0X00, 0XA1 };
const BYTE COLLECT_THIS_PATTERN[] = { 0x58, 0x46, 0x8C, 0x00, 0xFC };

const BYTE REST_PATTERN[] = { 0x55, 0x8B, 0xEC, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x49, 0x75, 0x00, 0x51, 0x53, 0x56, 0x57, 0x33, 0xC0 };

const BYTE MOVE_PET_PATTERN[] = { 0x55, 0X8B, 0XEC, 0X83, 0XC4,  0X00, 0X53, 0X56, 0X57, 0X8B, 0XF9, 0X89, 0X55, 0X00, 0X8B, 0XD8, 0XC6, 0X45 };

LPCSTR MOVE_MASK = "xxxxx?xxxxx??xx";
LPCSTR MOVE_THIS_MASK = "x??x?x";

LPCSTR ATTACK_MASK = "x?x?x?x????xx";
LPCSTR ATTACK_THIS_MASK = "x?xxx??x";

LPCSTR COLLECT_MASK = "xxxx?x?x?x?xxxxxxxxxx????xx?xx?x";
LPCSTR COLLECT_THIS_MASK = "xxxxx";

LPCSTR REST_MASK = "xxxx????x?x?xx?xxxxxx";

LPCSTR MOVE_PET_MASK = "xxxxx?xxxxxxx?xxxx";

LPVOID lpvMove;
LPVOID lpvMoveThis;

LPVOID lpvAttack;
LPVOID lpvAttackThis;

LPVOID lpvCollect;
LPVOID lpvCollectThis;

LPVOID lpvMovePetPartner;

LPVOID lpvRest;
#pragma managed(push, off)
void MoveTo(uint32_t waypoint)
{
    
    _asm
    {
        PUSH 01
        XOR ECX, ECX
        MOV EDX, waypoint
        MOV EAX, [lpvMoveThis]
        MOV EAX, [EAX]
        CALL lpvMove
    }
}
void MovePetPartner(uint32_t waypoint, bool moveOption)
{
    if (moveOption) // 1 - Partner move || 0 - Pet move
    {
        DWORD partner = *(DWORD*)ReadPointer(0x004F4F04, { 0x118, 0x4, 0x38, 0x168 });
        _asm
        {
            PUSH 01
            PUSH 01
            XOR ECX, ECX
            MOV EDX, waypoint
            MOV EAX, partner
            call lpvMovePetPartner
        }
    }
    else
    {
        DWORD pet = *(DWORD*)ReadPointer(0x004F4F04, { 0x118, 0x4, 0x38, 0x16C });
        _asm
        {
            PUSH 01
            PUSH 01
            XOR ECX, ECX
            MOV EDX, waypoint
            MOV EAX, pet
            call lpvMovePetPartner
        }
    }
}
void AttackMonster(uint32_t monster, short skill)
{
    _asm
    {
        MOV CX, skill
        MOV EDX, monster
        MOV EAX, [lpvAttackThis]
        MOV EAX, [EAX]
        CALL lpvAttack
    }
}
void Rest(void)
{
    _asm
    {
        MOV EAX, 0xE3250B0
        CALL lpvRest
    }
}
void Collect(uint32_t item)
{
    
    DWORD characterPointer = ReadPointer(0x360E7C, { 0x0 });
    _asm
    {
        MOV EAX, [lpvCollectThis]
        MOV EAX, [EAX]
        MOV ECX, characterPointer;
        MOV EDX, [ECX]
        MOV ESI, item
        MOV EDX, ESI
        CALL lpvCollect
    }
}
#pragma managed(pop)
BOOL StartBot()
{
    return FindAddresses();
}

BOOL FindAddresses()
{
    
    lpvAttack = FindPattern(ATTACK_PATTERN, ATTACK_MASK);

    lpvAttackThis = (LPVOID)0x008F4904;

    lpvMove = FindPattern(MOVE_PATTERN, MOVE_MASK);

    lpvMoveThis = (LPVOID)0x008F4904;

    lpvCollect = FindPattern(COLLECT_PATTERN, COLLECT_MASK);

    lpvCollectThis = (LPVOID)0x00765EA8;

    lpvMovePetPartner = FindPattern(MOVE_PET_PATTERN, MOVE_PET_MASK);

    return lpvMove && lpvMoveThis && lpvAttack && lpvAttackThis && lpvCollect && lpvCollectThis && lpvMovePetPartner;
}

