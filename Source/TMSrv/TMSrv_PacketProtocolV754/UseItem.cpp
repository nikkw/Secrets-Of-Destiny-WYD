#include "DLLMain.h"

void UseItens(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373 *p = (p373*)m_PacketBuffer;

	INT cId = p->Header.ClientId;

	st_Mob *player = (st_Mob*)GetMobFromIndex(cId);

	st_Item *srcItem = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(cId <= NULL || cId > MAX_PLAYER)
		return;

	else if(p->SrcSlot < 0 || p->SrcSlot > 63 || p->DstSlot < 0 || p->DstSlot > 63 || p->DstType < 0 || p->DstType > 2)
	{
		*pRetn = true; 

		CloseUser(cId);

		return;
	}

	else if(p->SrcType != INVENTORY)
	{
		*pRetn = true;

		SendClientMessage(p->Header.ClientId, "Passe o item para o inventário antes de utilizá-lo.");
		return;
	}

	else if(srcItem == NULL)
		return;

	else if(player->Status.curHP <= NULL)
		return;

	else if(srcItem->Index <= NULL || srcItem->Index > MAX_ITEMLIST)
		return;
			
	switch(srcItem->Index)
	{
		case 413: case 412:
			UseLac(m_PacketBuffer, pRetn);
			break;

		case 600:
			RecallRvR(m_PacketBuffer, pRetn);
			break;

		case 667: case 668: case 669: 
		case 670: case 671:
			ProcessSephiraBook(m_PacketBuffer, pRetn);
			break;

		case 1728:
		    Fogos(m_PacketBuffer, pRetn);
		    break;

		case 1731: case 3171: case 3172:
			Cartas(m_PacketBuffer, pRetn);
			break;

		case 1739:
			ChocAmor(m_PacketBuffer, pRetn);
			break;
				
		case 3020:
			PedraFuria(m_PacketBuffer, pRetn);
			break;

		case 3021: case 3022: 
		case 3023: case 3024: 
		case 3025: case 3026:
			Extracoes(m_PacketBuffer, pRetn);
			break;

		case 3027: case 3028:
		case 3029: case 3030:
			BarrasMithril(m_PacketBuffer, pRetn);
			break;

		case 777:  case 778:  case 779:  case 780:
		case 781:  case 782:  case 783:  case 784:
		case 3173: case 3174: case 3175: case 3176: 
		case 3177: case 3178: case 3179: case 3180: 
		case 3182: case 3183: case 3184: case 3185: 
		case 3186: case 3187: case 3188: case 3189: 
			Water(m_PacketBuffer, pRetn);
			break;

		case 785: case 3181: case 3190:
			BossWater(m_PacketBuffer, pRetn);
			break;

		case 3200: case 3201:
		case 3202: case 3204: 
		case 3205: case 3206:
		case 3208: case 3209:
			Joias(m_PacketBuffer, pRetn);
			break;

		case 3203:
			RemoveCancel(m_PacketBuffer, pRetn);
			break;

		case 3210:
			NewInv(m_PacketBuffer, pRetn);
			break;

		case 3314:
			Frango(m_PacketBuffer, pRetn);
			break;

		case 3315:
			CurarMontaria(m_PacketBuffer, pRetn);
			break;

		case 3316: case 3317:
			CatalizarLevel(m_PacketBuffer, pRetn);
			break;

		case 3221:
			Item_VIP(m_PacketBuffer, pRetn);
			break;

		case 3324: case 3325: case 3326:
			NightMare(m_PacketBuffer, pRetn);
			break;

		case 3343:
		    CaosPoint(m_PacketBuffer, pRetn);
		    break;

		case 3351: case 3352: case 3353: 
		case 3354: case 3355: case 3356: case 3357:
			RestaurarMontarias(m_PacketBuffer, pRetn);
			break;
			
		case 3386:
		case 3387:
		case 3388:
		case 3389:
			Gemas(m_PacketBuffer, pRetn);
			break;

		case 3394: case 3395: case 3396:
			DonateBars(m_PacketBuffer, pRetn);
			break;

		case 3407: case 3408: case 3409:
		case 3410: case 3411: case 3412:
		case 3413: case 3414: case 3415: case 3416:
			Tinturas(m_PacketBuffer, pRetn);
			break;

		case 3417:
			RemoveTinturas(m_PacketBuffer, pRetn);
			break;

		case 400:  case 401:  case 402:
		case 403:  case 404:  case 405:
		case 406:  case 407:  case 408:
		case 409:  case 428:  case 429:
		case 430:  case 431:  case 432:
		case 433:  case 434:  case 435:
		case 680:  case 681:  case 682:
		case 683:  case 684:  case 685:
		case 686:  case 687:  case 688:
		case 689:  case 690:  case 691:
		case 3322: case 3323: case 3431: 
		case 3472: case 3477: case 4097:
			Pots(m_PacketBuffer, pRetn);
			break;

		case 3432: case 3433: case 3434: 
		case 3435: case 3436: case 3437:
			ProcessHuntingScrolls(m_PacketBuffer, pRetn);
			break;

		case 3445: case 3446:
			AgruparPoeiras(m_PacketBuffer, pRetn);
			break;

		case 3447: case 3448:
			DesagruparPoeiras(m_PacketBuffer, pRetn);
			break;

		case 4010: case 4011: case 4026: 
		case 4027: case 4028: case 4029:
		case 5359: case 5360:
			Barras(m_PacketBuffer, pRetn);
			break;
		
		case 4016: case 4017: case 4018:
		case 4019: case 4020: case 4021:
		case 4022: case 4023: case 4024:
			Replations(m_PacketBuffer, pRetn);
			break;

		case 4106: case 4107: case 4108: case 4109:
			Cristais(m_PacketBuffer, pRetn);
			break;

		case 4117: case 4118: case 4119:
		case 4120: case 4121:
			QuestItens(m_PacketBuffer, pRetn);
			break;

		case 4122:
			MolarGargula(m_PacketBuffer, pRetn);
			break;

		case 4141:
			Lac100(m_PacketBuffer, pRetn);
			break;

		case 4140:
		case 4144:
			BauExp(m_PacketBuffer, pRetn);
			break;

		case 4146:
			SeloGuerreiro(m_PacketBuffer, pRetn);
			break;

		case 4148:
			Misteriosa(m_PacketBuffer, pRetn);
			break;

		case 4111: case 4112: case 4113:
			Lans(m_PacketBuffer, pRetn);
			break;

		case 4905:
			MoneyCube(m_PacketBuffer, pRetn);
			break;

		case 5338:
			Ideal(m_PacketBuffer, pRetn);
			break;
	}

	if(*pRetn)
	{
		char szLog[108];

		sprintf(szLog, "%s Usou item %s.", player->Name, ItemList[srcItem->Index].Name);

		//SendLog(Users[p->Header.ClientId].Username, szLog);
	}
}

