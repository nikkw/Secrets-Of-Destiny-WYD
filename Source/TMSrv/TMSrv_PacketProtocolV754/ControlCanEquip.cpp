#include "DLLMain.h"

bool HKD_BASE_CanEquip(st_Mob *player)
{
	INT8 mCLASS = player->Equip[0].EFV2;

	bool retn = true;

	if(mCLASS <= MORTAL)
		retn = false;

	else if(mCLASS > SHARDCORE)
		retn = false;

	return retn;
}