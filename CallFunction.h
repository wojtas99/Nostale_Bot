#pragma once
#include "memscan.h"

BOOL StartBot();
BOOL FindAddresses();

void AttackMonster(uint32_t monster, short skill);
void MoveTo(uint32_t waypoint);
void Rest(void);
void Collect(uint32_t item);
void MovePetPartner(uint32_t waypoint, bool moveOption);
void AttackMonsterPetPartner(uint32_t monster, bool attackOption);