void MolarGargula(UINT8* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);

	if(player->Equip[0].EFV2 != MORTAL)// Mortais apenas
	{
		SendItem(cId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(cId, "Item exclusivo para Mortais.");

		return;
	}

	if(player->Status.Level < 200 || player->Status.Level > 204)// 201 ao 205
	{
		SendItem(cId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(cId, "Possível utilizar este item apenas entre os níveis 201 - 205.");

		return;

	}

	if(wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.MolarGargula)// Já completou a quest
	{
		SendItem(cId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(cId, "Você já participou desta quest.");

		return;
	}

	if(player->Equip[1].Index >= 3500 && player->Equip[1].Index <= 3507)// Não pode refinar tiaras
	{
		SendItem(cId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(cId, "Nesta quest é impossível refinar Cythera.");

		return;
	}

	wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.MolarGargula = TRUE;

	for(INT8 i = 1; i < 6; i++)
	{
		SetItemSanc(&player->Equip[i], 6);

		SendItem(cId, EQUIP, i, &player->Equip[i]);
	}

	AmountMinus(&player->Inventory[p->SrcSlot]);

	SendEffect(cId, 0XE, 3);

	SendClientMessage(cId, "Quest Molar do Gargula concluída.");
}

void RemoveCancel(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);

	st_Item *srcItem  = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot);

	for(int i = 0; i < MAX_AFFECTS; i++)
	{
		if(mBuffer[cId].Affects[i].Index == 18)
		{
			AmountMinus(srcItem);
			
			memset(&mBuffer[cId].Affects[i], 0x0, sizeof(stAffects));

			GetCurrentScore(cId);

			SendScore(cId);

			printf("Chegay\n");
			return;
		}
	}
	printf("Passei direto\n");
	SendItem(cId, p->SrcType, p->SrcSlot, srcItem);
}

void RestaurarMontarias(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);

	st_Item *srcItem  = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem  = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(p->DstSlot != 14 || !dstItem)
	{
		SendItem(cId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(cId, "Usado somente em montarias.");

		return;
	}

	if(dstItem->EFV2 < 1 || dstItem->EFV2 >= 60)
	{
		SendItem(cId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(cId, "Vitalidade da montaria está no máximo.");

		return;
	}

	if(!CheckMount(srcItem, dstItem->Index))
    {
		SendItem(cId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(cId, "Usado apenas nas montarias citadas na descrição.");

		return;
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	static INT8 RandomVita[3] = {1, 2, 3};

	dstItem->EFV2 += RandomVita[rand() % 3]; // 1~2~3

	if(dstItem->EFV2 > 60)
		dstItem->EFV2 = 60;

	AmountMinus(srcItem);

	SendItem(cId, EQUIP, p->DstSlot, dstItem);

	SendClientMessage(cId, "Montaria refinada com sucesso.");
}

void Cartas(UINT8 *m_buffer, bool *pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_buffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(player->Leader || player->Leader == -1)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Apenas o líder pode usar este item.");

		return;
	}
	else if(Carta.isOn)
	{
		SendClientMessage(p->Header.ClientId, "Quest já está ativa, tente novamente mais tarde.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(srcItem->Index == 1731)
		Carta.Type = 1;
	else if(srcItem->Index == 3171)
		Carta.Type = 2;
	else if(srcItem->Index == 3172)
		Carta.Type = 3;
	else
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Ocorreu um erro com esse sistema, contate à Administração.");

		return;
	}

	Carta.isOn = true;
	Carta.canGo = false;

	Carta.cIds[0] = p->Header.ClientId;
	Carta.MobsLeft = CartasNum[Carta.Type - 1][0];
	Carta.TimeLeft = 180;
	Carta.ActualRoom = 0;
	Carta.bossState  = BOSSNAONASCIDO;

	memcpy(&Carta.cIds[1], player->PartyList, sizeof(INT16) * 12);

	DoTeleport(p->Header.ClientId, TeleportCarta[0][0], TeleportCarta[0][1]);
	TeleportPeople(player->PartyList, TeleportCarta[0][0], TeleportCarta[0][1]);

	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A1, Carta.TimeLeft);
	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3B0, Carta.MobsLeft);

	for(INT8 party = 1; party < 13; party++)
	{
		if(player->PartyList[party] < 0 || player->PartyList[party] > MAX_PLAYER)
			continue;

		if(Users[player->PartyList[party]].Status != 22)
			continue;

		SendClientSignalParm(Carta.cIds[party], 0x7530, 0x3A1, Carta.TimeLeft);
		SendClientSignalParm(Carta.cIds[party], 0x7530, 0x3B0, Carta.MobsLeft);
	}

	KillMobsOnArea(LettersVCoords[0][0], LettersVCoords[0][1], LettersVCoords[0][2], LettersVCoords[0][3]);

	for(INT8 MobCount = 0; MobCount < 25; MobCount++)
	{
		CreateMob(CartasMobs[Carta.Type - 1][0], LettersSMCoords[0][0][0], LettersSMCoords[0][0][1], "npc");
		CreateMob(CartasMobs[Carta.Type - 1][0], LettersSMCoords[0][1][0], LettersSMCoords[0][1][1], "npc");
		CreateMob(CartasMobs[Carta.Type - 1][0], LettersSMCoords[0][2][0], LettersSMCoords[0][2][1], "npc");
		CreateMob(CartasMobs[Carta.Type - 1][0], LettersSMCoords[0][3][0], LettersSMCoords[0][3][1], "npc");
	}

	AmountMinus(srcItem);
}

void BarrasMithril(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	static const UINT8 Add[4][2] = { 
		{6,  9},
		{2,  4},
		{6,  0},
		{5,  0}
	};

	static const UINT8 AddTypes[4] = {EF_DAMAGE, EF_MAGIC, EF_AC, EF_CRITICAL};

	static const UINT8 MaxAdds[4][2] = { 
		{42, 81},
	    {14, 36},
		{70,  0},
		{90, 30}
	};

	if(srcItem->Index < 3027 || srcItem->Index > 3030)
		return;

	UINT8 Type = srcItem->Index - 3027;

	if(Type < 0 || Type > 3)
	{
		SendClientMessage(p->Header.ClientId, "Erro no Type do Item, entre em contato com à Administração.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, srcItem);

		return;
	}

	UINT8 Armor = 0;

	if(ItemList[dstItem->Index].Pos == ARMA_TYPE1 || ItemList[dstItem->Index].Pos == ARMA_TYPE2)
		Armor = 1;
	else if(ItemList[dstItem->Index].Pos != ELMO_TYPE && ItemList[dstItem->Index].Pos != PEITO_TYPE &&
		    ItemList[dstItem->Index].Pos != LUVA_TYPE && ItemList[dstItem->Index].Pos != BOTA_TYPE  &&
			ItemList[dstItem->Index].Pos != CALCA_TYPE)
		Armor = -1;

	if(Armor == -1)
	{
		SendClientMessage(p->Header.ClientId, "Possível usar somente em armas ou armaduras.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, srcItem);

		return;
	}

	INT8 place = -1;

	for(int e = 0; e < 3; e++)
	{
		if(dstItem->Effect[e].Index == AddTypes[Type])
		{
			// Acha em qual slot dos efs no item está o add
			place = e;

			break;
		}
	}

	if(place == -1)
	{
		SendClientMessage(p->Header.ClientId, "Necessário que o item tenha o adicional que deseja aprimorar.");
		// O item não tem o adicional para o item que ele usou
		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, srcItem);

		return;
	}
	else if(dstItem->Effect[place].Value <= Add[Type][Armor] || (dstItem->Effect[place].Value + Add[Type][Armor]) > MaxAdds[Type][Armor] || GetItemSanc(dstItem) <= 9 || (!CheckArchItem(dstItem->Index) && !CheckHardItem(dstItem->Index)))
	{
		SendClientMessage(p->Header.ClientId, "Não é possível aprimorar este item.");
		// Adicional já passou do limite ou é muito pequeno
		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, srcItem);

		return;
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Chance = rand() % 10;

	AmountMinus(srcItem);

	if(Chance <= 4)
	{
		// Falha na composição, item volta o add
		dstItem->Effect[place].Value -= Add[Type][Armor];

		SendClientMessage(p->Header.ClientId, "Falha na composição, houve queda do adicional.");
	}
	else if(Chance <= 7)
	{
		// Acertou, add sobe
		dstItem->Effect[place].Value += Add[Type][Armor];

		SendClientMessage(p->Header.ClientId, "Houve sucesso na refinação.");
	}
	else
		SendClientMessage(p->Header.ClientId, "Falha na composição.");

	SendItem(p->Header.ClientId, p->DstType, p->DstSlot, dstItem);
}

void Item_VIP(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *Item  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(isVip(p->Header.ClientId))
	{
		SendClientMessage(p->Header.ClientId, "Você já possui vip ativado, espere a data de vencimento para ativar novamente.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	UINT8  FinalDay,
		   FinalMon;
	UINT16 FinalYear;
			
	FinalDay  = now->tm_mday;
	FinalMon  = now->tm_mon + 2;
	FinalYear = now->tm_year + 1900;

	if(FinalMon >= 13)
	{
		FinalMon = 1;
		FinalYear++;
	}

	if((now->tm_mon + 1) == 1 && now->tm_mday >= 29)
	{
		FinalMon = 2;

		if(now->tm_mday >= 29 && now->tm_mday <= 31) 
			FinalDay = now->tm_mday - 28;
	}

	wdBuffer[p->Header.ClientId].VipInfo.Date.Ano = FinalYear;
	wdBuffer[p->Header.ClientId].VipInfo.Date.Dia = FinalDay;
	wdBuffer[p->Header.ClientId].VipInfo.Date.Mes = FinalMon;

	wdBuffer[p->Header.ClientId].VipInfo.Type = PLUS;

	AmountMinus(Item);

	char tmp[108];
	sprintf_s(tmp, "Vip ativado até [%02d/%02d/%04d].", wdBuffer[p->Header.ClientId].VipInfo.Date.Dia, wdBuffer[p->Header.ClientId].VipInfo.Date.Mes, wdBuffer[p->Header.ClientId].VipInfo.Date.Ano);

	SendClientMessage(p->Header.ClientId, tmp);
}

void PedraFuria(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *Item  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(player->Equip[0].EFV2 < CELESTIAL)
	{
		SendClientMessage(p->Header.ClientId, "Não há quests a serem concluídas.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}
	else if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame < 500)
	{
		SendClientMessage(p->Header.ClientId, "Necessário possuir 500 de Fame para prosseguir.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}
	else if(player->bStatus.Level < 199)
	{
		if(player->bStatus.Level == 89)
		{
			if(!wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Block90Cele)
			{
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Block90Cele = TRUE;

				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame -= 500;

				AmountMinus(Item);

				SendClientMessage(p->Header.ClientId, "Nível foi desbloqueado com sucesso.");

				return;
			}
			
			SendClientMessage(p->Header.ClientId, "Desbloqueio só pode ser feito uma vez.");

		    SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

			return;
		}

		SendClientMessage(p->Header.ClientId, "Somente no level 200.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}
	else if(player->Equip[1].Index != 3502 || GetItemSanc(&player->Equip[1]) < 234)
	{
		SendClientMessage(p->Header.ClientId, "Equipe uma Cythera Mística superior a +10.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}
	else if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Arcana)
	{
		SendClientMessage(p->Header.ClientId, "Só é possível concluir esta quest uma vez.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}

	INT16 Agua = GetFirstSlot(p->Header.ClientId, 5334, INVENTORY),
		  Terra = GetFirstSlot(p->Header.ClientId, 5335, INVENTORY),
		  Sol = GetFirstSlot(p->Header.ClientId, 5336, INVENTORY),
		  Vento = GetFirstSlot(p->Header.ClientId, 5337, INVENTORY);

	if(Agua == -1 || Terra == -1 || Sol == -1 || Vento == -1)
	{
		SendClientMessage(p->Header.ClientId, "Necessário possuir as 4 pedras secretas.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}

	AmountMinus(&player->Inventory[Agua]);
	AmountMinus(&player->Inventory[Sol]);
	AmountMinus(&player->Inventory[Terra]);
	AmountMinus(&player->Inventory[Vento]);
	AmountMinus(Item);

	SendItem(p->Header.ClientId, EQUIP, 1, &player->Inventory[Agua]);
	SendItem(p->Header.ClientId, EQUIP, 1, &player->Inventory[Sol]);
	SendItem(p->Header.ClientId, EQUIP, 1, &player->Inventory[Terra]);
	SendItem(p->Header.ClientId, EQUIP, 1, &player->Inventory[Vento]);

	wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame -= 500;

	if(rand() % 2)
	{
		player->Equip[1].Index = 3507;
		
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Arcana = TRUE;

		SendItem(p->Header.ClientId, EQUIP, 1, &player->Equip[1]);

		SendClientMessage(p->Header.ClientId, "Sucesso na composição.");
	}
	else
		SendClientMessage(p->Header.ClientId, "Falha na composição.");
}

void QuestItens(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *Item  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(Item->Index < 4117 || Item->Index > 4121)
		return;

	INT8 ActualQuest = -1;

	char szMsg[108];

	ActualQuest = Item->Index - 4117; 

	if(ActualQuest < 0 || ActualQuest > 4)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, Item);

		SendClientMessage(p->Header.ClientId, "Erro no Type do item, entre em contato com à Administração.");

		return;
	}

	if(player->bStatus.Level < Quests_Level[ActualQuest][0] || player->bStatus.Level > Quests_Level[ActualQuest][1] || player->Equip[0].EFV2 != MORTAL)
	{
		sprintf(szMsg, "Somente mortais entre os níveis: %d e %d", Quests_Level[ActualQuest][0] + 1, Quests_Level[ActualQuest][1] + 1);

		SendClientMessage(p->Header.ClientId, szMsg);

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, Item);

		return;
	}

	AmountMinus(Item);

	player->Exp += ExpQuests[ActualQuest];

	if(ActualQuest)
	{
		if((player->Gold + ExpQuests[ActualQuest]) <= 2000000000)
			player->Gold += ExpQuests[ActualQuest];
		else
			player->Gold = 2000000000;
	}

	if(player->Leader && player->Leader != -1)
	{
		st_Mob *Lider = GetMobFromIndex(player->Leader);

		Lider->Exp += ExpQuests[ActualQuest] / 10;
			
		if(Lider->Gold + (ExpQuests[ActualQuest] / 10) > 2000000000)
			Lider->Gold = 2000000000;
		else
			Lider->Gold + (ExpQuests[ActualQuest] / 10);

		SendEtc(player->Leader);

		for(int i = 0; i < 12; i++)
		{
			if(!Lider->PartyList[i])
				continue;

			if(Users[Lider->PartyList[i]].Status != 22)
				continue;

			if(Lider->PartyList[i] < 0 || Lider->PartyList[i] > MAX_PLAYER)
				continue;

			if(Lider->PartyList[i] == p->Header.ClientId)
				continue;

			st_Mob *tmpMob = GetMobFromIndex(Lider->PartyList[i]);

			tmpMob->Exp += ExpQuests[ActualQuest] / 10;
			
			if(tmpMob->Gold + (ExpQuests[ActualQuest] / 10) > 2000000000)
				tmpMob->Gold = 2000000000;
			else
				tmpMob->Gold + (ExpQuests[ActualQuest] / 10);

			sprintf(szMsg, "++++ %d ++++", ExpQuests[ActualQuest] / 10);

			SendClientMessage(Lider->PartyList[i], szMsg);

			SendEtc(Lider->PartyList[i]);

			SendEffect(Lider->PartyList[i], 0x0E, 1);
		}
	}
	else
	{
		for(int i = 0; i < 12; i++)
		{
			if(player->PartyList[i] <= 0 || player->PartyList[i] > MAX_PLAYER)
				continue;

			if(Users[player->PartyList[i]].Status != 22)
				continue;

			if(player->PartyList[i] == p->Header.ClientId)
				continue;

			st_Mob *tmpMob = GetMobFromIndex(player->PartyList[i]);

			tmpMob->Exp += ExpQuests[ActualQuest] / 10;
			
			if(tmpMob->Gold + (ExpQuests[ActualQuest] / 10) > 2000000000)
				tmpMob->Gold = 2000000000;
			else
				tmpMob->Gold + (ExpQuests[ActualQuest] / 10);

			sprintf(szMsg, "++++ %d ++++", ExpQuests[ActualQuest] / 10);

			SendClientMessage(player->PartyList[i], szMsg);

			SendEtc(player->PartyList[i]);

			SendEffect(player->PartyList[i], 0x0E, 1);
		}
	}

	sprintf(szMsg, "++++ %d ++++", ExpQuests[ActualQuest]);

	SendClientMessage(p->Header.ClientId, szMsg);

	SendEtc(p->Header.ClientId);

	SendEffect(p->Header.ClientId, 0x0E, 1);
}

void SeloGuerreiro(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn =  true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame += 10;

	AmountMinus(srcItem);

	SendEffect(p->Header.ClientId, 0XE, 3);

	if(player->Equip[0].EFV2 == ARCH && player->bStatus.Level == 354) 
	{
		if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.SeloArch355)
			return;//Já completou a quest

		if(player->CapeInfo == 7) // Blue
			player->Equip[15].Index = 3191;
		else if(player->CapeInfo == 8) // Red
			player->Equip[15].Index = 3192;
		else // White
			player->Equip[15].Index = 3193;

		SendItem(p->Header.ClientId, EQUIP, 15, &player->Equip[15]);

		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.SeloArch355 = TRUE;
	}
}

void CaosPoint(UINT8* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	player->Inventory[63].EF1 = 150;

	SendCreateMob(p->Header.ClientId, p->Header.ClientId, 1);

	AmountMinus(&player->Inventory[p->SrcSlot]);
}

void Extracoes(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(dstItem == NULL)
		return;

	INT16 Type = srcItem->Index - 3021;

	if(srcItem->Index < 3021 || srcItem->Index > 3026)
	{
		SendClientMessage(p->Header.ClientId, "Erro na função, entre em contato com à Administração.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(dstItem->Index >= 3500 && dstItem->Index <= 3507)
	{
		SendClientMessage(p->Header.ClientId, "Não é possível utilizar em Cytheras.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(!dstItem->Index || p->DstType != EQUIP)
	{
		SendClientMessage(p->Header.ClientId, "Não possui nenhum item para utilizar extração.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(p->DstSlot != Type + 1)
	{
		SendClientMessage(p->Header.ClientId, "Este Slot não é apropriado para esta Extração.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	if(!dstItem->EF1 && !dstItem->EF2 && !dstItem->EF3)
	{
		if((Rand() % 50) <= 40)
		{
			memcpy(&dstItem->EF1, &srcItem->EF1, 6);

			AmountMinus(srcItem);

			SendClientMessage(p->Header.ClientId, "Adicional enviado para o equipamento com sucesso.");
		}
		else
		{
			AmountMinus(dstItem);

			SendClientMessage(p->Header.ClientId, "Sua extração falhou.");
		}
	}
	else
	{
		if((Rand() % 50) <= 40)
		{
			memcpy(&srcItem->EF1, &dstItem->EF1, 6);

			for(INT8 i = 0; i < 3; i++)
			{
				if(dstItem->Effect[i].Index)
					dstItem->Effect[i].Index = 0;

				if(dstItem->Effect[i].Value)
					dstItem->Effect[i].Value = 0;
			}

			SendClientMessage(p->Header.ClientId, "Adicional removido do equipamento com sucesso.");
		}
		else
		{
			AmountMinus(srcItem);

			SendClientMessage(p->Header.ClientId, "Sua extração falhou.");
		}
	}

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);
}

void Joias(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(srcItem->Index < 3200 || srcItem->Index > 3209)
		return;
		
	INT8 isJoia = -1;

	for(INT8 i = 0; i <= MAX_AFFECTS; i++)
	{
		if(mBuffer[p->Header.ClientId].Affects[i].Index == 8)
		{
			isJoia = i;
			break;
		}
	}

	if(isJoia >= 0)
	{
		mBuffer[p->Header.ClientId].Affects[isJoia].Index = 8;
		mBuffer[p->Header.ClientId].Affects[isJoia].Master = Joia[srcItem->Index - 3200];
		mBuffer[p->Header.ClientId].Affects[isJoia].Time = 420;
		mBuffer[p->Header.ClientId].Affects[isJoia].Value = Joia[srcItem->Index - 3200];
	}
	else
	{
		for(INT8 i = 0; i <= MAX_AFFECTS; i++)
		{
			if(mBuffer[p->Header.ClientId].Affects[i].Index == 0)
			{
				mBuffer[p->Header.ClientId].Affects[i].Index = 8;
				mBuffer[p->Header.ClientId].Affects[i].Master = Joia[srcItem->Index - 3200];
				mBuffer[p->Header.ClientId].Affects[i].Time = 420;
				mBuffer[p->Header.ClientId].Affects[i].Value = Joia[srcItem->Index - 3200];
				break;
			}
		}
	}

	GetCurrentScore(p->Header.ClientId);	

	SendScore(p->Header.ClientId);

	AmountMinus(srcItem);
}

void Frango(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);
		
	INT8 isFrango = -1;

	for(INT8 i = 0; i <= MAX_AFFECTS; i++)
	{
		if(mBuffer[p->Header.ClientId].Affects[i].Index == 30)
		{
			isFrango = i;
			break;
		}
	}

	if(isFrango >= 0)
	{
		mBuffer[p->Header.ClientId].Affects[isFrango].Index = 30;
		mBuffer[p->Header.ClientId].Affects[isFrango].Master = 30;
		mBuffer[p->Header.ClientId].Affects[isFrango].Time = 1800.4;
		mBuffer[p->Header.ClientId].Affects[isFrango].Value = 30;
	}
	else
	{
		for(INT8 i = 0; i <= MAX_AFFECTS; i++)
		{
			if(mBuffer[p->Header.ClientId].Affects[i].Index == 0)
			{
				mBuffer[p->Header.ClientId].Affects[i].Index = 30;
				mBuffer[p->Header.ClientId].Affects[i].Master = 30;
				mBuffer[p->Header.ClientId].Affects[i].Time = 1800.4;
				mBuffer[p->Header.ClientId].Affects[i].Value = 30;
				break;
			}
		}
	}

	GetCurrentScore(p->Header.ClientId);	

	SendScore(p->Header.ClientId);

	AmountMinus(srcItem);
}

void Fogos(UINT8* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	SendEffect(p->Header.ClientId, 100, (Rand() % 6));

	AmountMinus(srcItem);
}

void ChocAmor(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	Buff(p->Header.ClientId, 2000, 2000, 43);
	Buff(p->Header.ClientId, 2000, 2000, 44);
	Buff(p->Header.ClientId, 2000, 2000, 45);

	GetCurrentScore(p->Header.ClientId);

	SendScore(p->Header.ClientId);

	AmountMinus(srcItem);
}

void Lans(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	static const INT16 Infos[][3] = 
	{
		{3683, 3640, MORTAL},
		{3810, 3525, ARCH},
		{3908, 3652, CELESTIAL}
	};

	INT8 Index = srcItem->Index - 4111;

	if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Cidadania != SERV_1)
	{
		SendClientMessage(p->Header.ClientId, "Para utilizar este item, é necessário ser cidadão deste canal.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);
		return;
	}

	if(player->Equip[0].EFV2 >= Infos[Index][2])
	{
		AmountMinus(srcItem);

		DoTeleport(p->Header.ClientId, Infos[Index][0], Infos[Index][1]);
	}
	else
	{
		SendClientMessage(p->Header.ClientId, "Desculpe.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);
		return;
	}
}

void BauExp(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);
		
	INT8 isBau = -1;

	for(INT8 i = 0; i <= MAX_AFFECTS; i++)
	{
		if(mBuffer[p->Header.ClientId].Affects[i].Index == 39)
		{
			isBau = i;
			break;
		}
	}

	if(isBau >= 0)
	{
		mBuffer[p->Header.ClientId].Affects[isBau].Index = 39;
		mBuffer[p->Header.ClientId].Affects[isBau].Time += 900.4;
		mBuffer[p->Header.ClientId].Affects[isBau].Master = 39;
		mBuffer[p->Header.ClientId].Affects[isBau].Value = 39;
	}
	else
	{
		for(INT8 i = 0; i <= MAX_AFFECTS; i++)
		{
			if(mBuffer[p->Header.ClientId].Affects[i].Index == 0)
			{
				mBuffer[p->Header.ClientId].Affects[i].Index = 39;
				mBuffer[p->Header.ClientId].Affects[i].Time  = 900.4;
				mBuffer[p->Header.ClientId].Affects[i].Master = 39;
				mBuffer[p->Header.ClientId].Affects[i].Value = 39;
				break;
			}
		}
	}

	GetCurrentScore(p->Header.ClientId);	

	SendScore(p->Header.ClientId);

	AmountMinus(srcItem);
}

void Pots(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	*pRetn = true;

	for(INT8 i = 0; i <= MAX_AFFECTS; i++)
		if(mBuffer[p->Header.ClientId].Affects[i].Index == 47)
			return;
	
	Users[p->Header.ClientId].Potion.CountHp += (BASE_GetItemAbility(srcItem, EF_HP) + BASE_GetItemAbility(srcItem, EF_HPADD) + BASE_GetItemAbility(srcItem, EF_HPADD2));
	Users[p->Header.ClientId].Potion.CountMp += (BASE_GetItemAbility(srcItem, EF_MP) + BASE_GetItemAbility(srcItem, EF_MPADD) + BASE_GetItemAbility(srcItem, EF_MPADD2));

	AmountMinus(srcItem);
}

void CurarMontaria(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);
    
	st_Item *srcItem = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(!dstItem)
	{
		printf("NULL\n");

		return;
	}

	if(p->DstSlot != 14 || (dstItem->Index < 2360 || dstItem->Index > 2388))
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Usado somente em montarias.");

		return;
	}

	if(dstItem->EFV2 < 4 || dstItem->EFV2 > 59)
	{
		SendClientMessage(p->Header.ClientId, "Possível usar apenas com vitalidades entre o 4~60.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);
		
		return;
	}
	
	dstItem->EFV2++;

	SendClientMessage(p->Header.ClientId, "Foi restaurado 1 de vida da montaria.");

	AmountMinus(srcItem);

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	SendEffect(p->Header.ClientId, 0xE, 3);
}

void CatalizarLevel(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);
    
	st_Item *srcItem = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(!dstItem || p->DstType != EQUIP)
	{
		printf("NULL\n");

		return;
	}

	if(p->DstSlot != 14 || (dstItem->Index < 2360 || dstItem->Index > 2388))
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Usado somente em montarias.");

		return;
	}

	UINT8 Level    = 0,
		  MinLevel = 0;

	if(srcItem->Index == 3316)
		Level = 100;
	else if(srcItem->Index == 3317)
	{
		Level    = 120;
		MinLevel = 100;
	}

	if(dstItem->EF2 >= Level  || dstItem->EF2 < MinLevel || dstItem->EFV2 < 3)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Não é possível melhorar sua montaria.");

		return;
	}

	AmountMinus(srcItem);

	dstItem->EF2 = Level;

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	SendClientMessage(p->Header.ClientId, "Sua montaria foi melhorada.");
}

void Lac100(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);
    
	st_Item *srcItem = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(!dstItem || p->DstType != EQUIP)
	{
		printf("NULL\n");

		return;
	}

	for(INT16 i = 0; i < sizeof(DontRefine) / sizeof(INT16); i++)
	{
		if(dstItem->Index == DontRefine[i])
		{
			SendClientMessage(p->Header.ClientId, "Impossível refinar este item.");

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

			return;
		}
	}

	if(p->DstSlot < 1 || p->DstSlot == 14)
	{
		SendClientMessage(p->Header.ClientId, "Usado somente para os equipamentos.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(GetItemSanc(dstItem) == 9 || GetItemSanc(dstItem) > 233)
	{
		SendClientMessage(p->Header.ClientId, "Impossível refinar mais este item.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	AmountMinus(srcItem);

	if(GetItemSanc(dstItem) >= 230 && GetItemSanc(dstItem) <= 233)
		RefinarItemMais(dstItem, 4);
	else if(GetItemSanc(dstItem) >= 0 && GetItemSanc(dstItem) < 9)
		RefinarItemMais(dstItem, 1);

	SendEffect(p->Header.ClientId, 0xE, 3);

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	SendClientMessage(p->Header.ClientId, "Refinação sucedida.");
}	

void Cristais(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(player->Status.Level < 355)
	{
		SendClientMessage(p->Header.ClientId, "Esta quest só pode ser realizada após o level 355.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(player->Equip[0].EFV2 != ARCH)
	{
		SendClientMessage(p->Header.ClientId, "Somente archs podem realizar esta quest.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	switch(srcItem->Index)
	{
		case 4106:// Elime
		{
			if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalElime)
			{
				SendClientMessage(p->Header.ClientId, "Esta quest pode ser realizada apenas uma vez.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

				return;
			}

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalElime = TRUE;
		}
		break;

		case 4107:// Sylphed
		{
			if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalSylphed)
			{
				SendClientMessage(p->Header.ClientId, "Esta quest pode ser realizada apenas uma vez.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);
				
				return;
			}

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalSylphed = TRUE;
		}
		break;

		case 4108:// Thelion
		{
			if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalThelion)
			{
				SendClientMessage(p->Header.ClientId, "Esta quest pode ser realizada apenas uma vez.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

				return;
			}

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalThelion = TRUE;
		}
		break;

		case 4109:// Noas
		{
			if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalNoas)
			{
				SendClientMessage(p->Header.ClientId, "Esta quest pode ser realizada apenas uma vez.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

				return;
			}

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.CristalNoas = TRUE;
		}
		break;
		
	}

	AmountMinus(srcItem);

	player->Exp -= 100000000;

	GetCurrentScore(p->Header.ClientId);

	SendEtc(p->Header.ClientId);
	
	SendStats(p->Header.ClientId);
	
	SendScore(p->Header.ClientId);
	
	SendClientMessage(p->Header.ClientId, "Quest concluida.");
}

void NewInv(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].nInvent.hasBuyed)
	{
		SendClientMessage(p->Header.ClientId, "Somente é possível ativar uma vez.");
		
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		return;
	}

	AmountMinus(srcItem);

	wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].nInvent.hasBuyed = true;

	memset(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].nInvent.sInv1, 0x0, sizeof st_Item * 63 );

	memset(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].nInvent.sInv2, 0x0, sizeof st_Item * 63 );

	SendClientMessage(p->Header.ClientId, "!Novo inventário ativado. Para alternar entre os dois, digite /changeinv.");	
}

void DonateBars(BYTE *m_PacketBuffer, bool *pRetn)
{
	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	*pRetn = true;

	st_Item *srcItem  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	INT8 Coins = -1;

	if(srcItem->Index == 3394)
		Coins = 1;
	else if(srcItem->Index == 3395)
		Coins = 5;
	else if(srcItem->Index == 3396)
		Coins = 10;

	if(wdBuffer[p->Header.ClientId].Cash + Coins > 65535)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(p->Header.ClientId, "Limite de donates já atingido.");
		
		return;
	}

	AmountMinus(srcItem);

	wdBuffer[p->Header.ClientId].Cash += Coins;

	char szMsg[100];
	
	sprintf_s(szMsg, "Foram adicionados %d donates, possui: %d.", Coins, wdBuffer[p->Header.ClientId].Cash);

	SendClientMessage(p->Header.ClientId, szMsg);	
}

void BossWater(BYTE* m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);
	st_Item *Item  = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot);

	if(player->LastY >= 1785 || player->LastY <= 1780 || 
	   player->LastX >= 1950 || player->LastX <= 1955)
	{
		// Coords específicas pra uso
		// Detecta se ta naquela área perto da cachoeira

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		SendClientMessage(p->Header.ClientId, "Uso somente na zona elemental da água.");

		return;
	}

	int Type = -1;

	if(Item->Index == 3181)
		Type = 0;
	else if(Item->Index == 785)
		Type = 1;
	else if(Item->Index == 3190)
		Type = 2;
	else
	{
		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		SendClientMessage(p->Header.ClientId, "Erro de typing, favor entrar em contato com a administração.");

		return;
	}

	if(Agua[Type].Rooms[8].isActive)
	{
		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		SendClientMessage(p->Header.ClientId, "Esta sala já está ocupada.");

		return;
	}

	if(player->Leader != 0 && player->Leader != -1)
	{
		SendClientMessage(p->Header.ClientId, "Uso exclusivo do líder do grupo.");

		SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, Item);

		return;
	}

	AmountMinus(Item);

	st_Position Dest;

	// Zero a var pra evitar dados desconhecidos atrapalhando o funcionamento
	memset(&Dest, 0x0, sizeof(st_Position));

	// Pega as coords pela struct
	Dest.X = BossCoords[Type][0];
	Dest.Y = BossCoords[Type][1];

	// Marca a sala como ativa e fixa o tempo restante
	Agua[Type].Rooms[8].isActive = true;
	Agua[Type].Rooms[8].Leaders = p->Header.ClientId;
	Agua[Type].Rooms[8].Cids[0] = p->Header.ClientId;
	Agua[Type].Rooms[8].TimeLeft = 120;
	Agua[Type].Rooms[8].MobsLeft = (BossNum[Type][0] + BossNum[Type][1]);

	DoTeleport(p->Header.ClientId, Dest.X + (Rand() % 2), Dest.Y + (Rand() % 2));

	// Manda o tempo verde
	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A1, 120);
	// Manda o número de Mobs
	NpcsAlive(p->Header.ClientId, Agua[Type].Rooms[8].MobsLeft, Agua[Type].Rooms[8].MobsLeft);

	SendClientMessage(p->Header.ClientId, "Bem vindo a zona elemental da água.");

	int e = 0;

	while(e < BossNum[Type][0])
	{
		e++;
		
		CreateMob(BossWaterMobs[Type][0], Dest.X, Dest.Y, "npc");
	}

	e = 0;

	while(e < BossNum[Type][1])
	{
		e++;
		
		CreateMob(BossWaterMobs[Type][1], Dest.X, Dest.Y, "npc");
	}

	for(int i = 0; i < 12; i++)
	{
		if(player->PartyList[i] > 740)
			continue;

		if(Users[player->PartyList[i]].Status != 22)
			continue;

		// Caso tenha pessoas no grupo poe na array
		// i + 1 pq o 0 é sempre o lider
		Agua[Type].Rooms[8].Cids[i + 1] = player->PartyList[i];
		// Teleporta o pessoal
		DoTeleport(player->PartyList[i], Dest.X + (Rand() % 2), Dest.Y + (Rand() % 2));
		// Msg de gay
		SendClientMessage(player->PartyList[i], "Bem vindo a zona elemental da água.");
		// Tempo verde
		SendClientSignalParm(player->PartyList[i], 0x7530, 0x3A1, 120);
		// Manda o número de Mobs
		NpcsAlive(player->PartyList[i], Agua[Type].Rooms[8].MobsLeft, Agua[Type].Rooms[8].MobsLeft);
	}
}

void Water(BYTE *m_PacketBuffer, bool *pRetn)
{
	__try
	{
		p373* p = (p373*)m_PacketBuffer;
		st_Mob *player = GetMobFromIndex(p->Header.ClientId);

		*pRetn = true;

		//if(player->LastY >= 1785 || player->LastY <= 1780 || 
		//player->LastX >= 1950 || player->LastX <= 1955)
		//{
		//	// Coords específicas pra uso
		//	// Detecta se ta naquela área perto da cachoeira

		//	SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

		//	SendClientMessage(p->Header.ClientId, "Uso somente na zona elemental da água.");

		//	return;
		//}


		st_Item *Item = &player->Inventory[p->SrcSlot];

		INT8 Type = -1;
		UINT8 Sala = -1;

		switch(Item->Index)
		{
			case 3173: case 3174: case 3175: case 3176: 
			case 3177: case 3178: case 3179: case 3180: 
			{
				Type = 0;
				Sala = Item->Index - 3173;
				break;
			}

			case 777:  case 778:  case 779:  case 780:
			case 781:  case 782:  case 783:  case 784:
			{
				Type = 1;
				Sala = Item->Index - 777;
				break;
			}

			case 3182: case 3183: case 3184: case 3185: 
			case 3186: case 3187: case 3188: case 3189:
			{
				Type = 2;
				Sala = Item->Index - 3182;
				break;
			}

			default:
				break;
		}	

		if(Type == -1 || Sala == -1 || Type > 2 || Sala > 7)
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Entre em contato com a administração, erro de typing.");

			return;
		}

		if(Agua[Type].Rooms[Sala].isActive)
		{
			// Alguém já entrou nesta sala

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Esta sala já está ocupada.");

			return;
		}

		if(player->Leader != 0 && player->Leader != -1)
		{
			SendClientMessage(p->Header.ClientId, "Uso exclusivo do líder do grupo.");

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			return;
		}

		AmountMinus(&player->Inventory[p->SrcSlot]);

		st_Position Dest;

		// Zero a var pra evitar dados desconhecidos atrapalhando o funcionamento
		memset(&Dest, 0x0, sizeof(st_Position));

		// Pega as coords pela struct
		Dest.X = WaterCoords[Type][Sala][0];
		Dest.Y = WaterCoords[Type][Sala][1];

		// Marca a sala como ativa e fixa o tempo restante
		Agua[Type].Rooms[Sala].isActive = true;
		Agua[Type].Rooms[Sala].Leaders = p->Header.ClientId;
		Agua[Type].Rooms[Sala].Cids[0] = p->Header.ClientId;
		Agua[Type].Rooms[Sala].TimeLeft = 120;
		Agua[Type].Rooms[Sala].MobsLeft = WaterNum[Type][Sala];

		DoTeleport(p->Header.ClientId, Dest.X + (Rand() % 2), Dest.Y + (Rand() % 2));

		// Manda o tempo verde
		SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A1, 120);

		// Manda o número de Mobs
		NpcsAlive(p->Header.ClientId, WaterNum[Type][Sala], WaterNum[Type][Sala]);

		int e = 0;

		while(e < WaterNum[Type][Sala])
		{
			e++;
		
			CreateMob(WaterMobs[Type][Sala], Dest.X, Dest.Y, "npc");
		}

		for(INT8 i = 0; i < 12; i++)
		{
			if(player->PartyList[i] > 740)
				continue;

			if(Users[player->PartyList[i]].Status != 22)
				continue;

			// i + 1 pq o 0 é sempre o lider
			Agua[Type].Rooms[Sala].Cids[i + 1] = player->PartyList[i];

			// Teleporta o pessoal
			DoTeleport(player->PartyList[i], Dest.X + (Rand() % 2), Dest.Y + (Rand() % 2));

			// Tempo verde
			SendClientSignalParm(player->PartyList[i], 0x7530, 0x3A1, 120);
			// Manda o número de Mobs
			NpcsAlive(player->PartyList[i], WaterNum[Type][Sala], WaterNum[Type][Sala]);
		}
	}
	__except(TRUE)
	{
	}
}

void Misteriosa(BYTE *m_PacketBuffer, bool *pRetn)
{
	__try
	{
		p373* p = (p373*)m_PacketBuffer;
		st_Mob *player = GetMobFromIndex(p->Header.ClientId);

		*pRetn = true;

		if(player->Equip[0].EFV2 < CELESTIAL || !wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.SubCeleMade || player->Equip[0].EFV2 > SCELESTIAL)
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Não pode concluir esta quest.");

			return;
		}

		INT16 otherChar = -1,
			  actualClass = -1;

		otherChar = ((player->Equip[0].EFV2 - CELESTIAL) * -1) + 1; // Pega qual o outro slot de personagem
		actualClass = player->Equip[0].EFV2 - CELESTIAL;            // Pega o slot atual de personagem
		
		if(otherChar < 0 || otherChar > 1 || actualClass < 0 || actualClass > 1)
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Houve algum erro com sua conta, por favor entre em contato com a administração.");

			return;
		}		

		if(BASE_GetVillage(player->LastX, player->LastY) == 5)
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Uso restrito a cidades.");

			return;
		}

		//salva os affects atuais
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Affects[0], &mBuffer[p->Header.ClientId].Affects[0], sizeof stAffects * 16);

		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].ClassInfo = player->ClassInfo; // Salva a classe do cele
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Exp = player->Exp; // Salva a exp do cele
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Learn = player->Learn; // Salva as skills do cele
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].MasterPoint = player->MasterPoint; // Salva os pontos
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].SkillPoint = player->SkillPoint;   // Salva os pontos
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].StatusPoint = player->StatusPoint; // Salva os pontos
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.DEX = player->bStatus.DEX; // Salva a DEX
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.INT = player->bStatus.INT; // Salva a INT
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.STR = player->bStatus.STR; // Salva a STR
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.CON = player->bStatus.CON; // Salva a CON
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.Mastery[0] = player->bStatus.Mastery[0]; // Salva as aprendizagens
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.Mastery[1] = player->bStatus.Mastery[1]; // Salva as aprendizagens
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.Mastery[2] = player->bStatus.Mastery[2]; // Salva as aprendizagens
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.Mastery[3] = player->bStatus.Mastery[3]; // Salva as aprendizagens
		wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Stats.Level = player->bStatus.Level; // Salva o level do cele
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].AffectInfo, &player->AffectInfo, sizeof(Affects));
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].Face, &player->Equip[0], sizeof(st_Item)); // Salva a face do cele
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].SkillBar1, &player->SkillBar, 4);
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[actualClass].SkillBar2, &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].SkillBar2, 16);

		if(!SaveAccount(p->Header.ClientId))
		{
			SendClientMessage(p->Header.ClientId, "Houve um erro ao salvar sua conta, favor entrar em contato com a administração.");

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			return;
		}		
		
		memcpy(&mBuffer[p->Header.ClientId].Affects[0], &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Affects[0], sizeof stAffects * 16);
		memcpy(&player->SkillBar,   &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].SkillBar1, 4);
		memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].SkillBar2, &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].SkillBar2, 16);
		memcpy(&player->AffectInfo, &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].AffectInfo, sizeof(Affects));
		memcpy(&player->Equip[0],   &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Face,       sizeof(st_Item));
	    player->ClassInfo          = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].ClassInfo;
		player->Exp                = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Exp;
		player->bStatus.Mastery[0] = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.Mastery[0];
		player->bStatus.Mastery[1] = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.Mastery[1];
		player->bStatus.Mastery[2] = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.Mastery[2];
		player->bStatus.Mastery[3] = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.Mastery[3];
		player->bStatus.Level      = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.Level;
		player->bStatus.STR        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.STR;
	    player->bStatus.DEX        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.DEX;
		player->bStatus.INT        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.INT;
		player->bStatus.CON        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Stats.CON;
		player->Learn              = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].Learn;
		player->MasterPoint        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].MasterPoint;
		player->SkillPoint         = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].SkillPoint;
		player->StatusPoint        = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].StatusPoint;
		player->ClassInfo          = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[otherChar].ClassInfo;

		BASE_GetBonusSkillPoint(player);
		BASE_GetBonusScorePoint(player);
		GetCurrentScore(p->Header.ClientId);
		BASE_GetHpMp(player);
		
		SendScore(p->Header.ClientId);
		SendStats(p->Header.ClientId);
		SendEtc(p->Header.ClientId);
		SendEquip(p->Header.ClientId);
		SendItem(p->Header.ClientId, EQUIP, 0, &player->Equip[0]);
		
		AmountMinus(&player->Inventory[p->SrcSlot]);

		BYTE packet[108]; 

		BASE_GetCreateMob(p->Header.ClientId, (BYTE*)&packet);
		GridMulticast(p->Header.ClientId, player->TargetX, player->TargetY, (void*)&packet);

		SendCreateMob(p->Header.ClientId, p->Header.ClientId, 1);		
	}
	__except(TRUE)
	{
	}
}

