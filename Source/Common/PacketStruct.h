// ---
// by ptr0x
// ---

#ifndef __PACKET_STRUCT_H__
#define __PACKET_STRUCT_H__

#include "BaseStruct.h"

typedef struct
{
	MSG_STANDARD Header;

	STRUCT_POSITION Position;
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

	STRUCT_STATUS Status;

	struct
	{
    	BYTE Type;
    	BYTE MemberType;
	} Spawn;

	BYTE AnctCode[16];
	char Tab[26];

	BYTE Unknow[4];
} MSG_GetCreateMob;

typedef struct
{
	MSG_STANDARD Header;

	STRUCT_STATUS Status;

	BYTE Critical;
	BYTE SaveMana;

	struct
	{
		BYTE Time;
		BYTE Index;
	} Affect[16];

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

	BYTE Unknow[6];
} MSG_SendScore;

typedef struct 
{
	MSG_STANDARD Header;

	DWORD Hold;
	DWORD Exp;
	DWORD Learn;

	WORD pStatus;
	WORD pMaster;
	WORD pSkills;
	WORD Magic; // Unknow

	DWORD Gold;
} MSG_SendEtc;

typedef struct
{
	MSG_STANDARD Header;

	STRUCT_ITEM TradeItem[15];
	BYTE TradeItemSlot[15];

	BYTE Unknow;

	BYTE TradeInfo[8];
} MSG_SendTrade;

typedef struct
{
	MSG_STANDARD Header;

	WORD ClientId;
	WORD AtackCount;

	STRUCT_POSITION PositionInitial;
	STRUCT_POSITION PositionFinal;

	WORD SkillId; // SkillId

	DWORD Offset_26; // Unknow

	BYTE Offset_29[10]; // 0x0...

	DWORD Hold; // Possível hold...

	DWORD AtackInfo;
} MSG_AttackOne;

#endif // __PACKET_STRUCT_H__