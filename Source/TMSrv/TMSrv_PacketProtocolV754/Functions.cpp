#include "DLLMain.h"

INT32 GetMatchCombine(st_Item* pItem)
{
	for(int i = 0 ; i < 6; i++)
	{
		if(pItem[i].Index <= 0 || pItem[i].Index >= MAX_ITEMLIST)
			return FALSE;
	}

	if(ItemList[pItem[0].Index].Unique < 41 || ItemList[pItem[0].Index].Unique > 49)
		return FALSE;

	if(ItemList[pItem[0].Index].Pos <= 0)
		return FALSE;

	INT8 rate = 1;
	for(int j = 2 ; j < 6; j++)
	{
		if(BASE_GetItemAbility(&pItem[j], EF_POS) == 0)
			return FALSE;

		if(GetItemSanc(&pItem[j]) == 7)// +7
		{
			rate = rate + 2;

			continue;
		}

		if(GetItemSanc(&pItem[j]) == 8)// +8
		{
			rate = rate + 4;

			continue;
		}

		if(GetItemSanc(&pItem[j]) == 9)// +9
		{
			rate = rate + 10;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 230 && GetItemSanc(&pItem[j]) <= 233)// +10
		{
			rate = rate + 14;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 234 && GetItemSanc(&pItem[j]) <= 237)// +11
		{
			rate = rate + 16;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 238 && GetItemSanc(&pItem[j]) <= 241)// +12
		{
			rate = rate + 18;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 242 && GetItemSanc(&pItem[j]) <= 245)// +13
		{
			rate = rate + 20;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 246 && GetItemSanc(&pItem[j]) <= 249)// +14
		{
			rate = rate + 22;

			continue;
		}

		if(GetItemSanc(&pItem[j]) >= 250 && GetItemSanc(&pItem[j]) <= 253)// +15
		{
			rate = rate + 25;

			continue;
		}

		return FALSE;
	}

	return rate;
}

void SendGuildChat(UINT16 GuildIndex, char *Msg)
{
	char szMsg[120];
	sprintf(szMsg, "[Guild]:> %s", Msg);

	for(int i = 0; i < 750; i++)
	{
		st_Mob *player = GetMobFromIndex(i);

		if(player->GuildIndex == GuildIndex)
			sD1D(0x7530, i, szMsg, 0xFFB22222);
	}
}

void UpdateMGuildInfo(UINT16 GuildIndex)
{
	for(int i = 0; i < 750; i++)
	{
		st_Mob *player = GetMobFromIndex(i);

		if(player->GuildIndex == GuildIndex)
			UpdateGuildInfo(i);
	}
}

void UpdateGuildInfo(INT16 cId)
{
	if(cId < 0 || cId > 750)
		return;
	else if(Users[cId].Status != 22)
		return;

	st_Mob *player = GetMobFromIndex(cId);

	A03 packet;
	memset(&packet, 0x0, sizeof A03);

	packet.Header.ClientId = 0x7530;
	packet.Header.Size     = sizeof A03;
	packet.Header.PacketId = 0xA03;

	memcpy(&packet.Guild, &Guilds[player->GuildIndex], sizeof GuildInfos);

	Sendpack((BYTE*)&packet, cId, sizeof A03);
}

bool isSubLider(char *Name, UINT16 GuildID)
{
	if(GuildID < 0 || GuildID > 65000)
		return false;

	for(int i = 0; i < 3; i++)
		if(!strcmp(Name, Guilds[GuildID].SubLiderName[i]))
			return true;
	
	return false;
}

void TimeLimitCheck(st_Item *Item, INT16 cId, bool Fairy, char* Name)
{
	if((Item->Index >= 3980 && Item->Index <= 3989) || (Item->Index >= 4152 && Item->Index <= 4158))
	{
		time_t rawnow = time(NULL);
		struct tm *now = localtime(&rawnow);

		if(now->tm_mday >= Item->EFV1 && ++now->tm_mon >= Item->EFV2 && (now->tm_year - 100) >= Item->EFV3)
		{
			SendClientMsg(cId, "Item %s expirou.", ItemList[Item->Index].Name);

			AmountMinus(Item);

			SendItem(cId, EQUIP, 14, Item);

			//SendLog(Users[cId].Username, "%s item %s expirou.",  Name, ItemList[Item->Index].Name);
		}
	}
	else if(Item->Index >= 3900 && Item->Index <= 3908 && Fairy)
	{
		if(Item->EFV3 >= 1)
		{
			Item->EFV3--;

			SendItem(cId, EQUIP, 13, Item);
		}
		else
		{
			if(Item->EFV2 >= 1)
			{
				Item->EFV2--;
				Item->EFV3 = 59;

				SendItem(cId, EQUIP, 13, Item);
			}
			else
			{
				if(Item->EFV1 >= 1)
				{
					Item->EFV1--;
					Item->EFV2 = 24;
					Item->EFV3 = 0;

					SendItem(cId, EQUIP, 13, Item);
				}
				else
				{
					AmountMinus(Item);

					SendClientMessage(cId, "Sua fada expirou.");
					SendItem(cId, EQUIP, 13, Item);
					//SendLog(Users[cId].Username, Name, "%s item %s expirou.", ItemList[Item->Index].Name);
				}
			}
		}
	}
}

void CheckItemTime(st_Item *Item)
{
	if(Item->Index < 0 || Item->Index > 6500)
		return;

	if(Item->EFV1 > MesesConfig[Item->EFV2]) // Se o dia atual + tempo da mount passar do dia limite do mês atual aqui se concerta ele 
	{
		Item->EFV1 -= MesesConfig[Item->EFV2]; // Decrescemos exatamente o tempo necessário para passagem de um mês
		Item->EFV2++; // Incrementa-se a variável do mês
	}

	if(Item->EFV2 > 12)
	{
		Item->EFV2 -= 12;
		Item->EFV3++;
	}
}

void TeleportPeople(INT16 *cIds, INT16 destX, INT16 destY)
{
	for(INT16 i = 0; i < sizeof(cIds) / sizeof(INT16); i++)
	{
		if(cIds[i] < 0 && cIds[i] > 750)
			continue;
		else if(Users[cIds[i]].Status != 22)
			continue;

		DoTeleport(cIds[i], destX, destY);
	}
}

bool CheckMount(st_Item *Item, INT16 Mount)
{
	int number = Item->Index - 3351;

	for(INT8 e = 0; e < 4; e++)
		if(MountCheck[number][e] && MountCheck[number][e] == Mount)
			return true;
   
	return false;
}

UINT16 DefineGuildWinner()
{
	UINT16 retn      = 0,
		   maxPoints = 0;

	for(UINT16 i = 0; i < 0xFFFF; i++)
	{
		if(Guilds[i].WarPoints > maxPoints)
		{
			maxPoints = Guilds[i].WarPoints;
			retn = i;
		}

		Guilds[i].WarPoints = 0;
	}

	return retn;
}

void KillMobsOnArea(int x1, int y1, int x2, int y2)
{
	for(int i = 1000; i < 30000; i++)
	{
		st_Mob *mob = GetMobFromIndex(i);

		if(mob->PosX >= x1 && mob->PosY >= y1 &&
			mob->PosX <= x2 && mob->PosY <= y2)
		{
			// Não lembro qual func manda a morte do mob, heuehuehuehuehue
		    MobKilled(0x7530, i, 0, 0);
			
		}
	}
}

void SendWarInfo(char *Message)
{
	for(int i = 0; i < 750; i++)
	{
		st_Mob *player = GetMobFromIndex(i);

		if(player->PosX >= xX && player->PosX <= XX && player->PosY >= yY && player->PosY <= YY)
			sD1D(0x7530, i, Message, 0xFF000080);
	}
}