void Ideal(BYTE *m_PacketBuffer, bool *pRetn)
{
	__try
	{
		p373* p = (p373*)m_PacketBuffer;
		st_Mob *player = GetMobFromIndex(p->Header.ClientId);

		*pRetn = true;

		if(player->Equip[0].EFV2 < ARCH)
		{
			// Mortal
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Não há quests a serem concluídas.");

			return;
		}

		if(player->Equip[0].Index >= 22 && player->Equip[0].Index <= 25 || player->Equip[0].Index == 32)
		{
			SendClientMessage(p->Header.ClientId, "Não é possível usar transformado.");

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			return;
		}

		if(player->Status.Level <= 354 && player->Equip[0].EFV2 == ARCH)
		{
			// Arch 0~355 = HardCore
			SendClientMessage(p->Header.ClientId, "HardCore apartir de Arch não está liberado ainda.");

			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			return;
		}
	
		if(player->Status.Level > 354 && player->Equip[0].EFV2 == ARCH)
		{
			// Arch 356~400 = Celestial

			if(Users[p->Header.ClientId].CharList.Status[wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].RespectiveMortal].Level != 399)
			{
				SendClientMessage(p->Header.ClientId, "Para progredir nesta quest é necessário que seu Mortal esteja level 400.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

				return;
			}

			if(player->Status.Level > 354 && player->Status.Level < 369)
			{
				// 356~369
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Level355 = 1;
				player->Equip[1].Index = 3500;
			}

			if(player->Status.Level >= 369 && player->Status.Level < 379)
			{
				// 370~379
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Level370 = 1;
				player->Equip[1].Index = 3500;
			}

			if(player->Status.Level >= 379 && player->Status.Level <= 397)
			{
				// 380~397
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Level380 = 1;
				player->Equip[1].Index = 3501;
			}

			if(player->Status.Level == 398)
			{
				// 399
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Level398 = 1;
				player->Equip[1].Index = 3501;
			}

			if(player->Status.Level == 399)
			{
				// 400
				wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Level399 = 1;
				player->Equip[1].Index = 3502;
			}

			player->Equip[0].EFV2 = CELESTIAL; // Muda a classe do cara para cele

			player->Learn = 0; // Zera o learn 
			player->Learn |=  (1 << 30); // Entrega a Soul 

			player->Exp = 0; // Zera a exp
			player->Status.Level = 0; // Zera o Level
			player->bStatus.Level = 0; // " /\/\/\ "

			player->bStatus.DEX = 5; // Zera a DEX
			player->bStatus.STR = 5; // Zera a Str
			player->bStatus.INT = 5; // Zera a Int
			player->bStatus.CON = 5; // Zera a Con

			player->Status.Mastery[0] = 0; // Zera aprendizagem de skill
			player->Status.Mastery[1] = 0; // Zera aprendizagem de skill
			player->Status.Mastery[2] = 0; // Zera aprendizagem de skill
			player->Status.Mastery[3] = 0; // Zera aprendizagem de skill

			player->MasterPoint = 855; // Pontos de Aprendizagem

			memset(&player->Equip[15], 0x0, sizeof st_Item); // Zera a capa 

			if(player->CapeInfo == 7) // Blue
				player->Equip[15].Index = 3197;
			else if(player->CapeInfo == 8) // Red
				player->Equip[15].Index = 3198;
			else // White
				player->Equip[15].Index = 3199;

			AmountMinus(&player->Inventory[p->SrcSlot]);
			AmountMinus(&player->Equip[11]);

			char msg[108];
			sprintf_s(msg, "[%s] Agora é Celestial.", player->Name);

			SendNotice(msg);

			SendCharList(p->Header.ClientId);

			SendClientSignalParm(p->Header.ClientId, p->Header.ClientId, 0x3B4, wdBuffer[p->Header.ClientId].Ingame.LoggedMob);

			return;
		}

		if(player->Equip[0].EFV2 == CELESTIAL && player->Status.Level >= 120 && 
		  !wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.SubCeleMade && 
		  (player->Equip[11].Index >= 1760 && player->Equip[11].Index <= 1763))
		{
			// Celestial 121~200
			INT8 classInfo = player->Equip[11].Index - 1760;

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.SubCeleMade = 1;// Marca a quest como feita

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].ClassInfo = player->ClassInfo; // Salva a classe do cele
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Exp = player->Exp; // Salva a exp do cele
			memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Face, &player->Equip[0], sizeof(st_Item)); // Salva a face do cele
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Learn = player->Learn; // Salva as skills do cele
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].MasterPoint = player->MasterPoint; // Salva os pontos
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].SkillPoint = player->SkillPoint;   // Salva os pontos
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].StatusPoint = player->StatusPoint; // Salva os pontos
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.DEX = player->bStatus.DEX; // Salva a DEX
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.INT = player->bStatus.INT; // Salva a INT
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.STR = player->bStatus.STR; // Salva a STR
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.CON = player->bStatus.CON; // Salva a CON
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.Mastery[0] = player->bStatus.Mastery[0]; // Salva as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.Mastery[1] = player->bStatus.Mastery[1]; // Salva as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.Mastery[2] = player->bStatus.Mastery[2]; // Salva as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.Mastery[3] = player->bStatus.Mastery[3]; // Salva as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].Stats.Level = player->bStatus.Level; // Salva o level do cele
			memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].AffectInfo, &player->AffectInfo, sizeof Affects);
			memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].SkillBar1, &player->SkillBar, 4);
		    memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[0].SkillBar2, &wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].SkillBar2, 16);

			memset(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1], 0x0, sizeof(NewPerso)); // Zera as infos do subcele por segurança

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.Mastery[0] = 0; // Seta as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.Mastery[1] = 0; // Seta as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.Mastery[2] = 0; // Seta as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.Mastery[3] = 0; // Seta as aprendizagens
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.DEX = 5; // Seta a DEX
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.INT = 5; // Seta a INT
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.STR = 5; // Seta a STR
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.CON = 5; // Seta a CON
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Learn |=  (1 << 30); // Entrega a Soul
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].ClassInfo = classInfo; // Seta a classe das skills
			memcpy(&wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Face, &player->Equip[0], sizeof(st_Item)); 
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Face.EFV2 = SCELESTIAL; // Seta a classe como SCele
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Face.Index = (player->Equip[0].Index - player->ClassInfo) + classInfo; // Seta como a nova face, mesmo corpo mas com skill diferente
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Face.EFV3 = wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Face.Index;
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].Stats.Level = 0; // Seta o novo level como 0
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].MasterPoint = 855; // Seta os pontos
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].SkillPoint = 0;  // Seta os pontos
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Persos[1].StatusPoint = 0; // Seta os pontos

			if(!SaveAccount(p->Header.ClientId))
			{
				SendClientMessage(p->Header.ClientId, "Houve um erro enquanto salvavamos sua account, favor entrar em contato com a administração.");

				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

				return;
			}

			AmountMinus(&player->Inventory[p->SrcSlot]);
			AmountMinus(&player->Equip[11]);

			st_Item Misteriosa;
			memset(&Misteriosa, 0x0, sizeof(st_Item)); // Zera o item para garantir que não venham adds misteriosos

			Misteriosa.Index = 4148; 
			Misteriosa.EF1 = EF_AMOUNT; // Já entrega 10 unidades do item
			Misteriosa.EFV1 = 10; // Só pro cara sacar como funciona

			PutItem(p->Header.ClientId, &Misteriosa);

			char msg[108];
			sprintf_s(msg, "[%s] Agora é Sub Celestial.", player->Name);

			SendNotice(msg);

			SendCharList(p->Header.ClientId);

			SendClientSignalParm(p->Header.ClientId, p->Header.ClientId, 0x3B4, wdBuffer[p->Header.ClientId].Ingame.LoggedMob);

			return;
		}

		if((player->Equip[0].EFV2 == CELESTIAL || player->Equip[0].EFV2 == SCELESTIAL) && player->Equip[10].Index == 1742)
		{
			// HardCore 

			INT8 FreeSlot = -1;
			for(int i = 0; i < 4; i++)
			{
				if(!strcmp(Users[p->Header.ClientId].CharList.Name[i], "\0"))
				{
					FreeSlot = i;
					break;
				}
			}

			if(FreeSlot == -1)
			{
				SendClientMessage(p->Header.ClientId, "Você não tem espaço suficiente para um novo personagem.");
				
				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);
				
				return;
			}	

			memset(&player->Equip[10], 0, sizeof(st_Item)); // Remove a imo
			AmountMinus(&player->Inventory[p->SrcSlot]);    // Remove a ideal
			memset(&wdBuffer[p->Header.ClientId].Chars[FreeSlot], 0x0, sizeof wdBuffer[0].Chars[0]); // Zera as infos do slot do char do HC

			MSG_DBCreateArch pServer;

		    pServer.Header.ClientId = p->Header.ClientId;
			pServer.Header.PacketId = 0x80F;
			pServer.Header.Size = sizeof MSG_DBCreateArch;		

			pServer.charSlot = FreeSlot;

			memcpy(&pServer.mob, &MobArch, sizeof MobArch);			
			
			strcpy((char*)pServer.mob.Name, (char*)player->Name);
			
			memcpy(&pServer.mob.Equip[0], &player->Equip[0], sizeof st_Item);   // Põe a mesma face do cele/sub
			memcpy(&pServer.mob.Equip[15], &player->Equip[15], sizeof st_Item); // Põe a mesma capa do cele/sub
			
			pServer.mob.ClassInfo = player->ClassInfo; // Skills da account

			pServer.mob.Equip[0].EFV2 = HARDCORE; // Seta a Face como de hc pra infos futuras
			pServer.mob.Equip[1].Index = 3505; // Entrega a Cythera

			pServer.mob.Learn |=  (1 << 30);

			pServer.mob.bStatus.Defense = player->bStatus.Defense;
			pServer.mob.bStatus.Attack  = player->bStatus.Attack;

			pServer.mob.MasterPoint = 855;

			pServer.mob.bStatus.maxHP = player->bStatus.maxHP;
			pServer.mob.bStatus.maxMP = player->bStatus.maxMP;

			pServer.mob.bStatus.Move.Speed = 3;
			pServer.mob.Status.Move.Speed = 3;	

			wdBuffer[p->Header.ClientId].Chars[FreeSlot].Quests.CristalElime = TRUE;
			wdBuffer[p->Header.ClientId].Chars[FreeSlot].Quests.CristalNoas = TRUE;
			wdBuffer[p->Header.ClientId].Chars[FreeSlot].Quests.CristalSylphed = TRUE;
			wdBuffer[p->Header.ClientId].Chars[FreeSlot].Quests.CristalThelion = TRUE;
		   
			char szMsg[120];
			sprintf_s(szMsg, "[%s] Agora é HardCore.", player->Name);
			SendNotice(szMsg);

			SendCharList(p->Header.ClientId);

			SendDBPacket((BYTE*)&pServer, sizeof MSG_DBCreateArch);

			SendClientSignalParm(p->Header.ClientId, p->Header.ClientId, 0x3B4, FreeSlot);
			return;
		}

		SendClientMessage(p->Header.ClientId, "Não há quests a serem concluidas.");
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);
		return;
	}
	__except(TRUE)
	{
	}
}

