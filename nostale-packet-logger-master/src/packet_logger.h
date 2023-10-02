#pragma once
#include <iostream>
#include <windows.h>

#include "safequeue.h"
#include "hooking.h"
#include "memscan.h"
#include "nostale_string.h"
using namespace std;


BOOL StartLogger(SafeQueue* sqSendPackets, SafeQueue* sqRecvPackets);
BOOL StartLogger();
BOOL StopLogger();
void SendPacket(LPCSTR szPacket);
void ReceivePacket(LPCSTR szPacket);
void AttackMonster(uint32_t monster);
void MoveTo();

BOOL FindAddresses();
BOOL HookSend();
BOOL HookRecv();
BOOL UnhookSend();
BOOL UnhookRecv();
