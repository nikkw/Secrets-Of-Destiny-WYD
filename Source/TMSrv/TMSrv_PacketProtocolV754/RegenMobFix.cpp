#include "DLLMain.h"

INT16 __stdcall HKD_RegenMob_IncrementRegen(INT32 clientid, INT32 hp)
{
	__try
	{
		st_Mob *player = (st_Mob*)GetMobFromIndex(clientid);

		switch(player->Equip[0].EFV2)
		{
		case 1:
			hp += 200;
			break;

		case 2:
			hp += 400;
			break;

		case 3: case 4: case 5:
			hp += 800;
			break;
		}

		hp += 200;
	
		if(player->Status.Level > 1000)
			hp = player->Status.maxHP - 1;

		//tem que ficar no final	
		if(hp > player->Status.maxHP)
			hp = player->Status.maxHP;	

		return hp;
	}
	__except(1)
	{
	}
}



