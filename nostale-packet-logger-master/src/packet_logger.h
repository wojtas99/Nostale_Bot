#pragma once
#include <iostream>
#include <windows.h>

#include "safequeue.h"
#include "hooking.h"
#include "memscan.h"
#include "nostale_string.h"
using namespace std;


BOOL StartLogger(SafeQueue* sqSendPackets, SafeQueue* sqRecvPackets);
BOOL StopLogger();
void SendPacket(LPCSTR szPacket);
void ReceivePacket(LPCSTR szPacket);
void SendMessagex(LPCSTR szPacket);
void TargetMonster(uint32_t monster);
void AttackMonster(uint32_t monster);
void MoveTo();
void Vestia();
void Ruch();

BOOL FindAddresses();
BOOL HookSend();
BOOL HookRecv();
BOOL UnhookSend();
BOOL UnhookRecv();