void VerifyWarArea(INT16 cId)
{
	st_Mob *player = GetMobFromIndex(cId);

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	if(player->PosX >= xX && player->PosX <= XX &&
	   player->PosY <= yY && player->PosX <= YY)
	{
		bool canStay = true;

		if(!player->GuildIndex)
			canStay = false;
		if(DayOfWeek() != Quinta && DayOfWeek() != Terça)
			canStay = false;
		if(now->tm_hour != 21 || now->tm_min > 30)
			canStay = false;
		if(wdBuffer[cId].Ingame.isAdmin)
			canStay = true;

		if(!canStay)
		{
			DoTeleport(cId, 2100, 2100);
			SendClientMessage(cId, "Não possui autorização para estar nesta quest.");

			//SendLog(Users[cId].Username, "[%s] encontrado em localização irregular.", player->Name);
		}
	}
}

void VerifyQuests(INT16 cId)
{
	bool canStay = false;

	st_Mob *player = GetMobFromIndex(cId);

	INT8 questAtual = -1;

	for(INT8 a = 0; a < sizeof(QuestList) / sizeof(Quests); a++)
	{
		if(player->PosX >= MaxMinCoordsQuest[a][0] && player->PosX <= MaxMinCoordsQuest[a][2] &&
		   player->PosY >= MaxMinCoordsQuest[a][1] && player->PosY <= MaxMinCoordsQuest[a][3])
		{
			questAtual = a;
			break;
		}
	}

	if(questAtual == -1)
		return;

	for(int e = 0; e < 40; e++)
	{
	// Tentar fazer com while depois
		if(QuestList[questAtual].CidID[e] == cId)
		{
			canStay = true;
			break;
		}
	}

	if(player->Equip[0].EFV2 != MORTAL)
		canStay = false;

	if(player->bStatus.Level < Quests_Level[questAtual][0] || player->bStatus.Level > Quests_Level[questAtual][1])
		canStay = false;
	
	if(wdBuffer[cId].Ingame.isAdmin)
		canStay = true;

	if(!canStay)
	{
		DoTeleport(cId, 2100, 2100);
		SendClientMessage(cId, "Não possui autorização para estar nesta quest.");

		//SendLog(Users[cId].Username, "[%s] encontrado em localização irregular.", player->Name);
	}
}

void VerifyPesa(int cId)
{
	st_Mob *player = GetMobFromIndex(cId);

	for(int i = 0; i < 3; i++)
	{
		if(player->PosX >= MaxMinPesaCoords[i][0] && player->PosX <= MaxMinPesaCoords[i][2] &&
		   player->PosY >= MaxMinPesaCoords[i][1] && player->PosY <= MaxMinPesaCoords[i][3])
		{// Se estiver nesta sala do pesa

			bool canStay = false;

			for(int e = 0; e < 3; e++)
			{
				for(int a = 0; a < 13; a++)
					if(cId == Pesa[i].CIDS[e][a])
					{
						canStay = true;
						break;
					}
			}

			if(wdBuffer[cId].Ingame.isAdmin)
				canStay = true;

			if(wdBuffer[cId].Ingame.isMod)
				canStay = true;

			if(!canStay)
			{
				DoTeleport(cId, 2100, 2100);

				SendClientMessage(cId, "Não possui autorização para estar nesta área.");

				//SendLog(Users[cId].Username, "[%s] encontrado em localização irregular.", player->Name);
			}
			else if(Pesa[i].Status)
			{
			    SendClientSignalParm(cId, 0x7530, 0x3A1, Pesa[i].TimeLeft);
				NpcsAlive(cId, Pesa[i].NpcsAlive, 8);
			}
		}
	}
}

void LettersTime()
{
	if(!Carta.isOn)
		return;

	if(Carta.TimeLeft > 0)
		Carta.TimeLeft--;

	for(INT8 i = 0; i < 13; i++)
		SendClientSignalParm(Carta.cIds[i], 0x7530, 0x3A1, Carta.TimeLeft);

	if(!Carta.TimeLeft)
	{
		if(!Carta.canGo)
		{
			for(INT8 i = 0; i < 13; i++)
			{
				if(Carta.cIds[i] < 0 || Carta.cIds[i] > 750)
					continue;

				else if(Users[Carta.cIds[i]].Status != 22)
					continue;

				SendClientMessage(Carta.cIds[i], "Sua quest falhou, mais sorte na próxima vez.");

				DoRecall(Carta.cIds[i]);
			}

			KillMobsOnArea(LettersVCoords[Carta.ActualRoom][0], LettersVCoords[Carta.ActualRoom][1], 
						   LettersVCoords[Carta.ActualRoom][2], LettersVCoords[Carta.ActualRoom][3]);  

			Carta.ActualRoom = 0;
			Carta.MobsLeft   = 0;
			Carta.TimeLeft   = 0;
			Carta.Type       = 0;   
			Carta.bossState  = BOSSNAONASCIDO;

			Carta.canGo = false;
			Carta.isOn  = false;
		
			memset(&Carta.cIds, 0, sizeof(INT16) * 13);

			return;
		}
		else
		{
			Carta.ActualRoom++;
			Carta.canGo = false;

			if(Carta.ActualRoom == 4)
			{
				Carta.ActualRoom = 0;
				Carta.MobsLeft   = 0;
				Carta.TimeLeft   = 0;
				Carta.Type       = 0;   
				Carta.bossState  = BOSSNAONASCIDO;

				Carta.isOn  = false;

				for(INT8 i = 0; i < 13; i++)
				{
					if(Carta.cIds[i] < 0 || Carta.cIds[i] > 750)
						continue;
					else if(Users[Carta.cIds[i]].Status != 22)
						continue;

					DoRecall(Carta.cIds[i]);
				}

				memset(&Carta.cIds, 0, sizeof(INT16) * 13);

				return;
			}
			
			Carta.canGo = false;
			Carta.TimeLeft = 180;
			Carta.MobsLeft = CartasNum[Carta.Type - 1][Carta.ActualRoom];

			for(INT8 MobCount = 0; MobCount < 25; MobCount++)
			{
				CreateMob(CartasMobs[Carta.Type - 1][Carta.ActualRoom], LettersSMCoords[Carta.ActualRoom][0][0], LettersSMCoords[Carta.ActualRoom][0][1], "npc");
				CreateMob(CartasMobs[Carta.Type - 1][Carta.ActualRoom], LettersSMCoords[Carta.ActualRoom][1][0], LettersSMCoords[Carta.ActualRoom][1][1], "npc");
				CreateMob(CartasMobs[Carta.Type - 1][Carta.ActualRoom], LettersSMCoords[Carta.ActualRoom][2][0], LettersSMCoords[Carta.ActualRoom][2][1], "npc");
				CreateMob(CartasMobs[Carta.Type - 1][Carta.ActualRoom], LettersSMCoords[Carta.ActualRoom][3][0], LettersSMCoords[Carta.ActualRoom][3][1], "npc");
			}

			for(INT8 party = 0; party < 13; party++)
			{
				if(Carta.cIds[party] > MAX_PLAYER || Carta.cIds[party] < 0)
					continue;

				else if(Users[Carta.cIds[party]].Status != 22)
					continue;

				DoTeleport(Carta.cIds[party], TeleportCarta[Carta.ActualRoom][0], TeleportCarta[Carta.ActualRoom][1]);

				SendClientSignalParm(Carta.cIds[party], 0x7530, 0x3B0, Carta.MobsLeft);
			}
		}
	}
}