void NightMare(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	if(now->tm_min != 0 && now->tm_min != 15 && now->tm_min != 30 && now->tm_min != 45)
	{
		SendClientMessage(p->Header.ClientId, "Atente-se aos minutos corretos: 0 ~ 15 ~ 30 ~ 45 .");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(player->Leader || player->Leader == -1)
	{
		SendClientMessage(p->Header.ClientId, "Uso exclusivo do líder do grupo.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	UINT8 ActualPesa = (srcItem->Index - 3324) * -1 + 2;

	if(ActualPesa < 0 || ActualPesa > 2)
	{
		SendClientMessage(p->Header.ClientId, "Erro crítico, favor contatar a Administração.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	if(Pesa[ActualPesa].Groups > 3)
	{
		SendClientMessage(p->Header.ClientId, "Máximo de 3 grupos por vez nesta quest.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	st_Position FinalPosition;
	static const INT16 Destinys[3][2] = 
	{
		{1205, 173},
		{1093, 310},
		{1310, 313}
	};

	FinalPosition.X = Destinys[ActualPesa][0];
	FinalPosition.Y = Destinys[ActualPesa][1];

	if(!Pesa[ActualPesa].Status)
	{
		Pesa[ActualPesa].Status = true;
		Pesa[ActualPesa].NpcsAlive = 8;
	}

	Pesa[ActualPesa].Groups++;

	AmountMinus(srcItem);

	for(int i = 0; i < 3; i++)
	{
		if(!Pesa[ActualPesa].CIDS[i][0])
		{
			Pesa[ActualPesa].CIDS[i][0] = p->Header.ClientId;
				
			if((player->Equip[0].EFV2 != CELESTIAL && player->Equip[0].EFV2 != SCELESTIAL) || player->bStatus.Level < 180)
				DoTeleport(p->Header.ClientId, Destinys[ActualPesa][0], Destinys[ActualPesa][1]);
				
			Pesa[ActualPesa].TimeLeft = 60 - now->tm_sec;

			SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A1, Pesa[ActualPesa].TimeLeft);

			for(int e = 0; e < 12; e++)
			{
				if(player->PartyList[e] > 740)
					continue;

				if(Users[player->PartyList[e]].Status != 22)
					continue;

				st_Mob *tmpPlayer = GetMobFromIndex(player->PartyList[e]);

				if(tmpPlayer->Equip[0].EFV2 > ARCH && tmpPlayer->Equip[0].EFV2 <= SCELESTIAL && tmpPlayer->bStatus.Level > 180)
					continue;

				Pesa[ActualPesa].CIDS[i][e + 1] = player->PartyList[e];

				DoTeleport(player->PartyList[e], Destinys[ActualPesa][0], Destinys[ActualPesa][1]);

				SendClientSignalParm(player->PartyList[e], 0x7530, 0x3A1, Pesa[ActualPesa].TimeLeft);
			}

			break;
		}
	}
}

void RecallRvR(BYTE *m_PacketBuffer, bool *pRetn)
{
	__try
	{
		p373* p = (p373*)m_PacketBuffer;
		st_Mob *player = GetMobFromIndex(p->Header.ClientId);

		*pRetn = true;

		time_t rawnow = time(NULL);
		struct tm *now = localtime(&rawnow);

		AmountMinus(&player->Inventory[p->SrcSlot]);

		if(now->tm_hour != 19 || (DayOfWeek() == Sabado || DayOfWeek() == Domingo))
		{
			SendClientMessage(p->Header.ClientId, "Somente é possível usar na hora da guerra.");

			return;
		}

		if(player->CapeInfo == 7)
			DoTeleport(p->Header.ClientId, 3354, 1051);
		else if(player->CapeInfo == 8)
			DoTeleport(p->Header.ClientId, 3425, 1122);
		else
			SendClientMessage(p->Header.ClientId, "Sem capa? Sem rvr.");
	}
	__except(TRUE)
	{
	}
}

void UseLac(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(!dstItem || p->DstType != EQUIP)
	{
		printf("NULL\n");

		return;
	}

	// Ovos ou itens no slot da mount, retorna para usar a nativa
	if((dstItem->Index >= 2300 && dstItem->Index <= 2328) || p->DstSlot == 14)
		return;

	for(int i = 0; i < sizeof(Capas) / sizeof(int); i++)
	{
		if(dstItem->Index == Capas[i])
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, &player->Inventory[p->SrcSlot]);

			SendClientMessage(p->Header.ClientId, "Para refinar este item utilize o npc Odin.");
			return;
		}
	}

	for(int i = 0; i < sizeof(ArchNoEquip) / sizeof(int); i++)
	{
		if(dstItem->Index == ArchNoEquip[i])
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

			SendClientMessage(p->Header.ClientId, "Este item não pode ser refinado desta forma.");
			return;
		}
	}

	UINT8 index = srcItem->Index - 412,
		  atualref = GetItemSanc(dstItem);

    int SancRate[4][15] = {
			{100, 100, 80, 60, 40, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1},	// Poeira de Ori
			{100, 100, 100, 100, 100, 100, 85, 65, 25, -1, 5, -1, -1, -1, -1},	// Poeira de Lac
			{100, 100, 100, 100, 100, 100, 100, 100, 100, -1, 100, -1, -1, -1, -1},	// Poeira de Lac 100%
			{100, 100, 90, 80, 70, 60, 50, 40, 30, 15, 10, 5, -1, -1, -1} // Amagos
	};

	if(srcItem->Index == 412)
	{

		if(dstItem->Index >= 1752 && dstItem->Index <= 1759)
		{
			INT16 sucessRate[8][5] = {
				{ 5, 61, 85, 97, 100},
				{10, 31, 86, 96, 100},
				{15, 18, 36, 91, 100},
				{20, 23, 30, 45, 100},
				{30, 80, 92, 98, 100},
				{35, 44, 94, 98, 100},
				{38, 40, 46, 96, 100},
				{40, 42, 45, 50, 100}
			};

			INT16 ItemSorteado[8][5] = {
				{0, 1744, 1745, 1746, 1747},
				{0, 1744, 1745, 1746, 1747},
				{0, 1744, 1745, 1746, 1747},
				{0, 1744, 1745, 1746, 1747},
				{0, 1748, 1749, 1750, 1751},
				{0, 1748, 1749, 1750, 1751},
				{0, 1748, 1749, 1750, 1751},
				{0, 1748, 1749, 1750, 1751}
			};

			AmountMinus(srcItem);

			INT16 pos = dstItem->Index - 1752;

			st_Item Premio;
			memset(&Premio, 0x0, sizeof st_Item);

			srand(time(NULL) / 5 * (rand() % 500) * 5);

			INT8 chances = rand() % 100;

			for(int i = 0; i < 5; i++)
			{
				if(chances <= sucessRate[pos][i])
				{
					Premio.Index = ItemSorteado[pos][i];

					memcpy(dstItem, &Premio, sizeof st_Item);

					SendItem(p->Header.ClientId, p->DstType, p->DstSlot, dstItem);
					return;
				}
			}
		}
		else if(dstItem->Index >= 3397 && dstItem->Index <= 3406)
		{
			AmountMinus(srcItem);

			dstItem->Index += 10;

			SendItem(p->Header.ClientId, p->DstType, p->DstSlot, dstItem);

			return;
		}
		else
		{
			if(atualref < 6)
			{
				srand(time(NULL) / 5 * (rand() % 500) * 5);

				INT8 chances = rand() % 100;

				char szMsg[108];

				if(chances <= SancRate[0][atualref])
				{
					RefinarItemMais(dstItem, 1);
						
					SendClientMessage(p->Header.ClientId, "Refinação sucedida.");

					SendItem(p->Header.ClientId, p->DstType, p->DstSlot, dstItem);

					SendEffect(p->Header.ClientId, 0xE, 3);
				}
				else
				{
					SendClientMessage(p->Header.ClientId, "Refinação falhou.");

					SendEffect(p->Header.ClientId, 0xF, 0);
				}
			}
			else
			{
				SendItem(p->Header.ClientId, p->SrcType, p->SrcSlot, srcItem);

				SendClientMessage(p->Header.ClientId, "Não é possível refinar mais.");
			}

			return;
		}
	}

	if(dstItem->Index >= 591 && dstItem->Index <= 595 && GetItemSanc(dstItem) == 9)
	{
		AmountMinus(srcItem);

		srand(time(NULL) / 5 * (rand() % 500) * 5);

		INT8 chances = rand() % 100;

		if(chances > 5)
		{
			AmountMinus(dstItem);

			SendClientMessage(p->Header.ClientId, "Refinação falhou.");

			SendEffect(p->Header.ClientId, 0xF, 0);
		}
		else
		{
			SetItemSanc(dstItem, 230);

			SendClientMessage(p->Header.ClientId, "Refinação sucedida.");

			SendEffect(p->Header.ClientId, 0xE, 3);
		}

		SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);
		return;
	}

	if((p->DstSlot > 0 && p->DstSlot < 8 ) || (dstItem->Index >= 591 && dstItem->Index <= 595))
	{
		// Refinar +11
		if(GetItemSanc(dstItem) >= 230 && GetItemSanc(dstItem) <= 233)
		{
			AmountMinus(srcItem);

			srand(time(NULL) / 5 * (rand() % 500) * 5);

			INT8 chances = rand() % 100;

			if(chances > 5)
			{
				SendClientMessage(p->Header.ClientId, "Refinação falhou.");

				SendEffect(p->Header.ClientId, 0xF, 0);
			}
			else
			{
				RefinarItemMais(dstItem, 4);
				
				SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);
				
				SendClientMessage(p->Header.ClientId, "Refinação sucedida.");

				SendEffect(p->Header.ClientId, 0xE, 3);
			}

			return;
		}
	}

	if(GetItemSanc(dstItem) < 9)
	{
		srand(time(NULL) / 5 * (rand() % 500) * 5);

		INT8 chances = rand() % 100,
				atualref = GetItemSanc(dstItem);

		if(chances <= SancRate[1][atualref])
		{
			char szMsg[108];

			if(chances <= SancRate[1][atualref])
			{
				RefinarItemMais(dstItem, 1);
						
				SendClientMessage(p->Header.ClientId, "Refinação sucedida.");

				SendItem(p->Header.ClientId, p->DstType, p->DstSlot, dstItem);

				SendEffect(p->Header.ClientId, 0xE, 3);
			}
			else
			{
				SendClientMessage(p->Header.ClientId, "Refinação falhou.");

				SendEffect(p->Header.ClientId, 0xF, 0);
			}
		}

		AmountMinus(srcItem);

		return;
	}

	SendClientMessage(p->Header.ClientId, "Não é possível refinar este item no momento.");
	return;
}

void ProcessSephiraBook(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	const WORD BooksSkill[5] = {0, 36, 35, 40, 39};
	INT8 _index = srcItem->Index - 666;

	if(_index <= 0 || _index > 5)
		goto END;

	int has = (player->Learn & (1 << (24 + _index)));
	if(has)
	{
		SendClientMessage(p->Header.ClientId, "Já aprendeu esta skill anteriormente.");
		goto END;
	}

	if(player->SkillPoint < BooksSkill[_index - 1])
	{
		SendClientMessage(p->Header.ClientId, "Não possui pontos de skill suficientes.");
		goto END;
	}

	if(player->Equip[0].EFV2 <= ARCH && player->bStatus.Level < 255)
	{
		SendClientMessage(p->Header.ClientId, "Level inadequado.");
		goto END;
	}

	player->SkillPoint -= BooksSkill[_index - 1];
	player->Learn |= 1 << (_index + 24);

	GetCurrentScore(p->Header.ClientId);
	SendStats(p->Header.ClientId);

	AmountMinus(srcItem);

END:
	SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

	return;
}

void Barras(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	unsigned long int valor_gold;

	if(srcItem->Index == 4010)      
		valor_gold = 100000000;
	else if(srcItem->Index == 4011) 
		valor_gold = 1000000000;
	else if(srcItem->Index == 4026) 
		valor_gold = 1000000;
	else if(srcItem->Index == 4027) 
		valor_gold = 5000000;
	else if(srcItem->Index == 4028) 
		valor_gold = 10000000;
	else if(srcItem->Index == 4029) 
		valor_gold = 50000000;
	else if(srcItem->Index == 5359) 
		valor_gold = 500000000;
	else if(srcItem->Index == 5360) 
		valor_gold = 2000000000;

	if(player->Gold > 2000000000 - valor_gold)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Só é possível carregar 2.000.000.000 de gold.");

		return;
	}

	player->Gold += valor_gold;

	AmountMinus(srcItem);

	SendEtc(p->Header.ClientId);

	return;
}

