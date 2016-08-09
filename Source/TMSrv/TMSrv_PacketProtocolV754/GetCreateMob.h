// ---
// by ptr0x, supernov4
// ---

#ifndef __FIX_GET_CREATE_MOB_H__
#define __FIX_GET_CREATE_MOB_H__

#include "../NativeFunctions.h"
#include "DLLMain.h" 

#pragma region Packet Struct v613
typedef struct
{
	PacketHeader Header;	

	st_Position Position;
	WORD ClientId;
	char Name[12];

	BYTE ChaosPoints;
    BYTE CurrentKill;
    WORD TotalKill;

	struct // Item equip
	{
    	BYTE ItemID;
    	BYTE Sanc;
	} ItemEff[16];

	struct // Buffs
	{
    	BYTE Time;
    	BYTE Index;
	} Affect[4];
	
	WORD GuildIndex;

	st_Status Status;

	struct
	{
    	BYTE Type;
    	BYTE MemberType;
	} Spawn;

	BYTE Unknow[2];
} p613_GetCreateMob;
#pragma endregion

#pragma region Packet Struct v754
typedef struct
{
	PacketHeader Header;

	st_Position Position;
	WORD ClientId;
	char Name[12];

	BYTE ChaosPoints;
    BYTE CurrentKill;
    WORD TotalKill;

	struct // Item equip
	{
    	BYTE ItemID;
    	BYTE Sanc;
	} ItemEff[16];

	struct // Buffs
	{
    	BYTE Time;
    	BYTE Index;
	} Affect[16];
	
	WORD GuildIndex;

	st_Status Status;

	struct
	{
    	BYTE Type;
    	BYTE MemberType;
	} Spawn;

	BYTE AnctCode[16];
	char Tab[26];

	BYTE Unknow[4];
} p754_GetCreateMob;
#pragma endregion

void FixGetCreateMob_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);
void FixRefreshItens_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);

#endif // __FIX_GET_CREATE_MOB_H__