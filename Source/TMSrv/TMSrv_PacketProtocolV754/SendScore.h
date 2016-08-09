// ---
// by ptr0x
// ---

#ifndef __FIX_SEND_SCORE_H__
#define __FIX_SEND_SCORE_H__

#include "../NativeFunctions.h"
#include "DLLMain.h"

#pragma region Packet Struct v613
typedef struct
{
	PacketHeader Header;

	st_Status Status;

	BYTE Critical;
	BYTE SaveMana;

	struct
	{
		WORD Time : 8;
		WORD Index : 8;
	} Affect[4];

	BYTE GuildMemberType,
		 MagicIncrement;

	BYTE RegenHP,
		 RegenMP;

	BYTE Resist1;
	BYTE Resist2;
	BYTE Resist3;
	BYTE Resist4;

	WORD CurrHP;
	WORD CurrMP;

	BYTE Unknow[2];
} p613_SendScore;
#pragma endregion

#pragma region Packet Struct v754
typedef struct
{
	PacketHeader Header; // 12

	st_Status Status; // 40

	BYTE Critical;
	BYTE SaveMana;

	struct
	{
		BYTE Time;
		BYTE Index;
	} Affect[16];

	BYTE GuildMemberType,
		 GuildIndex;

	BYTE RegenHP,
		 RegenMP;

	BYTE Resist1;
	BYTE Resist2;
	BYTE Resist3;
	BYTE Resist4;

	WORD CurrHP;
	WORD CurrMP;
	
	BYTE MagicIncrement;
	BYTE Unk[5];
} p754_SendScore;
#pragma endregion

void FixSendScore_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);

#endif // __FIX_SEND_SCORE_H__