// ---
// by ptr0x
// ---

#ifndef __PACKET_CONTROL_H__
#define __PACKET_CONTROL_H__

#include <Windows.h>

#include "GetCreateMob.h"
#include "SendScore.h"
#include "SendEtc.h"
#include "GetCreateMobTrade.h"
#include "SendAffect.h"
#include "AddExp.h"
#include "SendTrade.h"
#include "ExitParty.h"
#include "PE_Patch.h"

#define SERVER_SIDE 0
#define CLIENT_SIDE 1

bool SendPacketControl(BYTE* newPacketBuffer, PacketHeader* oldPacketBuffer, int clientId);
bool RecvPacketControl(PacketHeader* packetBuffer, int clientId);
void __stdcall HKD_CorrectRecvPacket(UINT8* szBuffer, INT32 FixClientID);

#endif // __PACKET_CONTROL_H__