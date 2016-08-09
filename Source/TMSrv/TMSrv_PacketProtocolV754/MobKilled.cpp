#include "MobKilled.h"

void HKD_MobKilled_DropGold(INT32 index, UINT32 gold)
{
	st_Mob *mob = GetMobFromIndex(index);

	UINT32 xgold = mob->Gold + gold;

	if(xgold > 2000000000)
	{
		UINT32 zgold = 2000000000 - mob->Gold;
		if(zgold > 0)
		{
			if(gold > zgold)
				gold = zgold;
		}
		else
		{
			// Atingiu o limite máximo de gold
			return ;
		}
	}

	mob->Gold += gold;		

	SendClientSignalParm(index, index, 0x3AF, mob->Gold);
}

void __stdcall HKD_MobKilled_EventDead(INT32 killed, INT32 killer)
{
	if(killed < 0 || killed > 30000 || killer < 0 || killer > 30000)
		return;

	st_Mob *killler = GetMobFromIndex(killer),
		   *killled = GetMobFromIndex(killed);

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	if(killed < 1000 && killer < 1000)
	{
		// Caso do pvp
		// Pode ser usado para fazer quando o HC morrer virar Mortal
		// Ou coisas do tipo, depende muito do que você quer

		if((DayOfWeek() == Terça || DayOfWeek() == Quinta) && now->tm_hour == 21 && now->tm_min < 30)
		{
			if (killled->PosX >= xX && killler->PosX >= xX && killled->PosX <= XX && killler->PosX <= XX &&
				killled->PosY >= yY && killler->PosY >= yY && killled->PosY <= YY && killler->PosY <= YY &&
				killled->GuildIndex && killler->GuildIndex && killled->GuildIndex != killler->GuildIndex)
			{
				Guilds[killler->GuildIndex].FAME++;
				Guilds[killler->GuildIndex].WarPoints++;

				wdBuffer[killer].Chars[wdBuffer[killer].Ingame.LoggedMob].Fame++;

				char szMsg[120];

				sprintf(szMsg, "!Jogador %s acaba de ser morto por %s !!", killled->Name, killler->Name);

				SendWarInfo(szMsg);
			}
		}

		if(killled->Equip[0].EFV2 >= HARDCORE && BASE_GetVillage(killled->LastX, killled->LastY) == 5)
		{
			if(killled->Equip[13].Index == 769)// Com nyerds não baixa refinação.
				return;

			else if(GetItemSanc(&killled->Equip[1]))
			{
				RefinarItemMais(&killled->Equip[1], -1);

				SendItem(killed, EQUIP, 1, &killled->Equip[1]);
				
				return;
			}
			else
			{
				killled->Equip[0].Index = 1; // Seta a face como de mortal
				killled->Equip[0].EFV2 = MORTAL; // Seta a classe como de mortal
				killled->Equip[0].EFV3 = killled->Equip[0].Index; // Só por precaução

				killled->ClassInfo     = 0; // Seta as skills como de mortal
				killled->Learn         = 0; // Zera as skills
				killled->bStatus.Level = 0; // zera os stats \/
				killled->bStatus.STR   = 0;
				killled->bStatus.INT   = 0;
				killled->bStatus.DEX   = 0;
				killled->bStatus.CON   = 0;
				killled->Exp           = 0;
				killled->QuestInfo     = 0;
				killled->StatusPoint   = 0;
				killled->MasterPoint   = 0;
				killled->SkillPoint    = 0;

				memset(&killled->Equip[1], 0x0, sizeof(st_Item)); // Apaga a cythera de HC
				memset(&killled->Equip[15], 0x0, sizeof(st_Item)); // Apaga a capa de HC
				memset(&killled->SkillBar, 0x0, sizeof(INT8) * 4); // Zera a skillbar1
				memset(&wdBuffer[killed].Chars[wdBuffer[killed].Ingame.LoggedMob].SkillBar2, 0x0, sizeof(INT8) * 16);
				memset(&wdBuffer[killed].Chars[wdBuffer[killed].Ingame.LoggedMob].Quests, 0x0, sizeof(pQuestInfo));

				for(int i = 0; i < 4; i++)
					killled->bStatus.Mastery[i] = 0;

				BASE_GetBonusSkillPoint(killled);
				BASE_GetBonusScorePoint(killled);
				GetCurrentScore(killed);
				BASE_GetHpMp(killled);
		
				SendScore(killed);
				SendStats(killed);
				SendEtc(killed);
				SendEquip(killed);

				SendItem(killed, EQUIP, 0, &killled->Equip[0]);
				SendItem(killed, EQUIP, 0, &killled->Equip[1]);
				SendItem(killed, EQUIP, 0, &killled->Equip[15]);
		
				BYTE packet[108]; 

				BASE_GetCreateMob(killed, (BYTE*)&packet);
				GridMulticast(killed, killled->TargetX, killled->TargetY, (void*)&packet);

				SendCreateMob(killed, killed, 1);
			}
		}

		if(DayOfWeek() == Domingo && now->tm_hour == 21)
		{
			for(int e = 0; e < 4; e++)
			{
				if(killled->GuildIndex == War.WarIndexs[e][0] || killled->GuildIndex == War.WarIndexs[e][1])
				{
					if(killled->PosX >= MaxMinCoordsWar[e][0] && killled->PosX <= MaxMinCoordsWar[e][2] &&
						killled->PosY >= MaxMinCoordsWar[e][1] && killled->PosY <= MaxMinCoordsWar[e][3])
					{
						for(int j = 0; j < 2; j++)
						{
							for(int i = 0; i < War.TeamCount[e][j]; i++)
							{
								if(killed == War.OwnerTeam[e][i] || killed == War.DefyTeam[e][i])
								{
									wdBuffer[killed].Ingame.WarRestTime = 60;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	else if(killed > 1000 && killer > 1000)
	{
		// Caso de um MOB matar um MOB
		// Pode ser usado para Pesa
		// Ou o que mais der na telha
		// Portão infernal também		
	}

	else if(killed < 1000 && killer > 1000)
	{
		// Caso de um MOB matar um player
		// Usar de acordo com a criatividade
		INT16 PergaRessu = GetFirstSlot(killed, 3463, INVENTORY);

		if(PergaRessu != -1)
		{
			AmountMinus(&killled->Inventory[PergaRessu]);
			SendItem(killed, INVENTORY, PergaRessu, &killled->Inventory[PergaRessu]);

			killled->Status.curHP = killled->Status.maxHP;
			killled->Status.curMP = killled->Status.maxMP;

			Users[killed].Potion.CountMp = killled->Status.maxMP;
			Users[killed].Potion.CountHp = killled->Status.maxHP;

			GetCurrentScore(killed);

			BASE_GetHpMp(killled);

			SendScore(killed);
			SendCreateMob(killed, killed, 1);
			
			return;
		}
	}

	else if(killed > 1000 && killer < 1000)
	{
		// Caso de um player matar um MOB
		// Usei para fazer o evento de drop pela DLL
		// Usar de acordo com a criatividade
		// Pode ser usado para fazer Kefra e coisas assim

		if(Server.Event.Drop.isOn)
		{
			srand(time(NULL) / 5 * (rand() % 500) * 5);

			if((rand() % 100) <= Server.Event.Drop.Rate && Server.Event.Drop.Quantity > 0 && Server.Event.Drop.Id)
			{
				st_Item Item;
				memset(&Item, 0x0, sizeof(st_Item));

				Item.Index = Server.Event.Drop.Id;
				HKD_MobKilled_ControlDropItem(killer, &Item);

				Server.Event.Drop.Quantity--;
				Server.Event.Drop.Dropped++;

				char szTmp[108];

				sprintf_s(szTmp, "Jogador %s dropou %s, foram dropados [%d] restam [%d].", killler->Name, ItemList[Item.Index].Name, Server.Event.Drop.Dropped, Server.Event.Drop.Quantity);

				SendNotice(szTmp);
				//SendLog("system", szTmp);
			}
		}

		if(!strcmp(killled->Name, "Sombra Negra"))
		{
			Server.SombraNegra = FALSE;

			char szMsg[120];

			sprintf(szMsg, "%s Derrotou o Sombra Negra.", killler->Name);

			SendNotice(szMsg);

			//SendLog("system", szMsg);

			return;
		}

		if(Carta.isOn && Carta.MobsLeft)
		{
			if(killled->LastX >= LettersVCoords[Carta.ActualRoom][0] && killled->LastX <= LettersVCoords[Carta.ActualRoom][2] &&
			   killled->LastY >= LettersVCoords[Carta.ActualRoom][1] && killled->LastY <= LettersVCoords[Carta.ActualRoom][3])
			{
				Carta.MobsLeft--;

				if(Carta.MobsLeft <= 0 && Carta.ActualRoom == 3 && Carta.bossState == BOSSNAONASCIDO)
				{
					// Cria o boss 
					Carta.bossState = BOSSNASCIDO;

					CreateMob(CartasBoss[Carta.Type], 807, 3621, "npc");

					Carta.MobsLeft++;
				}
				else if(Carta.MobsLeft <= 0)
				{
					Carta.TimeLeft = 10;

					Carta.canGo = true;
				}
					
				for(INT8 party = 0; party < 13; party++)
				{
					if(Carta.cIds[party] > MAX_PLAYER || Carta.cIds[party] < 0)
						continue;

					else if(Users[Carta.cIds[party]].Status != 22)
						continue;

					SendClientSignalParm(Carta.cIds[party], 0x7530, 0x3B0, Carta.MobsLeft);

					//SendClientSignalParm(Carta.cIds[party], 0x7530, 0x3A1, Carta.TimeLeft);
				}
			}
		}

        INT8 Type = -1;
		INT8 Sala = -1;

		for(int i = 0; i < 3; i++)
		{
			for(int e = 0; e < 9; e++)
			{
				if(killled->LastX >= WaterMMCoords[i][e][0] && killled->LastX <= WaterMMCoords[i][e][2] &&
					killled->LastY >= WaterMMCoords[i][e][1] && killled->LastY <= WaterMMCoords[i][e][3])
				{
					Type = i;
					Sala = e;

					Agua[Type].Rooms[Sala].MobsLeft--;

					if(!Agua[Type].Rooms[Sala].MobsLeft)
					{
						// Quest acabou
						Agua[Type].Rooms[Sala].TimeLeft = 10;

						st_Item Item;
						memset(&Item, 0x0, sizeof(st_Item));

						Item.Index = WaterIds[Type][Sala + 1];

						PutItem(Agua[Type].Rooms[Sala].Leaders, &Item);
					}
					else
					{
						INT8 cid = -1;
						while(cid < 12)
						{
							cid++;
							NpcsAlive(Agua[Type].Rooms[Sala].Cids[cid], Agua[Type].Rooms[Sala].MobsLeft, WaterNum[Type][Sala]);
						}
					}

					break;
				}
			}
		}
	}
}

void __stdcall HKD_MobKilled_ControlDropItem(INT32 clientid, st_Item* item)
{
	// Caso o ID do item seja inexistente
	if(item->Index < 0 || item->Index > 6500)
		return;
	else if(item->Index >= 5110 && item->Index <= 5133)
		return;

	st_Mob *player = GetMobFromIndex(clientid);

	bool createItem = true;

	if(wdBuffer[clientid].Ingame.AutoDrop.isOn)
	{
		// Se o autodrop estiver on
		// createItem é setado como false por padrão
		// e só sera setada como true caso o item
		// seja uma das exceções adicionadas pelo player
		createItem = false;

		for(int i = 0; i < 5; i++)
			if(item->Index == wdBuffer[clientid].Ingame.AutoDrop.Id[i])
			{
				createItem = true;
				break;
			}
	}

	if(!createItem)
	{
		char szTmp[120];

		sprintf(szTmp, "!Item [%s] deletado pelo autodrop.", ItemList[item->Index].Name);

		SendClientMessage(clientid, szTmp);

		sprintf(szTmp, "%s Item [%s] deletado pelo autodrop.", player->Name, ItemList[item->Index].Name);

		//SendLog(Users[clientid].Username, szTmp);

		return;
	}

	if(!PutItem(clientid, item)) // Falhou em por o item, provavelmente sem espaço
		PutItemnInv(clientid, item); // Tenta por no segundo, caso tenha espaço e tenha adquirido
}