void Replations(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(GetItemSanc(dstItem) > 4)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Somente itens com refinação igual ou inferior a +4.");

		return;
	}

	for(int i = 0; i < sizeof(NotReplation) / sizeof(int); i++)
	{
		if(dstItem->Index == NotReplation[i])
		{
			SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);
			return;
		}
	}

	bool CheckRefine = false;

	for(int i = 0; i < sizeof(CheckAllReplations) / sizeof(int); i++)
		if(dstItem->Index == CheckAllReplations[i])
		{
			CheckRefine = true;
			break;
		}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	int successRate = Rand() % 100;
	BOOL doRefine = FALSE;

	switch(srcItem->Index)
	{
		case 4016: case 4021:
			if(successRate <= 95 && CheckRefine)
				doRefine = true;
			break;
		case 4017: case 4022:
			if(successRate <= 90 && CheckRefine)
				doRefine = true;
			break;
		case 4018: case 4023:
			if(successRate <= 85 && CheckRefine)
				doRefine = true;
			break;
		case 4019: case 4024:
			if(successRate <= 80 && CheckRefine)
				doRefine = true;
			break;
		case 4020:
			if(successRate <= 41 && CheckRefine)
				doRefine = true;
			break;
	}
	        
	if(doRefine)
	{
		int ef2 = 0, efv2 = 0,
			ef3 = 0, efv3 = 0,

			effs_elmo[5] = { EF_NONE, EF_ATTSPEED, EF_MAGIC, EF_HP, EF_ACADD },
			effs_armadura[5] = { EF_NONE, EF_DAMAGE, EF_CRITICAL, EF_MAGIC, EF_ACADD },
			effs_calca[5] = { EF_NONE, EF_DAMAGE, EF_CRITICAL, EF_MAGIC, EF_ACADD },
			effs_manopla[5] = { EF_NONE, EF_DAMAGE, EF_SPECIALALL, EF_MAGIC, EF_ACADD },
			effs_bota[4] = { EF_NONE, EF_DAMAGE, EF_SPECIALALL, EF_MAGIC };

		INT16 type = ItemList[dstItem->Index].Pos;
		if(type == ELMO_TYPE)
		{
			ef2 = effs_elmo[Rand() % (sizeof(effs_elmo) / sizeof(int))];
			ef3 = effs_elmo[Rand() % (sizeof(effs_elmo) / sizeof(int))];
		}
		else if(type == PEITO_TYPE)
		{
			ef2 = effs_armadura[Rand() % (sizeof(effs_armadura) / sizeof(int))];
			ef3 = effs_armadura[Rand() % (sizeof(effs_armadura) / sizeof(int))];
		}
		else if(type == CALCA_TYPE)
		{
			ef2 = effs_calca[Rand() % (sizeof(effs_calca) / sizeof(int))];
			ef3 = effs_calca[Rand() % (sizeof(effs_calca) / sizeof(int))];
		}
		else if(type == LUVA_TYPE)
		{
			ef2 = effs_manopla[Rand() % (sizeof(effs_manopla) / sizeof(int))];
			ef3 = effs_manopla[Rand() % (sizeof(effs_manopla) / sizeof(int))];
		}
		else if(type == BOTA_TYPE)
		{
			ef2 = effs_bota[Rand() % (sizeof(effs_bota) / sizeof(int))];
			ef3 = effs_bota[Rand() % (sizeof(effs_bota) / sizeof(int))];
		}
				
		if(ef2 == EF_NONE)
			ef2 = ef3;
		if(ef2 == ef3)
			ef3 = EF_NONE;

		if(ef2 != EF_NONE)
		{
			if(ef2 == EF_ATTSPEED)
				efv2 = add_attspeed[Rand() % (sizeof(add_attspeed) / sizeof(int))];
			else if(ef2 == EF_CRITICAL)
				efv2 = add_critical[Rand() % (sizeof(add_critical) / sizeof(int))];
			else if(ef2 == EF_ACADD)
				efv2 = add_ac[Rand() % (sizeof(add_ac) / sizeof(int))];
			else if(ef2 == EF_DAMAGE)
				efv2 = add_damage[Rand() % (sizeof(add_damage) / sizeof(int))];
		   	else if(ef2 == EF_MAGIC)
				efv2 = add_magic[Rand() % (sizeof(add_magic) / sizeof(int))];
			else if(ef2 == EF_HP)
				efv2 = add_hp[Rand() % (sizeof(add_hp) / sizeof(int))];
			else if(ef2 == EF_SPECIALALL)
				efv2 = add_skill[Rand() % (sizeof(add_skill) / sizeof(int))];
		}
		if(ef3 != EF_NONE)
		{
			if(ef3 == EF_ATTSPEED)
				efv3 = add_attspeed[Rand() % (sizeof(add_attspeed) / sizeof(int))];
			else if(ef3 == EF_CRITICAL)
				efv3 = add_critical[Rand() % (sizeof(add_critical) / sizeof(int))];
			else if(ef3 == EF_ACADD)
				efv3 = add_ac[Rand() % (sizeof(add_ac) / sizeof(int))];
			else if(ef3 == EF_DAMAGE)
				efv3 = add_damage[Rand() % (sizeof(add_damage) / sizeof(int))];
			else if(ef3 == EF_MAGIC)
				efv3 = add_magic[Rand() % (sizeof(add_magic) / sizeof(int))];
			else if(ef3 == EF_HP)
				efv3 = add_hp[Rand() % (sizeof(add_hp) / sizeof(int))];
			else if(ef3 == EF_SPECIALALL)
				efv3 = add_skill[Rand() % (sizeof(add_skill) / sizeof(int))];
		}

		dstItem->EF1 = 43;
		dstItem->EFV1 = Rand() % 4;
		dstItem->EF2 = ef2;
		dstItem->EFV2 = efv2;
		dstItem->EF3 = ef3;
		dstItem->EFV3 = efv3;

		SendItem(p->Header.ClientId, INVENTORY, p->DstSlot, dstItem);
	}
			
	AmountMinus(srcItem);
}