void DecrementWaterTime()
{
	for(int e = 0; e < 9; e++)
	{
		if(Agua[0].Rooms[e].TimeLeft > 0)
			Agua[0].Rooms[e].TimeLeft --; // Decremento do tempo restante
		else
		{
			// Tempo desta sala acabou
			DoTeleportArea(WaterMMCoords[0][e][0], WaterMMCoords[0][e][1], WaterMMCoords[0][e][2], WaterMMCoords[0][e][3], 1966, 1768);
			KillMobsOnArea(WaterMMCoords[0][e][0], WaterMMCoords[0][e][1], WaterMMCoords[0][e][2], WaterMMCoords[0][e][3]);
			    
			Agua[0].Rooms[e].MobsLeft = 0;
			Agua[0].Rooms[e].TimeLeft = 0;
			Agua[0].Rooms[e].isActive = false;
			Agua[0].Rooms[e].Leaders = 0;

			INT8 cid = -1;
			while(cid < 12)
			{
				cid++;
				Agua[0].Rooms[e].Cids[cid] = 0;
			}
		}

		if(Agua[1].Rooms[e].TimeLeft > 0)
			Agua[1].Rooms[e].TimeLeft --; // Decremento do tempo restante
		else
		{
			// Tempo desta sala acabou
			DoTeleportArea(WaterMMCoords[1][e][0], WaterMMCoords[1][e][1], WaterMMCoords[1][e][2], WaterMMCoords[1][e][3], 1966, 1768);
			KillMobsOnArea(WaterMMCoords[1][e][0], WaterMMCoords[1][e][1], WaterMMCoords[1][e][2], WaterMMCoords[1][e][3]);

			Agua[1].Rooms[e].MobsLeft = 0;
			Agua[1].Rooms[e].TimeLeft = 0;
			Agua[1].Rooms[e].isActive = false;
			Agua[1].Rooms[e].Leaders = 0;

			INT8 cid = -1;
			while(cid < 12)
			{
				cid++;
				Agua[1].Rooms[e].Cids[cid] = 0;
			}
		}

		if(Agua[2].Rooms[e].TimeLeft > 0)
			Agua[2].Rooms[e].TimeLeft --; // Decremento do tempo restante
		else
		{
			// Tempo desta sala acabou
			DoTeleportArea(WaterMMCoords[2][e][0], WaterMMCoords[2][e][1], WaterMMCoords[2][e][2], WaterMMCoords[2][e][3], 1966, 1768);
			KillMobsOnArea(WaterMMCoords[2][e][0], WaterMMCoords[2][e][1], WaterMMCoords[2][e][2], WaterMMCoords[2][e][3]);
			    
			Agua[2].Rooms[e].MobsLeft = 0;
			Agua[2].Rooms[e].TimeLeft = 0;
			Agua[2].Rooms[e].isActive = false;
			Agua[2].Rooms[e].Leaders = 0;

			INT8 cid = -1;
			while(cid < 12)
			{
				cid++;
				Agua[2].Rooms[e].Cids[cid] = 0;
			}
		}
	}
}

bool PutAddOnItem(st_Item *Item, UINT8 ef1, UINT8 ef2, UINT8 efv1, UINT8 efv2)
{
	if(Item->Index < 0 || Item->Index > 6500) // Id inválido
		return false;
	else if(ef1 && !efv1) // Diz que vai por add mas não tem o valor
		return false;
	else if(ef2 && !efv2) // '''''''''''''''''''''''''''''''''''''''
		return false;
	else if(!ef1 && efv1) // '''''''''''''''''''''''''''''''''''''''
		return false;
	else if(!ef2 && efv2) // '''''''''''''''''''''''''''''''''''''''
		return false;

	// Salva a sanc do item
	UINT8 Sanc = 0;

	Sanc = GetItemSanc(Item);

	// Zera os adds prévios do item
	memset(Item->Effect, 0x0, 6);

	INT8 value = 0;

	if(Sanc)
	{
		value++;

		// Põe a sanc anterior do item nele novamente
		SetItemSanc(Item, Sanc);
	}
	// Seta os novos adicionais
	Item->Effect[value].Index = ef1;
	Item->Effect[value].Value = efv1;

	Item->Effect[value + 1].Index = ef2;
	Item->Effect[value + 1].Value = efv2;

	return true;
}

void sD1D(int clientid, int destino, char *msg, int cor)
{
	pD1D p;

	p.Header.Size = sizeof pD1D;
	p.Header.PacketId = 0xD1D;
	p.Header.ClientId = clientid;

	strncpy(p.message, msg, sizeof p.message);

	p.color = cor;

	if(!destino) 
		SendToALL((BYTE*)&p, sizeof pD1D);
	else 
		Sendpack((BYTE*)&p, destino, sizeof pD1D);
}

void s334(INT32 clientId, char *message)
{// Feita por Elisson / -Guerra-
	p334 p;
	memset(&p, 0, sizeof p);

	st_Mob *player = GetMobFromIndex(clientId);

	p.Header.ClientId = clientId;
	p.Header.PacketId = 0x334;
	p.Header.Size = sizeof p334;

	strncpy(p.Arg, message, 96);
	strncpy(p.Cmd, (char*)player->Name, 16);

	for(INT16 i = 0; i < MAX_PLAYER; i++)
	{
		if(Users[i].Status != 22)
			continue;

		else if(i != clientId)
			Sendpack((BYTE*)&p, i, sizeof p334);
	}
}

void SendPartyChat(int clientId, char *message)
{
	p334 p;
	st_Mob *player = GetMobFromIndex(clientId);

	p.Header.ClientId = clientId;
	p.Header.PacketId = 0x334;
	p.Header.Size = 128;

	strncpy(p.Arg, message, 96);
	strcpy(p.Cmd,player->Name);

	if(player->Leader != -1 && player->Leader != 0)
	{
		st_Mob *mob = GetMobFromIndex(player->Leader);
		for(int i = 0;i<12;i++)
		{
			if(mob->PartyList[i] > MAX_PLAYER)
				continue;

			if(mob->PartyList[i] == clientId)
				continue;

			CUser *user = &Users[mob->PartyList[i]];

			if(user->Status != 22)
				continue;
			
			if(user->AllStatus.Party)
				continue;

			Sendpack((BYTE*)&p, mob->PartyList[i], sizeof p334);
		}

		Sendpack((BYTE*)&p, player->Leader, sizeof p334);
	}
	else
	{
		for(int i = 0; i<12;i++)
		{
			if(player->PartyList[i] > MAX_PLAYER)
				continue;

			CUser *user = &Users[player->PartyList[i]];

			if(user->Status != 22)
				continue;

			if(user->AllStatus.Party)
				continue;

			Sendpack((BYTE*)&p, player->PartyList[i], sizeof p334);
		}
	}
}

void SendToALL(BYTE *szBuffer, int PacketSize)
{
	for(int i = 0; i < 750; i++) 
	{
		if(Users[i].Status == 22)
			Sendpack(szBuffer, i, PacketSize);
	}
}

unsigned long int GetCoinOnItens(st_Item *Inventory)
{
	if(Inventory == NULL)
		return 0;

	unsigned long int retn = 0;

	for(int i = 0; i < sizeof Inventory / sizeof st_Item; i++)
	{
		// Id do slot inválido, segue para o próximo slot
		if(Inventory[i].Index < 0 || Inventory[i].Index > 6500)
			continue;

		// Preço do item invalido, segue para o próximo slot
		if(ItemList[Inventory[i].Index].Price < 0 || ItemList[Inventory[i].Index].Price > 2000000000)
			continue;

		unsigned long int PriceOfItem = ItemList[Inventory[i].Index].Price;

		for(int e = 0; e < 3; e++)
		{
			if(Inventory[i].Effect[e].Index == EF_AMOUNT)
			{
				// Caso esteja em pack, multiplica o preço pago pelo número de itens no pack
				PriceOfItem = PriceOfItem * Inventory[i].Effect[e].Value;

				break;
			}
		}

		if((retn + PriceOfItem) > 2000000000)
		{
			// Valor total não pode passar de 2Bi
			retn = 2000000000;

			break;
		}

		retn += PriceOfItem;
	}

	return retn;
}

st_Item* GetItemPointer(st_Mob* mob, st_Item* cargo, int type, int pos) 
{
	st_Item* ret = NULL;

	if(type == EQUIP)
	{
		if(pos < 0 || pos >= 16)
			return NULL;

		ret = &mob->Equip[pos];
	}
	else if(type == INVENTORY)
	{
		if(pos < 0 || pos >= 64)
			return NULL;

		ret = &mob->Inventory[pos];
	}
	else if(type == CARGO)
	{
		if(pos < 0 || pos >= 128)
			return NULL;

		ret = &cargo[pos];
	}
	else
		return NULL;

	if(ret->Index <= 0 || ret->Index > 6500)
		return NULL;

	return ret;
}

