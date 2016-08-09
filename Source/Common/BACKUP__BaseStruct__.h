// ---
// by ptr0x
// ---

#ifndef __BASE_STRUCT_H__
#define __BASE_STRUCT_H__

#include <Windows.h>

typedef struct
{
	WORD Size;

	BYTE Key;
	BYTE CheckSum;

	WORD PacketId;
	WORD ClientId;

	DWORD TimeStamp;
} MSG_STANDARD;

typedef struct
{
	WORD X;
	WORD Y;
} STRUCT_POSITION;

typedef struct
{
	WORD Index;

	BYTE EF1, EFV1;
	BYTE EF2, EFV2;
	BYTE EF3, EFV3;
} STRUCT_ITEM;

typedef struct
{
	WORD Level;
	WORD Defense;
	WORD Attack;

    BYTE Merchant;
    BYTE ChaosRate;

	WORD maxHP, maxMP;
	WORD curHP, curMP;

	WORD STR, INT;
	WORD DEX, CON;

	BYTE wMaster;
	BYTE fMaster;
	BYTE sMaster;
	BYTE tMaster;
} STRUCT_STATUS;

typedef struct
{
	BYTE Name[16];
    BYTE CapeInfo;
	BYTE Merchant;
    WORD GuildIndex;
    BYTE ClassInfo;

    struct
    {
        BYTE SlowMov : 1;
        BYTE DrainHP : 1;
        BYTE VisionDrop : 1;
        BYTE Evasion : 1;
        BYTE Snoop : 1;
        BYTE SpeedMov : 1;
        BYTE SkillDelay : 1;
        BYTE Resist : 1;
    } AffectInfo;

    WORD QuestInfo;
    DWORD Gold;
    DWORD Exp;

	STRUCT_POSITION LastPosition;

	STRUCT_STATUS bStatus;
	STRUCT_STATUS Status;

    STRUCT_ITEM Equip[16];
	STRUCT_ITEM Inventory[64];

    DWORD Learn;

    WORD StatusPoint,
		 MasterPoint,
		 SkillPoint;

	BYTE Critical;
    BYTE SaveMana;

    BYTE SkillBar[4];

    BYTE GuildMemberType;
    BYTE MagicIncrement;

    BYTE RegenHP,
		 RegenMP;

	BYTE Resist1,
		 Resist2,
		 Resist3,
		 Resist4;

	struct
	{
		WORD Index;
		WORD Master;
		WORD Value;
		WORD Time;
	} Affects[4];

	BYTE Unknow[252];
} STRUCT_MOB;

typedef struct
{
	DWORD AtaqFisico;
	DWORD AtaqMagico;
	DWORD Unknow;
	DWORD Resistencia;
	DWORD Evasao;
} STRUCT_MOUNT;

#endif // __BASE_STRUCT_H__