void DesagruparPoeiras(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;
		
	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	if(GetFirstSlot(p->Header.ClientId, 0, INVENTORY) == -1)
		goto END;

	int amount = 0, index = (player->Inventory[p->SrcSlot].Index - 3035), slot = 0;

	amount = player->Inventory[p->SrcSlot].EFV1;

	while(amount > 0 && GetFirstSlot(p->Header.ClientId, 0, INVENTORY) != -1)
	{
		amount--;
		slot = GetFirstSlot(p->Header.ClientId, 0, INVENTORY);
		player->Inventory[slot].Index = index;
		AmountMinus(&player->Inventory[p->SrcSlot]);
	}

END:
	SendALL(p->Header.ClientId);
	
	return;
}

void AgruparPoeiras(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373* p = (p373*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	int i = 0, amount = 0, index = (player->Inventory[p->SrcSlot].Index - 3033);

	for(; i < 63; i++)
	{
		if(player->Inventory[i].Index == index && (player->Inventory[i].EF1 != EF_AMOUNT || player->Inventory[i].EFV1 <= 1))
		{
			amount++;
			AmountMinus(&player->Inventory[i]);
		}       
	}

	if(amount != 0)
	{
		int slot = GetFirstSlot(p->Header.ClientId, 0, INVENTORY);
		player->Inventory[slot].Index = (index + 3035);
		player->Inventory[slot].EF1 = EF_AMOUNT;
		player->Inventory[slot].EFV1 = amount;
		AmountMinus(&player->Inventory[p->SrcSlot]);
	}

	SendALL(p->Header.ClientId);

	return;
}

void ProcessHuntingScrolls(BYTE *m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if((srcItem->Index < 3432 || srcItem->Index > 3437) || p->warp > 10 || (p->warp - 1 < 0))
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Erro, entre em contato com à Administração.");

		return;
	}

	p->warp--;

	AmountMinus(srcItem);

	DoTeleport(p->Header.ClientId, HuntingScrolls[srcItem->Index - 3432][p->warp][0], HuntingScrolls[srcItem->Index - 3432][p->warp][1]);

	return;
}