bool CheckArchItem(int id)
{
    int retorno = false;
    ///SET'S
    if(id >= 1221 && id <= 1224) retorno = true;
    else if(id >= 1356 && id <= 1359) retorno = true;
    else if(id >= 1506 && id <= 1509) retorno = true;
    else if(id >= 1656 && id <= 1659) retorno = true;
    ///ARMAS ARCH
    else if(id == 811 || id == 826 || id == 841) retorno = true;
    else if(id == 856 || id == 871 || id == 886) retorno = true;
    else if(id == 871 || id == 886 || id == 903 || id == 904) retorno = true;
    else if(id == 912 || id == 937 || id == 2379 || id == 2380) retorno = true;
    ///ARMAS ARCH ANCT
    else if( (id >= 2491 && id <= 2494) || (id >= 2551 && id <= 2554) ) retorno = true;
    else if( (id >= 2611 && id <= 2614) || (id >= 2671 && id <= 2674) ) retorno = true;
    else if( (id >= 2791 && id <= 2794) || (id >= 2859 && id <= 2866) ) retorno = true;
    else if( (id >= 2895 && id <= 2898) || (id >= 2935 && id <= 2938) ) retorno = true;
    return retorno;
}

bool CheckHardItem(int id)
{
    int retorno = false;
    ///SET'S
    if(id >= 1901 && id <= 1910){
        retorno = true;
    }

    ///ARMAS ARCH
    else if(id == 1230 || id == 1231 || id == 1232 || id == 1667)
        retorno = true;
    else if(id == 1233 || id == 1365 || id == 1366 || id == 1668)
        retorno = true;
    else if(id == 1367 || id == 1368 || id == 1515 || id == 1516)
        retorno = true;
    else if(id == 1517 || id == 1518 || id == 1665 || id == 1666)
        retorno = true;

    return retorno;
}

int GetTeamAlive(INT8 WarNum, INT8 Team)
{
	if(WarNum < 0 || WarNum > 3)
		return -1;
	if(Team && Team != 1)
		return -1;

	int retn = 0;

	for(int i = 0; i < War.TeamCount[WarNum][Team]; i++)
	{
		INT16 cId = 0;

		if(!Team)
			cId = War.OwnerTeam[WarNum][i];
		else
			cId = War.DefyTeam[WarNum][i];

		if(cId < 0 || cId > 750)
			continue;
		if(Users[cId].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(cId);

		if(player->PosX >= MaxMinCoordsWar[WarNum][0] && player->PosX <= MaxMinCoordsWar[WarNum][2] &&
		   player->PosY >= MaxMinCoordsWar[WarNum][1] && player->PosY <= MaxMinCoordsWar[WarNum][3])
		{
			// Caso esteja vivo, ou ainda tenha tempo para ser ressucitado, ou esteja de nyerds
			if(player->Status.curHP >= 1 || wdBuffer[cId].Ingame.WarRestTime || player->Equip[13].Index == 769)
				retn++;
			else
				ClearArea(player->PosX, player->PosY, player->PosX, player->PosY);
		}
	}

	return retn;
}

void PutAsWinner(INT8 WarNum, INT8 Winner)
{
	// Winner = 1 Desafiante
	// Winner = 0 Dono

	if(WarNum < 0 || WarNum > 3)
		return;
	if(Winner && Winner != 1)
		return;

	// Limpa a área da guerra
	ClearArea(MaxMinCoordsWar[WarNum][0], MaxMinCoordsWar[WarNum][1], MaxMinCoordsWar[WarNum][2], MaxMinCoordsWar[WarNum][3]);
	
	// Seta a guerra atual como finalizada 
	War.Finalizada[WarNum] = true;
	
	// Se o dominante atual for diferente do vencedor, seta como o correto.
	if(War.Owner[WarNum] != War.BetIndex[WarNum][Winner]) 
	    War.Owner[WarNum] = War.BetIndex[WarNum][Winner];

	Guilds[War.Owner[WarNum]].Posses[WarNum] = true;

	// Seta o reino dominante como o da guild dominante
	War.Kingdom[WarNum] = Guilds[War.Owner[WarNum]].Kingdom;

	// Entrega 70% da Fame das apostas para a guild campeã
	Guilds[War.Owner[WarNum]].FAME += (War.BetValue[WarNum] / 100) * 70;

	// Zera os index dos apostadores
	War.BetIndex[WarNum][0] = 0;
	War.BetIndex[WarNum][1] = 0;

	// Zera a aposta acumulada
	War.BetValue[WarNum] = 0;

	// Seta a guerra como finalizada
	War.Finalizada[WarNum] = true;
	War.Iniciada[WarNum] = false;
	
	char szMsg[108];

	sprintf(szMsg, "Guild [%s] acaba de dominar %s!!", Guilds[War.Owner[WarNum]].GuildName, szCitys[WarNum]);

	SendNotice(szMsg);
}

void OpenTrade(short ClientID, short MobID)
{
        // Usado após o Request, onde é enviado o trade totalmente vazio
        SendTrade p;
        memset(&p, 0, sizeof p);
        p.Header.ClientId = MobID;
        p.OtherClientid = ClientID;
        p.Header.Size = 156;
        p.Header.PacketId = 0x383;
        for(UINT8 i=0;i<15;i++)
                p.TradeItemSlot[i] = 255;
        Sendpack((BYTE*)&p, MobID, 156);
}
 
void SendAllTrade(short ClientID, short MobID)
{
        // Envia o trade completo para o MobID
        SendTrade p;   
        memset(&p, 0, sizeof p);
        p.Header.ClientId = MobID;
        p.OtherClientid = ClientID;
        p.Header.Size = 156;
        p.Header.PacketId = 0x383;
        p.Confirma = Trade[ClientID].Confirm;
        for(UINT8 i=0;i<15;i++)
        {
                p.TradeItem[i] = Trade[ClientID].Itens[i];
                p.TradeItemSlot[i] = Trade[ClientID].TradeItemSlot[i];
        }
        p.Gold = Trade[ClientID].Gold;
        Sendpack((BYTE*)&p, MobID, 156);
}
 
void CloseTrade(short ClientID)
{
    // Fecha o trade dos dois usuários
    memset(Trade[ClientID].TradeItemSlot, 255, sizeof(char) * 15);
    memset(Trade[ClientID].Itens, 0, sizeof st_Item * 15);

    Trade[ClientID].isTrading = false;
    Trade[ClientID].Timer = 0;
    Trade[ClientID].Confirm = false;
    Trade[ClientID].WaitingData = false;

    PacketHeader Header;
    Header.ClientId = ClientID;
    Header.Size = 12;
    Header.PacketId = 0x384;
    Sendpack((BYTE*)&Header, ClientID, 12);

	if(Trade[Trade[ClientID].ClientID].isTrading && Trade[Trade[ClientID].ClientID].ClientID != 0 && Users[Trade[Trade[ClientID].ClientID].ClientID].Status == 22)
    {
        // Checa se o outro jogador está em modo troca e se ele é um jogador válido
        // Evita bugs com o outro char ficar em modo troca ainda
        Trade[Trade[ClientID].ClientID].isTrading = false;
        Trade[Trade[ClientID].ClientID].Timer = 0;
        Trade[Trade[ClientID].ClientID].Confirm = false;
        Trade[Trade[ClientID].ClientID].WaitingData = false;

        memset(Trade[Trade[ClientID].ClientID].Itens, 0, sizeof st_Item * 15);
        memset(Trade[Trade[ClientID].ClientID].TradeItemSlot, 0, sizeof(char) * 15);

        Header.ClientId = Trade[ClientID].ClientID;
        Sendpack((BYTE*)&Header, Trade[ClientID].ClientID, 12);
        Trade[Trade[ClientID].ClientID].ClientID = 0;
    }

    Trade[ClientID].ClientID = 0;
}
 
void CheckItensOnTrade(short ClientID, short MobID)
{
        // Sua função é checar se os itens colocados no trade realmente existem no inventário do usuário
        // Se não existirem, provavelmente é uma tentativa de hack pois o client não se enganará com isso
        st_Mob *player = GetMobFromIndex(ClientID);
        st_Mob *mob = GetMobFromIndex(MobID);
        for(UINT8 i=0;i<15;i++)
        {
                if(Trade[ClientID].Itens[i].Index == 255)
                        continue;
                if(!memcmp(&Trade[ClientID].Itens[i], &player->Inventory[Trade[ClientID].TradeItemSlot[i]], 8))
                {
                        CloseTrade(ClientID);
                        break;
                }
                if(!memcmp(&Trade[MobID].Itens[i], &mob->Inventory[Trade[MobID].TradeItemSlot[i]], 8))
                {
                        CloseTrade(MobID);
                        break;
                }
        }
}
 
bool CanTrade(UINT16 Index)
{
    // Função que serve para adicionar Itens imóveis
    switch(Index)
    {
		case 508: case 509: case 526: 
		case 527: case 528:
			return false;

		default:
			return true;
    }

    return true;
}
 
bool AddItensOnTrade(SendTrade *p)
{
    // Serve para a verificação de um item imóvel e para adicionar os itens do trade a struct trade do usuário
    for(UINT8 i=0;i<15;i++)
    {
        if(!CanTrade(p->TradeItem[i].Index))
        {
            SendClientMessage(p->Header.ClientId, "Item imóvel!");
            return false;
        }

        Trade[p->Header.ClientId].TradeItemSlot[i] = p->TradeItemSlot[i];

        memcpy(&Trade[p->Header.ClientId].Itens[i], &p->TradeItem[i], sizeof st_Item);              
    }      

    st_Mob *player = GetMobFromIndex(p->Header.ClientId);
    st_Mob *mob = GetMobFromIndex(p->OtherClientid);

    if(p->Gold > player->Gold)
        return false;

	if((player->Gold - Trade[p->Header.ClientId].Gold) + Trade[p->OtherClientid].Gold > 2000000000)
    {
        SendClientMessage(p->Header.ClientId, "Limite de 2.000.000.000 bilhões de gold.");
        SendClientMessage(p->OtherClientid, "Limite de 2.000.000.000 bilhões de gold.");
        return false;
    }

	if((mob->Gold - Trade[p->OtherClientid].Gold) + Trade[p->Header.ClientId].Gold > 2000000000)
    {
        SendClientMessage(p->Header.ClientId, "Limite de 2.000.000.000 bilhões de gold.");
        SendClientMessage(p->OtherClientid, "Limite de 2.000.000.000 bilhões de gold.");
        return false;
    }

    return true;
}
 
BYTE GetAmountItemOnTrade(short ClientID)
{
        // Retorna quantos itens foram colocados no trade do usuário
        BYTE val = 0;
        for(UINT8 i=0;i<15;i++)
                if(Trade[ClientID].Itens[i].Index != 0)
                        val++;
        return val;
}

BYTE GetAmountItem(WORD clientid)
{
        st_Mob* player = GetMobFromIndex(clientid);
        BYTE j = 0;
        for(BYTE i = 0; i < 64; i++)
                if(player->Inventory[i].Index == 0)
                        j++;
        return j;
}

bool PutItemnInv(INT16 cId, st_Item *Item)
{
	if(cId < 0 || cId > MAX_PLAYER)
		return false;

	if(Item->Index < 0 || Item->Index > MAX_ITEMLIST)
		return false;

	if(!wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].nInvent.hasBuyed)
		return false;

	for(INT8 i = 0; i < 63; i++)
	{
		if(!wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].nInvent.sInv1[i].Index)
		{
			memcpy(&wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].nInvent.sInv1[i].Index, &Item, sizeof st_Item);

			char tmp[120];

			sprintf_s(tmp, "! Item [%s] adicionado ao segundo inventário.", ItemList[Item->Index].Name);

			SendClientMessage(cId, tmp);

			return true;
		}
	}

	return false;
}

