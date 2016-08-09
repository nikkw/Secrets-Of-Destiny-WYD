#include "DLLMain.h"

void __stdcall FixProcessAttack(int clientid, int mobid, int *ataqValue)
{
	__try
	{
		st_Mob *player = (st_Mob*)GetMobFromIndex(clientid),
			   *mob = (st_Mob*)GetMobFromIndex(mobid);		

		for(int i = 0; i < 16; i++)
			if(mBuffer[clientid].Affects[i].Index == 30 && mobid > 1000)
				*ataqValue += 2000; // Bônus do frango

		int hpDef = 0;
		if(mob->Equip[13].Index == 786)
			hpDef = 2;
		else if(mob->Equip[13].Index == 1936)
			hpDef = 10;
		else if(mob->Equip[13].Index == 1937)
			hpDef = 20;

		if(hpDef) //significa que tá com aquele item que "multiplica" o HP do mob
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

				SendStats(mobid);
			}
		
			if(*ataqValue > mob->Status.curHP)
				*ataqValue = mob->Status.curHP;

			mob->Status.curHP -= *ataqValue;				
		}
	}
	__except(1)
	{
	}
}