void MoneyCube(BYTE *m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
			*dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(!player->Gold || player->Gold > 1000000000)
	{
		SendClientMessage(p->Header.ClientId, "Alguma coisa está errada com seu gold.");

		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		return;
	}

	AmountMinus(srcItem);

	INT64 totalGold = player->Gold * 2;
		
	if((Rand() % 2) == 1)
		totalGold /= 4;

	player->Gold = totalGold;

	SendEtc(p->Header.ClientId);

	return;
}

void Gemas(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(p->DstType != EQUIP || dstItem == NULL)
		return;

	if(srcItem->Index < 3386 || srcItem->Index > 3389)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Erro, entre em contato com a Administração.");

		return;
	}

	if(GetItemSanc(dstItem) < 230 || GetItemSanc(dstItem) > 253)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Não há como usar em refinações abaixo de +10.");

		return;
	}

	if(dstItem->Index >= 3500 && dstItem->Index <= 3507)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Não é possível utilizar em Cytheras.");

		return;
	}

	if(ItemList[dstItem->Index].Pos == ELMO_TYPE || ItemList[dstItem->Index].Pos == PEITO_TYPE || 
		ItemList[dstItem->Index].Pos == CALCA_TYPE || ItemList[dstItem->Index].Pos == LUVA_TYPE || 
		ItemList[dstItem->Index].Pos == BOTA_TYPE || ItemList[dstItem->Index].Pos == ESCUDO_TYPE)
	{
		for(int i = 0; i < 6; i++)
		{
			if(GetItemSanc(dstItem) >= szRefis[i][0] && GetItemSanc(dstItem) <= szRefis[i][1])
			{
				SetItemSanc(dstItem, szRefis[i][0] + srcItem->Index - 3386);

				AmountMinus(srcItem);

				SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

				SendEffect(p->Header.ClientId, 0xE, 3);

				break;
			}
		}
	}
	else
	{
		if(ItemList[dstItem->Index].Pos == ARMA_TYPE1 || ItemList[dstItem->Index].Pos == ARMA_TYPE2)
		{
			if(ItemList[dstItem->Index].Grade < 5 || ItemList[dstItem->Index].Grade > 8)
			{
				SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

				SendClientMessage(p->Header.ClientId, "Há algo errado com este item.");
				
				return;
			}

			for(int i = 0; i < 6; i++)
			{
				if(GetItemSanc(dstItem) >= szRefis[i][0] && GetItemSanc(dstItem) <= szRefis[i][1])
				{
					if(ItemList[dstItem->Index].Grade >= 5 && ItemList[dstItem->Index].Grade <= 8)
						 dstItem->Index += (srcItem->Index - 3386 + 5 - ItemList[dstItem->Index].Grade);

					SetItemSanc(dstItem, szRefis[i][0] + srcItem->Index - 3386);
				
					AmountMinus(srcItem);

					SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

					SendEffect(p->Header.ClientId, 0xE, 3);

					break;
				}
			}
		}
	}
}