void Sendpack(BYTE *bufr, int clientId, int paksize)
{
	static DWORD call_addr = 0x00401221;
	int socketAddress = (UINT32)&Users[clientId].Service.FD;
	__asm
	{
		MOV ECX, socketAddress

		PUSH paksize
		PUSH bufr
		CALL call_addr
	}
}

bool Log(char* Log, char *Who)
{
	bool retn = false;

	if(!Who[0])
		return retn;

	char szTmp[1024];
	sprintf(szTmp, "Log/%s.txt", Who);

	FILE *fs = fopen(szTmp, "a");

	if(fs)
	{
		if(fprintf(fs, Log) == strlen(Log))
			retn = true;

		fclose(fs);
	}

	return retn;
}

void SendLog(char *Who, char *msg, ...)
{   
	char szBuffer[1000];
	char realMsg[1000];

	SYSTEMTIME time;
	GetLocalTime(&time);

	va_list arglist;
	va_start(arglist, msg); 
	vsprintf(szBuffer, msg, arglist);
	va_end(arglist); 		

	sprintf_s(realMsg, "[%02d/%02d/%04d as %02d:%02d:%02d] %s\n", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond, szBuffer);
		
	Log(realMsg, Who);
}

void ReadDonateList()
{
	FILE *fs = NULL;
	fopen_s(&fs,"Plugin/TMSRV_SOD/DonateList.txt", "r");

	if(fs)
	{
		memset(DonateList, 0x0, sizeof(DonateList) / sizeof(Donate));
		char line[1024];
		int i = 0;		
		while(fgets(line, sizeof(line), fs))
		{
			if(i < 300)
			{
				if(*line == '\n' || *line == '#')
					continue;

				sscanf(line, "%d,%d,%d,%d,%d,%d,%d,%d,%d", &DonateList[i].Item.Index, &DonateList[i].Item.Effect[0].Index, 
				&DonateList[i].Item.Effect[0].Value, &DonateList[i].Item.Effect[1].Index, &DonateList[i].Item.Effect[1].Value, 
				&DonateList[i].Item.Effect[2].Index, &DonateList[i].Item.Effect[2].Value, &DonateList[i].Price, &DonateList[i].Store);
			}
			else
			{
				//SendLog("system", "Erro: Contagem máxima na lista de donates atingida.");				
				break;
			}

			i++;
		}
		fclose(fs);
	}
	else
	{		
		MessageBoxA(NULL, "Erro na leitura da lista de donates.", "Error", MB_OK);
		ExitProcess(1);
	}
}

void ReadResetList()
{
	FILE *fs = NULL;
	fopen_s(&fs,"Plugin/TMSRV_SOD/ResetList.txt", "r");

	if(fs)
	{
		memset(ResetList, 0x0, sizeof(ResetList) / sizeof(Resets));
		char line[1024];
		int i = 0;
		while((fscanf(fs, "%[^\n]", line)) != EOF)
	    {
			if(i < 300)
			{
				fgetc(fs);
				//<TimeInterval>,<X_Min>,<Y_Min>,<X_Max>,<Y_Max>,<Lvl_Min>,<Lvl_Max>
				sscanf(line, "%d,%d,%d,%d,%d,%d,%d", &ResetList[i].Time, &ResetList[i].MinCoords.X,
					&ResetList[i].MinCoords.Y, &ResetList[i].MaxCoords.X, &ResetList[i].MaxCoords.Y,
					&ResetList[i].MinLevel, &ResetList[i].MaxLevel);	

				if(!ResetList[i].Time)
					continue;								
			}
			else
			{
		       //SendLog("system", "Erro: Contagem máxima na lista de resetes atingida.");				
				break;
			}

			i++;
		}
		fclose(fs);
	}
	else
	{		
		MessageBoxA(NULL, "Erro na leitura da lista de resets.", "Error", MB_OK);
		ExitProcess(1);
	}
}

