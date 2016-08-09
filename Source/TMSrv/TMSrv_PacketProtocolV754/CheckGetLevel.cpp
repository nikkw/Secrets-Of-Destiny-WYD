#include "DLLMain.h"

static const UINT8 Adds[][2][6] = {
	{
		{EF_SANC, 3, EF_DAMAGE,   30, EF_AC,         30},
		{EF_SANC, 3, EF_MAGIC,    10, EF_AC,         30}
	},
	{
		{EF_SANC, 3, EF_DAMAGE,   30, EF_SPECIALALL, 18},
		{EF_SANC, 3, EF_DAMAGE,   24, EF_MAGIC,      10}
	},
	{
		{EF_SANC, 3, EF_ATTSPEED, 18, EF_HP,         50},
		{EF_SANC, 3, EF_MAGIC,    12, EF_AC,         25}
	},
	{
		{EF_SANC, 3, EF_DAMAGE,   30, EF_AC,         30},
		{EF_SANC, 3, EF_MAGIC,    10, EF_AC,         30}
	},
	{
		{EF_SANC, 3, EF_DAMAGE,   30, EF_AC,         30},
		{EF_SANC, 3, EF_MAGIC,    10, EF_AC,         30}
	}
};

void ItensPerLevel(int clientid) 
{
	int SlotPlace = GetFirstSlot(clientid, 0, CARGO); 

	st_Mob *player = GetMobFromIndex(clientid);

	if(SlotPlace == -1)
	{
		SendClientMessage(clientid, "Você não possui espaço no banco para receber itens.");

		//SendLog(Users[clientid].Username, "%s não executou ItensPerLevel por conta de espaço no baú.", player->Name);

		return;
	}	

	int level = player->bStatus.Level, build = player->bStatus.STR + player->bStatus.DEX > player->bStatus.INT? 0: 1;

	st_Item Item;
	memset(&Item, 0, sizeof st_Item);

	for(int i = 0; i < sizeof(ClassLevel) / sizeof INT16; i++)
	{
		if(wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.ItensReceived[i])
			continue;

		int ActualLevel = ClassLevel[i];

		if(level < ActualLevel)
			continue;
		else 
		    memset(&Item, 0, sizeof st_Item);

		if(ActualLevel == 155 || ActualLevel == 255)
			Item.Index = Armas[player->ClassInfo][ActualLevel == 155? 0 : 1];
		else
		{
			Item.Index = szItens[player->ClassInfo][i];

			if(Item.Index != 2368)
				memcpy(&Item.Effect, Adds[Pos[i]][build], 6);
			else
			{
				Item.EF1  = 10;
				Item.EFV1 = 10;
				Item.EF2  = 50;
				Item.EFV2 = 20;
				Item.EF3  = 10;
				Item.EFV3 = 10;
			}
		}

		memcpy(&Users[clientid].Storage.Item[SlotPlace], &Item, sizeof st_Item);

		SendItem(clientid, CARGO, SlotPlace, &Item);

		SendClientMsg(clientid, "!Item %s acaba de chegar.", ItemList[Item.Index].Name);

		//SendLog(Users[clientid].Username, "%s recebeu o item %s no nível %d.", player->Name, ItemList[Item.Index].Name, player->Status.Level);

		wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.ItensReceived[i] = true;
		// Não vou dar break pois pode acontecer de no ultimo level o item não ter chegado por conta de não haver espaço
	}
}

INT32 __stdcall HKD_CheckGetLevel_FixClass(st_Mob &player)
{	
	if(player.Equip[0].EFV2 <= 2)
	{
		if(player.bStatus.Level >= 399)
			return FALSE;
	}

	else if(player.Equip[0].EFV2 > 2)
	{
		if(player.bStatus.Level >= 199)
			return FALSE;
	}

	return TRUE;
}

