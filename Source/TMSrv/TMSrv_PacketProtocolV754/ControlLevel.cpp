#include "DLLMain.h"

void __stdcall FixMaxLevel(INT32 clientid, INT16 type)
{
	st_Mob *player = GetMobFromIndex(clientid);

	INT32 table1, table2;		

	if(player->Equip[0].EFV2 < CELESTIAL)	
	{
		table1 = (INT32)(exp_table[player->bStatus.Level]);
		table2 = (INT32)((exp_table)[player->bStatus.Level+1]);
	}
	else
	{
		table1 = (INT32)(exp_table_2[player->bStatus.Level]);
		table2 = (INT32)((exp_table_2)[player->bStatus.Level+1]);
	}		

	__asm
	{
		PUSH EAX
		PUSH ECX
		MOV EAX, table1
		MOV ECX, table2
	}

	if(type == 0)
	{
		__asm{
			MOV DWORD PTR SS:[EBP-01Ch], EAX
			MOV DWORD PTR SS:[EBP-020h], ECX		
		}
	}

	else if(type == 1)
	{
		__asm{
			MOV DWORD PTR SS:[EBP-044h], EAX
			MOV DWORD PTR SS:[EBP-048h], ECX
		}
	}

	else if(type == 2)
	{
		__asm{
			ADD ECX, 01h
			MOV EDX,DWORD PTR SS:[EBP+08h]
			IMUL EDX,EDX,0410h
			MOV DWORD PTR DS:[EDX+015C69D4h], ECX
		}
	}

	else if(type == 3)
	{
		__asm{
			MOV DWORD PTR SS:[EBP-040Ch], EAX
			MOV DWORD PTR SS:[EBP-0410h], ECX
		}

	}

	__asm
	{
		POP EAX
		POP ECX
	}
}