void ReadMessageList()
{
	FILE *fs = NULL;
	fopen_s(&fs,"Plugin/TMSRV_SOD/MessageList.txt", "r");

	if(fs)
	{
		memset(MessageList, 0x0, sizeof(MessageList) / sizeof(Messages));
		char line[1024];
		int i = 0;
		while((fscanf(fs, "%[^\n]", line)) != EOF)
	    {
			if(i < 50)
			{
				char msg[1024];
				fgetc(fs);
				//<TimeInterval>,<msg>
				sscanf(line, "%d,%s", &MessageList[i].Time, &msg);
				strncpy(MessageList[i].Msg, msg, 107);// 107 carácteres, pra não extrapolar os 108 da MessageList[i].Msg e sobrar um pra setar como 0/				
			}
			else
			{
		        //SendLog("system", "Erro: Contagem máxima na lista de mensagens atingida.");				
				break;
			}

			i++;
		}
		fclose(fs);
	}
	else
	{		
		MessageBoxA(NULL, "Erro na leitura da lista de mensagens.", "Error", MB_OK);
		ExitProcess(1);
	}
}

void ReadArchFile() 
{
	FILE *hFile = NULL; 
	char szTMP[128]; 
	sprintf_s(szTMP, "Plugin/TMSRV_SOD/BaseMob/Arch");
	fopen_s(&hFile, szTMP, "rb"); 
	if(hFile != NULL) 
	{ 
		stMOB754 *mobs = (stMOB754*)0x7B08520; 
		fread(&MobArch, 1, 756, hFile); fclose(hFile); 		
	}
	else
	{
		MessageBoxA(NULL, "Erro na leitura do basemob arch.", "Error", MB_OK);
		ExitProcess(1);
	}
}

void ReadGuildFile()
{
	memset(&Guilds, 0x0, sizeof(GuildInfos) * 0xFFFF);
			
	FILE *hFile = NULL; 
	char szTMP[128]; 
	sprintf_s(szTMP, "Plugin/TMSRV_SOD/Guilds.bin");
	fopen_s(&hFile, szTMP, "rb");

	if(hFile != NULL) 
	{ 
		fread(&Guilds, 1, sizeof(GuildInfos) * 0xFFFF, hFile); 
		fclose(hFile); 		
	}
	else
	{
		MessageBoxA(NULL, "Erro na leitura das guilds.", "Error", MB_OK);
		ExitProcess(1);
	}
}

void ReadEventFile()
{
	memset(&Server.Event, 0x0, sizeof Events);
			
	FILE *hFile = NULL; 
	char szTMP[128]; 
	sprintf_s(szTMP, "Plugin/TMSRV_SOD/eventData.bin");
	fopen_s(&hFile, szTMP, "rb");

	if(hFile != NULL) 
	{ 
		fread(&Server.Event, 1, sizeof Events, hFile); 
		fclose(hFile); 		
	}
	else
		MessageBoxA(NULL, "Erro na leitura dos npcs de evento.", "Error", MB_OK);
}

void ReadAllData()
{
	for(int i = 0; i < 5; i++)
		War.Tax[i] = 10;

	memset(&Server, 0x0, sizeof ServerInfos);
	memset(&Pesa, 0x0, sizeof(Pesas) * 3);
	memset(&Agua, 0x0, sizeof(Aguas) * 3);
	memset(&Trade, 0x0, sizeof(st_Trade) * 1000);

	ReadDonateList();
	ReadResetList();
	ReadMessageList();	
	ReadArchFile();	
	ReadGuildFile();
	ReadEventFile();
}