void __stdcall HKD_ControlCheckGetLevel(int mPointer, short *mPoints)
{	
	st_Mob *player = (st_Mob*)mPointer;

	int clientid = (((int)player - 0x15C69B8) / 0x410);		

	int level = player->Status.Level;

	//SendLog(Users[clientid].Username, "%s level up para %d.", player->Name, level);

	switch(player->Equip[0].EFV2)
	{
		case MORTAL:
		{
			*mPoints += 5;

			if(level >= 254)
				*mPoints += 5;
			if(level >= 299)
				*mPoints += 10;
			if(level >= 355)
				*mPoints -= 8;

			ItensPerLevel(clientid);

			break;
		}

		case ARCH:
		{
			*mPoints += 6;

			if(level >= 355)
				*mPoints += 6;

			break;
		}

		case CELESTIAL: case SCELESTIAL: case HARDCORE: case SHARDCORE:
		{
			*mPoints += 10;

			if(player->Equip[0].EFV2 == HARDCORE || player->Equip[0].EFV2 == SHARDCORE)
				*mPoints += 2;
				
			if((wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.SubCeleMade || player->Equip[0].EFV2 >= CELESTIAL) && player->Equip[1].Index >= 3500 && player->Equip[1].Index <= 3507)
			{
				if(player->bStatus.Level >= 120 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add120)
				{
					if(PutAddOnItem(&player->Equip[1], EF_AC, EF_HP, 30, 40))
					{
						wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add120 = TRUE;

						SendItem(clientid, EQUIP, 1, &player->Equip[1]);	
						//SendLog(Users[clientid].Username, "%s recebeu add 30/40 na %s.", player->Name, ItemList[player->Equip[1].Index].Name);
					}
				}

				if(player->bStatus.Level >= 150 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add151)
				{
					if(PutAddOnItem(&player->Equip[1], EF_AC, EF_HP, 35, 50))
					{
						wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add151 = TRUE;

						SendItem(clientid, EQUIP, 1, &player->Equip[1]);
						//SendLog(Users[clientid].Username, "%s recebeu add 35/50 na %s.", player->Name, ItemList[player->Equip[1].Index].Name);
					}
				}

				if(player->bStatus.Level >= 180 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add180)
				{
					if(PutAddOnItem(&player->Equip[1], EF_AC, EF_HP, 45, 60))
					{
						wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add180 = TRUE;

						SendItem(clientid, EQUIP, 1, &player->Equip[1]);
						//SendLog(Users[clientid].Username, "%s recebeu add 45/60 na %s.", player->Name, ItemList[player->Equip[1].Index].Name);
					}
				}

				if(player->bStatus.Level >= 198 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add199)
				{
					if(PutAddOnItem(&player->Equip[1], EF_AC, EF_HP, 50, 70))
					{
						wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Add199 = TRUE;

						SendItem(clientid, EQUIP, 1, &player->Equip[1]);
						//SendLog(Users[clientid].Username, "%s recebeu add 50/70 na %s.", player->Name, ItemList[player->Equip[1].Index].Name);
					}
				}
			}
				

			if(level == 189)
				*mPoints += 290;

			break;	
		}

		default:
			*mPoints = 0;		
			break;
	}					

	//SendLog(Users[clientid].Username, "%s recebeu %d pontos.", player->Name, *mPoints);

	BASE_GetHpMp(player);
	GetCurrentScore(clientid);

	player->bStatus.curHP = player->bStatus.maxHP;
	player->bStatus.curMP = player->bStatus.maxMP;

	player->Status.curHP  = player->Status.maxHP;
	player->Status.curMP  = player->Status.maxMP;

	Users[clientid].Potion.CountMp = player->Status.maxMP;
	Users[clientid].Potion.CountHp = player->Status.maxHP;
		
	SendScore(clientid);
	SendStats(clientid);
	SendEtc(clientid);
	SendEquip(clientid);
		
	BYTE packet[108]; 

	BASE_GetCreateMob(clientid, (BYTE*)&packet);
	GridMulticast(clientid, player->TargetX, player->TargetY, (void*)&packet);

	SendCreateMob(clientid, clientid, 1);		
}