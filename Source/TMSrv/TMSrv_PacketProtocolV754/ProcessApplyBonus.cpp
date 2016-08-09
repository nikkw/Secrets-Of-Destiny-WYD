#include "DLLMain.h"

INT32 HKD_ProcessClientMessage_ApplyBonus(BYTE *buffer, INT32 clientid)
{
	p277 *p = (p277*)buffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = (st_Mob*)GetMobFromIndex(cId);
 
	if(!p->Info)
	{
		if(player->bStatus.Mastery[p->Info] >= 200)
			return 0;
 
		return 1;
	}
 
	if(player->Equip[0].EFV2 >= CELESTIAL)
	{
		if(player->bStatus.Mastery[p->Info] < 200)
			return 1;
	}
 
	int Have = player->Learn & (1 << (8 * p->Info - 1));

	if(Have)
	{
		if(player->bStatus.Mastery[p->Info] >= 255)
		{
			SendClientMessage(cId, "Limite máximo de pontos.");

			//SendLog(Users[cId].Username, "%s tentou distribuir pontos além do limite no mastery %d.", player->Name, p->Info);

			return 0;
		}
	} 
	else 
	{
		if(player->bStatus.Mastery[p->Info] >= 200)
		{
			SendClientMessage(cId, "Limite máximo de pontos");

			//SendLog(Users[cId].Username, "%s tentou distribuir pontos além do limite no mastery %d.", player->Name, p->Info);

			return 0;
		}
	}

	return 1;
}