UINT8 DayOfWeek()
{
	// 0 = segunda .... 6 = domingo
	// Créditos: shepher'
	static const BYTE szTable[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    time_t rawnow = time(NULL);
    struct tm *now = localtime(&rawnow);
	int cDay = now->tm_mday;
	int cMon = now->tm_mon;
	int cYear = now->tm_year;

	return (cYear + ((cYear / 4) + szTable[cMon] + (cDay - 1))) % 7;
}

bool SaveAccount(int clientId)
{
	if(clientId < 0 || clientId > 740)
		return false;
	if(!Users[clientId].Status)
        return false;
	
	char szTMP[1024];
	FILE *pFile = NULL;

	sprintf_s(szTMP, "Plugin/TMSRV_SOD/Data/%s.bin", Users[clientId].Username);

	fopen_s(&pFile, szTMP, "wb");
	if(pFile)
	{
		int mobSize = sizeof wdBase - (sizeof wdBuffer[0].Ingame);

		fwrite((void*)&wdBuffer[clientId], 1, mobSize, pFile);

		fclose(pFile);		

		return true;
	}

	printf("Conta %s não foi salva com sucesso. \n", Users[clientId].Username);

	return false;	
}

bool SaveGuilds()
{
	char szTMP[1024];
	FILE *pFile = NULL;

	sprintf_s(szTMP, "Plugin/TMSRV_SOD/Guilds.bin");

	fopen_s(&pFile, szTMP, "wb");
	if(pFile)
	{
		int fileSize = sizeof GuildInfos * 0xFFFF;

		fwrite((void*)&Guilds, 1, fileSize, pFile);

		fclose(pFile);		

		return true;
	}

	return false;	
}

FindAmountItem FindOcurrences(st_Item *Item, int index)
{
	FindAmountItem retn;
	memset(&retn, 0, sizeof(FindAmountItem));

	if(index < 0 || index > 6500)
		return retn;

	for(int i = 0; i < sizeof(Item) / sizeof(st_Item); i++)
	{
		if(Item[i].Index == index)
		{
			// Salva em qual slot está a info
			retn.Slots[retn.Amount] = i;
			// Retorna um ponteiro para o item, melhor para mexer
			retn.Itens[retn.Amount] = &Item[i];
			// Aumenta a quantidade de itens disponíveis
			retn.Amount++;
		}
	}

	return retn;
}

void AmountMinus(st_Item *item)
{
	int index = 0;
	int amount = 0;
	for(int i = 0;i < 3;i++)
	{
		if(item->Effect[i].Index == 61)
		{
			index = i;
			amount = item->Effect[i].Value;
			break;
		}
	}

	if(amount <= 1)
		memset(item, 0, sizeof st_Item);
	else
		item->Effect[index].Value --;
}

void SendALL(int clientid)
{
	sendinv1(clientid);
	sendinv2(clientid);
	sendstats(clientid);
	sendequip(clientid);
	return;
}

void RefinarItemMais(st_Item *item, int value)
{
	if(item->EF1 == EF_SANC || (item->EF1 >= 116 && item->EF1 <= 125))
	    item->EFV1 += value;
	else if(item->EF2 == EF_SANC || (item->EF2 >= 116 && item->EF2 <= 125))
	    item->EFV2 += value;
	else if(item->EF3 == EF_SANC || (item->EF3 >= 116 && item->EF3 <= 125))
	    item->EFV3 += value;
	else
	{
		if(!item->EF1) 
		{
			item->EF1 = EF_SANC;
			item->EFV1 = value;
		}
		else if(!item->EF2) 
		{
			item->EF2 = EF_SANC;
			item->EFV2 = value;
		}
		else if(!item->EF3) 
		{
			item->EF3 = EF_SANC;
			item->EFV3 = value;
		}
	}
	
	return;
}

int GetChanceRefOdin(st_Item *Item)
{
	if((Item->EFV1 >= 234 && Item->EFV1 < 238) ||
	   (Item->EFV2 >= 234 && Item->EFV2 < 238) ||
	   (Item->EFV3 >= 234 && Item->EFV3 < 238))
		return 5;
	else if((Item->EFV1 >= 238 && Item->EFV1 < 242) ||
	   (Item->EFV2 >= 238 && Item->EFV2 < 242) ||
	   (Item->EFV3 >= 238 && Item->EFV3 < 242))
		return 3;
	else if((Item->EFV1 >= 242 && Item->EFV1 < 246) ||
	   (Item->EFV2 >= 242 && Item->EFV2 < 246) ||
	   (Item->EFV3 >= 242 && Item->EFV3 < 246))
		return 2;
	else if((Item->EFV1 >= 246 && Item->EFV1 < 250) ||
	   (Item->EFV2 >= 246 && Item->EFV2 < 250) ||
	   (Item->EFV3 >= 246 && Item->EFV3 < 250))
		return 1;
	else
		return 0;
}

INT8 ReturnItemAmount(st_Item *Item)
{
    INT8 retn = 0;

    for(int i = 0; i < 3; i++)
	  if(Item->Effect[i].Index == EF_AMOUNT)
	  {
		   retn = Item->Effect[i].Value;

		   break;
	  }

	 return retn;
}

int GetItemSanc(st_Item *item)
{
	for (int i = 0; i < 3; i++)
		if (item->Effect[i].Index == EF_SANC || (item->Effect[i].Index >= 116 && item->Effect[i].Index <= 125))
			return item->Effect[i].Value;
	
	return 0;
}

int GetFirstSlot(int clientId, int itemId, int itemType)
{
	st_Mob *player = GetMobFromIndex(clientId);

	switch(itemType)
	{
		case EQUIP:
		{
			for(int i = 0; i < 16; i++)
			{
				if(player->Equip[i].Index == itemId)
					return i;
			}
		}
		break;

		case INVENTORY:
		{
			for(int i = 0; i < 63; i++)
			{
				if(player->Inventory[i].Index == itemId)
					return i;
			}
		}
		break;

		case CARGO:
		{
			for(int e = 0; e < sizeof(Users[0].Storage.Item) / sizeof(st_Item); e++)
			{
				// Procura por slot vazio no Baú
				if(Users[clientId].Storage.Item[e].Index == itemId)
					return e;
			}
		}
		break;
	}

	return -1;
}

void SetItemSanc(st_Item *item, int value)
{
	if(item->EF1 == EF_SANC || (item->EF1 >= 116 && item->EF1 <= 125))
		item->EFV1 = value;
	else if(item->EF2 == EF_SANC || (item->EF2 >= 116 && item->EF2 <= 125))
		item->EFV2 = value;
	else if(item->EF3 == EF_SANC || (item->EF3 >= 116 && item->EF3 <= 125))
		item->EFV3 = value;
	else
	{
		for(int i = 0; i < 3; i++)
		{
			if(!item->Effect[i].Index)
			{
				item->Effect[i].Index = EF_SANC;
				item->Effect[i].Value = value;
				return;
			}
		}
	}
}

bool isVip(int index)
{
	if(index < 0 || index > 740)
		return false;

	time_t rawnow = time(NULL);
    struct tm *now = localtime(&rawnow);

	if((now->tm_mday > wdBuffer[index].VipInfo.Date.Dia  && ++now->tm_mon >= wdBuffer[index].VipInfo.Date.Mes && (now->tm_year + 1900) >= wdBuffer[index].VipInfo.Date.Ano) || 
		++now->tm_mon > wdBuffer[index].VipInfo.Date.Mes && (now->tm_year + 1900) >= wdBuffer[index].VipInfo.Date.Ano)
		return false;
	else
		return true;
}

bool bFile_exists(const char *filename)
{
	FILE *arquivo;
	arquivo = fopen(filename, "rb");

	if(arquivo)
	{
		fclose(arquivo);
		return true;
	}

	return false;
}

bool file_exists(const char *filename)
{
	FILE *arquivo;

	if(arquivo = fopen(filename, "r"))
	{
		fclose(arquivo);
		return true;
	}

	return false;
}

void NpcsAlive(int clientid, int vivos, int total)
{
	BYTE BufferSend[4096];
	*(short*)&BufferSend[0] = 16;
	*(short*)&BufferSend[4] = 0x3BB;
	*(short*)&BufferSend[6] = 30000;
	*(short*)&BufferSend[12] = vivos;
	*(short*)&BufferSend[14] = total;
	Sendpack((BYTE*)BufferSend, clientid, 16);
}

INT32 CheckItems(st_Window *pServer)
{
	INT32 retn = -1;

	static const INT16 ItemJoia[6][4] = {
		{413, 2441, 2442, 3200}, {413, 2443, 2442, 3201},{4127, 4127, 4127, 3202}, 
		{4127, 4127, 697, 3203}, {412, 2441, 2444, 3204}, {412, 2444, 2443, 3205}
	};

	for(INT8 i = 0; i < sizeof(ItemJoia) / sizeof(INT16); i++)
	{
		if(pServer->ItemId[0].Index == ItemJoia[i][0] && pServer->ItemId[1].Index == ItemJoia[i][1] && pServer->ItemId[2].Index == ItemJoia[i][2])
			retn = ItemJoia[i][3];
	}

	return retn;	
}

void Composition(st_Window *pServer, st_Mob *player)
{
	if(CheckItems(pServer) == -1)
		SendClientMessage(pServer->Header.ClientId, "Há algo errado com sua composição.");
	else
	{
		for(char i = 0; i < 3; i ++)				
			memset(&player->Inventory[pServer->Slot[i]], 0, sizeof st_Item);

		srand(time(NULL) / 5 * (rand() % 500) * 5);

		INT8 Random = Rand() % 100, Chances = 0;

		if(player->Equip[0].EFV2 <= ARCH)
			Chances = 30;
		else if(player->Equip[0].EFV2 >= CELESTIAL)
			Chances = 50;

		if(isVip(pServer->Header.ClientId))
			Chances += 15;

		if(Random > Chances)
			SendClientMessage(pServer->Header.ClientId, "Falha na composição.");
		else
		{
			SendClientMessage(pServer->Header.ClientId, "Composição concluída.");

			st_Item pItem;
			memset(&pItem, 0x0, sizeof(st_Item));

			pItem.Index = CheckItems(pServer);

			PutItem(pServer->Header.ClientId, &pItem);
		}

		for(char i = 0; i < 3; i ++)			
			SendItem(pServer->Header.ClientId, INVENTORY, pServer->Slot[i], &player->Inventory[pServer->Slot[i]]);
	}
}

INT16 GetFrags(INT32 clientid)
{
	//estou apenas reaproveitando o sistema da TM
	//este é o melhor método para usar os frags
	return *(short*)(&GetMobFromIndex(clientid)->Inventory[63].Index + 2);
}

void SetFrags(INT32 clientid, short frags)
{
	*(short*)(&GetMobFromIndex(clientid)->Inventory[63].Index + 2) = frags;
}

INT64 SystemTimeDifference(const SYSTEMTIME time1, const SYSTEMTIME time2)
{   
    union timeunion {
        FILETIME fileTime;
        LARGE_INTEGER ul;		
    };
    
    timeunion ft1;
    timeunion ft2;

    SystemTimeToFileTime(&time1, &ft1.fileTime);
    SystemTimeToFileTime(&time2, &ft2.fileTime);

    return ft2.ul.QuadPart - ft1.ul.QuadPart;
}

bool FileExist(const char* Name )
{	
	if (FILE * file = fopen(Name, "r"))
    {
        fclose(file);
        return true;
    }
    return false;	
}

bool CheckBan(const char *login)
{	//retorna true se estiver banido
	try{

		char fileName[1024];
		sprintf_s(fileName, "Plugin/TMSRV_SOD/Data/Ban/%s.bin", login);				

		if(!FileExist(fileName))			
			return false;			

		FILE *pFile = NULL;
		fopen_s(&pFile, fileName, "rb");
		INT8 buffer[sizeof SYSTEMTIME];
		fread(buffer, 1, sizeof SYSTEMTIME, pFile);
		fclose(pFile);

		SYSTEMTIME banTime, nowTime;		
		memcpy(&banTime, &buffer, sizeof SYSTEMTIME);	
		GetLocalTime(&nowTime);				
						
		INT64 timeDiff = SystemTimeDifference(nowTime, banTime);						

		if(timeDiff > 0)
			return true;				
				
		remove(fileName);
		return false;		
	}
	catch(...)
	{		
		return true;
	}
}

void SendBan(const char *login)
{
	//ban permanente
	__try
	{
		char fileName[1024];
		sprintf_s(fileName, "Plugin/TMSRV_SOD/Data/Ban/%s.bin", login);		

		SYSTEMTIME mTime;		
		GetLocalTime(&mTime);
		mTime.wYear = 9999;	

		FILE *pFile;
		fopen_s(&pFile, fileName, "wb");
		fwrite(&mTime, 1, sizeof SYSTEMTIME, pFile);
		fclose(pFile);
	}
	__except(TRUE)
	{
	}
}

void SendBan(const char *login, const SYSTEMTIME banTime)
{
	//ban definido por data
	__try{
		char fileName[1024];
		sprintf_s(fileName, "Plugin/TMSRV_SOD/Data/Ban/%s.bin", login);				

		FILE *pFile;
		fopen_s(&pFile, fileName, "wb");
		fwrite(&banTime, 1, sizeof SYSTEMTIME, pFile);
		fclose(pFile);
	}
	__except(TRUE)
	{
	}
}

// Teleporta todos os players para os respectivos locais da guerra
void TeleportWar()
{
	static const UINT8 DestCoordsWar[4][4] = 
	{
		{205, 221, 229, 221},
		{148, 221, 173, 221},
		{204, 157, 229, 157},
		{148, 157, 173, 157}
	};

	for(int x=0; x<4; x++)
	{
		if(!War.BetIndex[x][0])
		{// Não houve desafiante
			printf("Não houve desafiante na cidade %s\n", szCitys[x]);
			War.Finalizada[x] = true;
			continue;
		}

		int Chall = 0;
		int Owner = 0;

		for(int y = 1; y < MAX_PLAYER; y++)
		{
			// Checa se esse cID está online 
			if(Users[y].Status != 22)
				continue;

			st_Mob *player = GetMobFromIndex(y);
			// Checa se o player possui uma guild, se não, continua o loop
			if(!player->GuildIndex)
				continue;

			int GuildIndex = player->GuildIndex;
			// Caso não seja desafiador / defensor continua o loop
			if(War.Owner[x])
			{
				if(GuildIndex != War.BetIndex[x][0] && GuildIndex != War.Owner[x])
					continue;
			}
			else
			{
				if(GuildIndex != War.BetIndex[x][0] && GuildIndex != War.BetIndex[x][1])
					continue;
			}
			
			if(x == 2) // Checa se é a cidade de Erion
				if(player->Equip[0].EFV2 != MORTAL) // Checa se é mortal
					continue; // Se não for2, apenas continua o loop

			if(x == 3)
				if(player->Equip[0].EFV2 != ARCH) // Checa se é arch
					continue;

			// Verifica se o usuário está dentro dos limites das cidades
			if(player->LastX >= MaxMinCoordsCitys[x][0] && player->LastX <= MaxMinCoordsCitys[x][2] && 
			   player->LastY >= MaxMinCoordsCitys[x][1] && player->LastY <= MaxMinCoordsCitys[x][3])
			{
				if(War.Owner[x])
				{
					// Checa se o player é da guild desafiante
					if(GuildIndex == War.BetIndex[x][0] && Chall < MAX_USER_WAR)
					{
						// Adiciona o player a struct de quem está na guerra
						War.DefyTeam[x][Chall] = y;
						// Manda o personagem para a área de guerra
						SendClientMessage(y, "Você foi convocado para a Guerra entre Guildas.");
						DoTeleport(y, DestCoordsWar[x][0], DestCoordsWar[x][1]);
						wdBuffer[y].Ingame.cantRessurect = true;
						// Adiciona que mais um player foi convocado para a Guerra
						Chall++;
						War.TeamCount[x][1]++;
					}
					// Checa se o player é da guild defensora
					else if(GuildIndex == War.Owner[x] && Owner < MAX_USER_WAR)
					{
						// Adiciona o player a struct de quem está na guerra
						War.OwnerTeam[x][Owner] = y;
						// Manda o personagem para a área de guerra
						SendClientMessage(y, "Você foi convocado para a Guerra entre Guildas.");
						DoTeleport(y, DestCoordsWar[x][2], DestCoordsWar[x][3]);
						wdBuffer[y].Ingame.cantRessurect = true;
						// Adiciona que mais um player foi convocado para a Guerra
						Owner++;
						War.TeamCount[x][0]++;
					}
				}
				else
				{
					// Checa se o player é da guild desafiante
					if(GuildIndex == War.BetIndex[x][0] && Chall < MAX_USER_WAR)
					{
						// Adiciona o player a struct de quem está na guerra
						War.DefyTeam[x][Chall] = y;
						// Manda o personagem para a área de guerra
						SendClientMessage(y, "Você foi convocado para a Guerra entre Guildas.");
						DoTeleport(y, DestCoordsWar[x][0], DestCoordsWar[x][1]);
						wdBuffer[y].Ingame.cantRessurect = true;
						// Adiciona que mais um player foi convocado para a Guerra
						Chall++;
						War.TeamCount[x][1]++;
					}
					// Checa se o player é da guild defensora
					else if(GuildIndex == War.BetIndex[x][1] && Owner < MAX_USER_WAR)
					{
						// Adiciona o player a struct de quem está na guerra
						War.OwnerTeam[x][Owner] = y;
						// Manda o personagem para a área de guerra
						SendClientMessage(y, "Você foi convocado para a Guerra entre Guildas.");
						DoTeleport(y, DestCoordsWar[x][2], DestCoordsWar[x][3]);
						wdBuffer[y].Ingame.cantRessurect = true;
						// Adiciona que mais um player foi convocado para a Guerra
						Owner++;
						War.TeamCount[x][0]++;
					}
				}
				if(Owner == MAX_USER_WAR && Chall == MAX_USER_WAR)
				{
					break;
				}
			}
		}

		War.Iniciada[x] = true;

		if(War.Owner[x])
		{
			War.WarIndexs[x][0] = War.Owner[x];
			War.WarIndexs[x][1] = War.BetIndex[x][0];
		}
		else
		{
			War.WarIndexs[x][0] = War.BetIndex[x][0];
			War.WarIndexs[x][1] = War.BetIndex[x][1];
		}
	}

	return;
}

int GetCity(int cId)
{
	if(cId < 0 || cId > 750)
		return -1;

	INT8 CityId = -1;

	st_Mob *player = GetMobFromIndex(cId);

	for(int x=0; x < 4; x++)
	{
		if(player->LastX >= MaxMinCoordsCitys[x][0] && player->LastX <= MaxMinCoordsCitys[x][2] &&
		   player->LastY >= MaxMinCoordsCitys[x][1] && player->LastY <= MaxMinCoordsCitys[x][3])
		{
			CityId = x;
			break;
		}
	}

	if(CityId < 0 || CityId > 3)
		return -1;

	return CityId;
}

void WINAPI PremiumDelivery()
{
	// Um clientId será sorteado para receber um prêmio de acordo com o dia da semana
	bool Delivered = false;

	INT16 cId = 0;

	do
	{
		// Garante que haverão realmente resultados aleatorios
		srand(time(NULL) / 5 * (rand() % 500) * 5);

		cId = rand() % 750;

		if(Users[cId].Status == 22)
		{
			Delivered = true;

			st_Item Premium;

			memset(&Premium, 0x0, sizeof st_Item);

			Premium.Index = 3448;
			Premium.EF1 = 61;
			Premium.EFV1 = 10;

			if(!PutItem(cId, &Premium))
				if(!PutItemnInv(cId, &Premium))
					Delivered = false;
		}
	}while(!Delivered);

	st_Mob *Lucky = GetMobFromIndex(cId);

	char szMsg[108];

	sprintf(szMsg, "[Notícia]: O jogador %s foi premiado.", Lucky->Name);

	sD1D(0x7530, 0, szMsg, MSG_COLOR_GIFT);

	sprintf(szMsg, "!Parabéns, você acaba de receber um presente do servidor!");
	SendClientMessage(cId, szMsg);

	return;
}

void SendClientMsg(int cID, char *msg, ...)
{
    char buff[1000];

    va_list va;
    va_start(va, msg);
    vsprintf(buff, msg, va);
    va_end(va);
    SendClientMessage(cID, buff);
}