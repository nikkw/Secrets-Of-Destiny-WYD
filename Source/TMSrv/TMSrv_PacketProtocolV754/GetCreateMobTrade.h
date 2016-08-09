// ---
// by ptr0x
// ---

#ifndef __FIX_GET_CREATE_MOB_TRADE_H__
#define __FIX_GET_CREATE_MOB_TRADE_H__

#include "../../Common/st_Base.h"

#pragma region Packet Struct v613
typedef struct
{
	PacketHeader Header;

	st_Position Position;

	WORD ClientId; // precisa confirmar

	char CharName[12];

	BYTE Unknow[4];

	struct
	{
		WORD ItemId : 12;
		WORD Sanc : 4;
	}Equips[16];

	BYTE _Unknow[10];

	st_Status Status;

	WORD ___Unknow;

	char StoreName[26];
} p613_GetCreateMobTrade;
#pragma endregion

#pragma region Packet Struct v754
typedef struct
{
	PacketHeader Header;

	st_Position Position;

	WORD ClientId; // precisa confirmar

	char CharName[12];

	DWORD Unknow;

	struct
	{
		WORD ItemId : 12;
		WORD Sanc : 4;
	}Equips[16];

	BYTE _Unknow[34];

	st_Status Status;

	BYTE ___Unknow[45];

	char StoreName[27];
} p754_GetCreateMobTrade;
#pragma endregion

void FixGetCreateMobTrade_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);

#endif // __FIX_GET_CREATE_MOB_TRADE_H__