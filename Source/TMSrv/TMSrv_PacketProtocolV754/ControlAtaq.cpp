#include "DLLMain.h"

void __stdcall FixProcessAttack(int clientid, int mobid, int *ataqValue)
{
	st_Mob *player = (st_Mob*)GetMobFromIndex(clientid);
	st_Mob *mob = (st_Mob*)GetMobFromIndex(mobid);

	*ataqValue &= 0x7FFF;

	if(*ataqValue > 32000 || player->Status.Level > 1000)
		*ataqValue = 32000;

	int hpDef = 0;
	if(mob->Equip[13].Index == 1936)
		hpDef = 10;
	else if(mob->Equip[13].Index == 1937)
		hpDef = 20;

	if(hpDef != 0) //significa que tá com aquele item que "multiplica" o HP do mob
	{
		int sanc = BASE_GetItemSanc(&mob->Equip[13]);
		int finalAtaq = 0;

		if(sanc < 2)
			sanc = 2;

		sanc *= hpDef;

		finalAtaq = *ataqValue / sanc;

		if(finalAtaq > mob->Status.curHP)
			finalAtaq = mob->Status.curHP;

		mob->Status.curHP -= finalAtaq;			
	}
	else
	{
		bool ControlManaOn = false;
		for(int i = 0; i < 16; i++)
			if(mBuffer[mobid].Affects[i].Index == 18)
			{
			    ControlManaOn = true;
				break;
			}

		if(ControlManaOn)
		{
			int manaspent = (*ataqValue / 10) * 7;
			if(manaspent > mob->Status.curMP)
				manaspent = mob->Status.curMP;

			mob->Status.curMP -= manaspent;
			*ataqValue = (*ataqValue / 10) * 3;
		}
		
		if(*ataqValue > mob->Status.curHP)
			*ataqValue = mob->Status.curHP;

		mob->Status.curHP -= *ataqValue;				
	}
}