void Tinturas(BYTE *m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(p->DstType != EQUIP || dstItem == NULL)
		return;

	if(GetItemSanc(dstItem) < 230) 
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Você só pode utilizar em equipamentos superiores a +9.");

		return;
	}

	if(p->DstSlot < 1 || p->DstSlot > 5)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Você só pode utilizar em equipamentos de defesa.");

		return;
	}

	for(int i = 0; i < 3; i++)
		if(dstItem->Effect[i].Index == 43 || (dstItem->Effect[i].Index >= 116 && dstItem->Effect[i].Index <= 125))
			dstItem->Effect[i].Index = srcItem->Index - 3291;

	AmountMinus(srcItem);

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	return;
}

void RemoveTinturas(BYTE* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p373 *p = (p373*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	st_Item *srcItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem = GetItemPointer(player, Users[p->Header.ClientId].Storage.Item, p->DstType, p->DstSlot);

	if(p->DstType != EQUIP || dstItem == NULL)
		return;

	if(GetItemSanc(dstItem) < 230) 
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Você só pode utilizar em equipamentos superiores a +9.");

		return;
	}

	if(p->DstSlot < 1 || p->DstSlot > 5)
	{
		SendItem(p->Header.ClientId, INVENTORY, p->SrcSlot, srcItem);

		SendClientMessage(p->Header.ClientId, "Você só pode utilizar em equipamentos de defesa.");

		return;
	}

	for(int i = 0; i < 3; i++)
		if(dstItem->Effect[i].Index >= 116 && dstItem->Effect[i].Index <= 125)
			dstItem->Effect[i].Index = 43;

	AmountMinus(srcItem);

	SendItem(p->Header.ClientId, EQUIP, p->DstSlot, dstItem);

	return;
}