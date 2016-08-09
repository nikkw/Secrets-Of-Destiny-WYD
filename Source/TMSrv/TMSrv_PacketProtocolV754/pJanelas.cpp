#include "DLLMain.h"

void Lindy(UINT8 *packet, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)packet;

	INT16 cId = p->Header.ClientId;

	if(cId <= 0 || cId >= MAX_PLAYER)
		return;

	st_Mob *player = (st_Mob*)GetMobFromIndex(cId);

	for(INT8 i = 0; i < 7; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;

		else if(i <= 1 && (p->ItemId[i].Index != 3448 || ReturnItemAmount(&p->ItemId[i]) != 10))
		{
			SendClientMessage(cId, "São necessários 2 Pacotes de Lactolerium com 10 unidades cada.");

			return;
		}

		else if(i == 2 && p->ItemId[i].Index != 4127)
		{
			SendClientMessage(cId, "É necessário 1 Pergaminho Selado.");

			return;
		}

		else if(i >= 3 && p->ItemId[i].Index != 413)
		{
			SendClientMessage(cId, "São necessárias 4 Poeiras de Lactolerium.");

			return;
		}
	}

	if(wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Fame < 10)
	{
		SendClientMessage(cId, "Fame insuficiente. É necessário 10 de Fame para prosseguir.");

		return;
	}

	if(player->Status.Level == 354 && !wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.Block355Arch)
		wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.Block355Arch = TRUE;
	else if(player->Status.Level == 369 && !wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.Block370Arch)
		wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Quests.Block370Arch = TRUE;
	else
	{
		SendClientMessage(cId, "Nível inadequado, desculpe.");

		return;
	}

	wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].Fame -= 10;

	for(INT8 i = 0; i < 7; i++)		
	{
		memset(&player->Inventory[p->Slot[i]], 0, sizeof(st_Item));

		SendItem(cId, INVENTORY, p->Slot[i], &player->Inventory[p->Slot[i]]);
	}

	SendClientMessage(cId, "Nível destravado com sucesso!");

	SendClientSignalParm(cId, 0x7530, 0x3A7, 2);
}

void Compounder(BYTE *packetBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)packetBuffer;

	INT16 cId = p->Header.ClientId;

	if(cId <= 0 || cId >= MAX_PLAYER)
		return;

	st_Mob *player = (st_Mob*)GetMobFromIndex(cId);

	for(INT8 i = 0; i < 6; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;

		else if(i >= 2)
		{
			if(player->Inventory[p->Slot[i]].Index && GetItemSanc(&p->ItemId[i]) < 7)
			{
				SendClientMessage(cId, "Somente itens com refinação superior ou igual a 7.");

				return;
			}
		}
	}

	INT16 ItemExtreme = ItemList[p->ItemId[0].Index].Extreme,
		  ItemIndex = p->ItemId[1].Index - 2441;

	if(ItemExtreme <= 0 || ItemExtreme > MAX_ITEMLIST)
	{
		SendClientMessage(cId, "Este item já é Anct.");
		 
		return;
	}

	if(ItemIndex < 0 || ItemIndex > 3)
	{
		SendClientMessage(cId, "Necessário 1 jóia Garnet, Coral, Esmeralda ou Diamente.");

		return;
	}

	for(INT8 i = 1; i < 6; i++)		
	{
		memset(&player->Inventory[p->Slot[i]], 0, sizeof(st_Item));
		SendItem(cId, INVENTORY, p->Slot[i], &player->Inventory[p->Slot[i]]);
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Chance = rand() % 100,
		 Percent = 0;

	char Message[245];

	if(Chance < GetMatchCombine(p->ItemId))
	{
		player->Inventory[p->Slot[0]].Index = (INT16)(ItemExtreme + ItemIndex);

		SetItemSanc(&player->Inventory[p->Slot[0]], 7);

		sprintf(Message, "%s obteve sucesso na composição do item %s. (%d/%d)", player->Name, ItemList[p->ItemId[0].Index].Name, Chance, GetMatchCombine(p->ItemId));
	}
	else
	{
		memset(&player->Inventory[p->Slot[0]], 0, sizeof(st_Item));

		sprintf(Message, "Houve falha na composição do item.");
	}

	SendItem(cId, INVENTORY, p->Slot[0], &player->Inventory[p->Slot[0]]);

	SendClientMessage(cId, Message);

	SendClientSignalParm(cId, 0x7530, 0x3A7, 2);
}

void Agatha(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId <= 0 || p->Header.ClientId >= MAX_PLAYER)
		return;

	for(INT8 i = 0; i < 6; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;
	}

	INT16 SancSlot1 = GetItemSanc(&p->ItemId[0]), SancSlot2 = GetItemSanc(&p->ItemId[1]);

	if(SancSlot1 < 9 || SancSlot1 > 253 || SancSlot2 < 9 || SancSlot2 > 253)
	{
		SendClientMessage(p->Header.ClientId, "O item deve ter a refinação acima de +9.");

		return;
	}

	INT8 Percent = 0;
	if(ItemList[p->ItemId[1].Index].Grade == 1)
		Percent = 12;
	else if(ItemList[p->ItemId[1].Index].Grade == 2)
		Percent = 18;
	else if(ItemList[p->ItemId[1].Index].Grade == 3)
		Percent = 22;
	else if(ItemList[p->ItemId[1].Index].Grade == 4)
		Percent = 29;
	else
		Percent = 10;

	if(SancSlot2 >= 230 && SancSlot2 <= 233)
		Percent += 18;
	else if(SancSlot2 >= 234 && SancSlot2 <= 237)
		Percent += 26;
	else if(SancSlot2 >= 238 && SancSlot2 <= 241)
		Percent += 28;
	else if(SancSlot2 >= 242 && SancSlot2 <= 245)
		Percent += 30;
	else if(SancSlot2 >= 246 && SancSlot2 <= 249)
		Percent += 32;
	else if(SancSlot2 >= 250 && SancSlot2 <= 253)
		Percent += 34;
	else
		Percent += 10;

	if(isVip(p->Header.ClientId))
		Percent += 15;

	if(Percent < 0 || Percent > 100)
		Percent = 100;
	
	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Chance = rand() % 100;

	char Message[260];

	for(INT8 i = 2; i < 6; i++)
		memset(&player->Inventory[p->Slot[i]], 0, sizeof(st_Item));

	if(Chance <= Percent)
	{
		memcpy(&player->Inventory[p->Slot[0]].EF1, &player->Inventory[p->Slot[1]].EF1, 6);

		SetItemSanc(&player->Inventory[p->Slot[0]], 7);

		memset(&player->Inventory[p->Slot[1]], 0x0, sizeof(st_Item));

		sprintf(Message, "%s obteve sucesso na composição do item %s. (%d/%d)", player->Name, ItemList[p->ItemId[0].Index].Name, Chance, Percent);
	}
	else
	{
		memset(&player->Inventory[p->Slot[0]], 0, sizeof(st_Item));

		sprintf(Message, "Houve falha na composição do item.");
	}

	for(INT8 i = 0; i < 6; i++)			
		SendItem(p->Header.ClientId, INVENTORY, p->Slot[i], &player->Inventory[p->Slot[i]]);

	SendClientMessage(p->Header.ClientId, Message);

	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
}

void Tiny(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId <= 0 || p->Header.ClientId >= MAX_PLAYER)
		return;

	for(INT8 i = 0; i < 3; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;
	}

	INT16 SancSlot1 = GetItemSanc(&p->ItemId[0]), SancSlot2 = GetItemSanc(&p->ItemId[1]);

	if(SancSlot1 < 9 || SancSlot1 > 253 || SancSlot2 < 9 || SancSlot2 > 253)
	{
		SendClientMessage(p->Header.ClientId, "O item deve ter a refinação acima de +9.");
		return;
	}

	if(player->Gold < 100000000)
	{
		SendClientMessage(p->Header.ClientId, "Você precisa de 100 Milhões(100kk) de Gold.");
		return;
	}

	INT8 Percent = 0;
	if(SancSlot2 >= 230 && SancSlot2 <= 233)
		Percent += 25;
	else if(SancSlot2 >= 234 && SancSlot2 <= 237)
		Percent += 30;
	else if(SancSlot2 >= 238 && SancSlot2 <= 241)
		Percent += 35;
	else if(SancSlot2 >= 242 && SancSlot2 <= 245)
		Percent += 40;
	else if(SancSlot2 >= 246 && SancSlot2 <= 249)
		Percent += 45;
	else if(SancSlot2 >= 250 && SancSlot2 <= 253)
		Percent += 60;
	else
		Percent += 20;

	if(isVip(p->Header.ClientId))
		Percent += 15;

	if(Percent < 0 || Percent > 100)
		Percent = 100;

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Chance = rand() % 100;

	char Message[260];

	INT8 size = 0;

	if(Chance <= Percent)
	{
		memcpy(&player->Inventory[p->Slot[0]].EF1, &player->Inventory[p->Slot[1]].EF1, 6);

		SetItemSanc(&player->Inventory[p->Slot[0]], 7);

		size = 1;

		sprintf(Message, "%s obteve sucesso na composição do item %s. (%d/%d)", player->Name, ItemList[p->ItemId[0].Index].Name, Chance, Percent);
	}
	else
		sprintf(Message, "Houve falha na composição do item.");

	for(INT8 i = size; i < 3; i++)			
	{
		memset(&player->Inventory[p->Slot[i]], 0, sizeof(st_Item));

		SendItem(p->Header.ClientId, INVENTORY, p->Slot[i], &player->Inventory[p->Slot[i]]);
	}

	SendClientMessage(p->Header.ClientId, Message);

	player->Gold -= 100000000;

	SendEtc(p->Header.ClientId);

	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
}

void Shany(UINT8 *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId <= 0 || p->Header.ClientId >= MAX_PLAYER)
		return;

	if(player->Equip[0].EFV2 < ARCH || player->bStatus.Level < 355)
	{
		SendClientMessage(p->Header.ClientId, "Necessário ser Arch e estar nível superior a 356.");

		return;
	}

	if(player->Gold < 2000000)
	{
		SendClientMessage(p->Header.ClientId, "Você precisa de 2 Milhões (2kk) de Gold.");

		return;
	}

	for(INT8 i = 0; i < 7; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;

		else if(i >= 3 && p->ItemId[i].Index != 413)
		{
			SendClientMessage(p->Header.ClientId, "Traga-me 4 Poeiras de Lactolerium para a composição.");

			return;
		}
	}

	if((p->ItemId[0].Index != AbsVerific[0] && p->ItemId[0].Index != AbsVerific[1]) ||
	   (p->ItemId[1].Index != AbsVerific[0] && p->ItemId[1].Index != AbsVerific[1]) ||
	   (p->ItemId[2].Index != AbsVerific[0] && p->ItemId[2].Index != AbsVerific[1]))
	{
		// Caso a abs seja diferente das duas permitidas, ou caso alguma das abs seja diferente das outras
		SendClientMessage(p->Header.ClientId, "Preciso de todas as Pedras Espirituais[E] para a composição.");
		return;
	}

	if(GetItemSanc(&p->ItemId[0]) != 9 || GetItemSanc(&p->ItemId[1]) != 9)
	{
		SendClientMessage(p->Header.ClientId, "As Pedras Espirituais dos dois primeiros slots devem ser +9.");
		return;
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Chance = rand() % 100;

	char Message[100];

	player->Gold -= 500000;

	INT8 size = 0;

	if(Chance <= 60)
	{
		player->Exp -= 2000000;

		player->Gold -= 1500000;

		memset(&player->Inventory[p->Slot[0]], 0x0, sizeof st_Item);

		player->Inventory[p->Slot[0]].Index = AbsDelivery[rand() % 3];

		SendItem(p->Header.ClientId, INVENTORY, p->Slot[0], &player->Inventory[p->Slot[0]]);

		size = 1;

		sprintf(Message, "%s obteve sucesso na composição do item %s. (%d/%d)", player->Name, ItemList[player->Inventory[p->Slot[0]].Index].Name, Chance, 60);
	}
	else
	{
		size = 2;

		sprintf(Message, "Houve falha na composição do item.");
	}

	for(INT8 o = size; o < 7; o++)
	{
		memset(&player->Inventory[p->Slot[o]], 0, sizeof st_Item);

		SendItem(p->Header.ClientId, INVENTORY, p->Slot[o], &player->Inventory[p->Slot[o]]);
	}

	SendClientMessage(p->Header.ClientId, Message);

	SendEtc(p->Header.ClientId);

	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
}

void Ehre(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId <= 0 || p->Header.ClientId >= MAX_PLAYER)
		return;

	for(INT8 i = 0; i < 3; i++)
	{
		if(p->Slot[i] == 0xFF)
			return;
	
		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;
	}

	for(INT8 i = 0; i < sizeof(Configs) / sizeof(INT16); i++)
	{
		if(Configs[i][0] == p->ItemId[0].Index && Configs[i][1] == p->ItemId[1].Index && Configs[i][2] == p->ItemId[2].Index && player->Equip[0].EFV2 != ARCH)
		{
			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].SoulInfo = i;

			for(INT8 o = 0; o < 3; o++)
			{
				memset(&player->Inventory[p->Slot[o]], 0, sizeof st_Item);

				SendItem(p->Header.ClientId, INVENTORY, p->Slot[o], &player->Inventory[p->Slot[o]]);
			}

			SendClientMessage(p->Header.ClientId, "Composição concluída.");	

			SaveAccount(p->Header.ClientId);

			SendClientSignalParm(p->Header.ClientId,0x7530, 0x3A7, 2);				
			return;
		}
	}

	if(p->ItemId[0].Index == 697 && p->ItemId[1].Index == 697)
	{
		if((player->Equip[0].EFV2 == CELESTIAL || player->Equip[0].EFV2 == SCELESTIAL) && player->Status.Level >= 39)
		{
			if(player->Inventory[p->Slot[2]].Index != 3338 || GetItemSanc(&p->ItemId[2]) >= 9)
			{
				SendClientMessage(p->Header.ClientId, "Necessário uma Refinação Abençoada inferior a +9.");
				return;
			}

			INT8 chances = 0;
			if(player->Status.Level >= 39 && player->Status.Level <= 149)
				chances = 30;
			if(player->Status.Level >= 150 && player->Status.Level <= 159)
				chances = 35;
			if(player->Status.Level >= 160 && player->Status.Level <= 169)
				chances = 40;
			if(player->Status.Level >= 170 && player->Status.Level <= 179)
				chances = 50;
			if(player->Status.Level >= 180 && player->Status.Level <= 189)
				chances = 70;
			if(player->Status.Level >= 190 && player->Status.Level <= 199)
				chances = 100;

			if (isVip(p->Header.ClientId))
				chances += 15;

			srand(time(NULL) / 5 * (rand() % 500) * 5);

			if((rand() % 100) <= chances)
			{
				SendClientMessage(p->Header.ClientId, "Obteve sucesso na refinação.");

				RefinarItemMais(&player->Inventory[p->Slot[2]], 1);
			}
			else
			{
				SendClientMessage(p->Header.ClientId, "Sua refinação falhou.");
				memset(&player->Inventory[p->Slot[2]], 0, sizeof st_Item);
			}

			for(INT8 j = 0; j < 2; j++)
				memset(&player->Inventory[p->Slot[j]], 0, sizeof st_Item);

			player->Exp -= 5000000;

			SendEtc(p->Header.ClientId);
			SendALL(p->Header.ClientId);

			SendClientSignalParm(p->Header.ClientId,0x7530, 0x3A7, 2);
		}
		else
		{
			SendClientMessage(p->Header.ClientId, "Necessário ser Celestial/Sub level 40 ou acima.");
			return;
		}
	}
}

void Odin(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId <= 0 || p->Header.ClientId >= MAX_PLAYER)
		return;

	for(INT8 i = 0; i < 7; i ++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		else if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > 6500)
			return;
	}

	//Criação das Pedras Secretas
	for(INT8 i = 0; i < sizeof(CompoeSecretas) / sizeof(INT16); i++)
	{
		if(p->ItemId[0].Index == CompoeSecretas[i][0] && p->ItemId[1].Index == CompoeSecretas[i][1] &&
		p->ItemId[2].Index == CompoeSecretas[i][2] && p->ItemId[3].Index == CompoeSecretas[i][3] &&
		p->ItemId[4].Index == CompoeSecretas[i][4] && p->ItemId[5].Index == CompoeSecretas[i][5] &&
		p->ItemId[6].Index == CompoeSecretas[i][6])
		{
			for(INT8 o = 0; o < 7; o++)
			{
				memset(&player->Inventory[p->Slot[o]], 0, sizeof st_Item);

				SendItem(p->Header.ClientId, INVENTORY, p->Slot[o], &player->Inventory[p->Slot[o]]);
			}

			st_Item ItemSlot;

			memset(&ItemSlot, 0x0, sizeof st_Item);

			ItemSlot.Index = CompoeSecretas[i][7];

			PutItem(p->Header.ClientId, &ItemSlot);

			SendClientMessage(p->Header.ClientId, "Composição concluída.");

			SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
			return;
		}
	}

	//Refinando capa Celestial
	if(p->ItemId[0].Index == 4127 && p->ItemId[1].Index == 4127 && p->ItemId[2].Index == 5135 &&
	p->ItemId[3].Index == 413 && p->ItemId[4].Index == 413 && p->ItemId[5].Index == 413 &&
	p->ItemId[6].Index == 413)
	{
		if(player->Equip[15].Index < 3197 || player->Equip[15].Index > 3199 || 
			player->Equip[0].EFV2 < CELESTIAL || player->Equip[0].EFV2 > SHARDCORE)
		{
			SendClientMessage(p->Header.ClientId, "Você deve ser Celestial ou superior.");
			return;
		}

		if(GetItemSanc(&player->Equip[15]) > 9)
		{
			SendClientMessage(p->Header.ClientId, "Sua capa já está na refinação máxima.");
			return;
		}

		for(INT8 j = 0; j < 7; j++)
			memset(&player->Inventory[p->Slot[j]], 0, sizeof st_Item);

		RefinarItemMais(&player->Equip[15], 1);

		SendClientMessage(p->Header.ClientId, "Obteve sucesso na refinação.");

		SendEffect(3, 0xE, p->Header.ClientId);

		SendItem(p->Header.ClientId, EQUIP, 15, &player->Equip[15]);

		SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);

		SendALL(p->Header.ClientId);
		return;
	}

	//Criação da Pedra da Fúria
	if(p->ItemId[0].Index == 5125 && p->ItemId[1].Index == 5115 && p->ItemId[2].Index == 5111 && p->ItemId[3].Index == 5112 && 
		p->ItemId[4].Index == 5120 && p->ItemId[5].Index == 5128 && p->ItemId[6].Index == 5119)
	{			
		for(INT8 e = 0; e < 7; e++)
		{
			memset(&player->Inventory[p->Slot[e]], 0, sizeof st_Item);

			SendItem(p->Header.ClientId, INVENTORY, p->Slot[e], &player->Inventory[e]);
		}

		st_Item pItem;
		memset(&pItem, 0x0, sizeof(st_Item));

		pItem.Index = 3020;

		PutItem(p->Header.ClientId, &pItem);

		SendClientMessage(p->Header.ClientId, "Composição concluída.");

		SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
		return;
	}

	// Desbloqueio do level 40
	if(p->ItemId[0].Index == 5113 && p->ItemId[1].Index == 5129 && 
		p->ItemId[2].Index == 5112 && p->ItemId[3].Index == 5110 && 
		p->ItemId[4].Index == 4127 && p->ItemId[5].Index == 4127 &&
		p->ItemId[6].Index == 5135)
	{
		if(player->bStatus.Level != 39)
		{
			SendClientMessage(p->Header.ClientId, "Volte aqui no nível 40.");
			return;
		}

		if(!wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Block40Cele)
		{
			if(wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame < 200)
			{
				SendClientMessage(p->Header.ClientId, "É necessário possuir 200 de Fame.");
				return;
			}

			for(INT8 e = 0; e < 7; e++)
			{
				memset(&player->Inventory[p->Slot[e]], 0, sizeof st_Item);

				SendItem(p->Header.ClientId, INVENTORY, p->Slot[e], &player->Inventory[e]);
			}

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Quests.Block40Cele = TRUE;

			wdBuffer[p->Header.ClientId].Chars[wdBuffer[p->Header.ClientId].Ingame.LoggedMob].Fame -= 200;

			SendClientMessage(p->Header.ClientId, "Nível foi desbloqueado com sucesso.");

			SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
			return;
		}

		SendClientMessage(p->Header.ClientId, "Seu nível já foi desbloqueado.");
		return;
	}

	if(p->ItemId[0].Index == 4043 && p->ItemId[1].Index == 4043)
	{
		if(p->ItemId[3].Index != 3338 && p->ItemId[3].Index)
			return;
		else if(p->ItemId[4].Index != 3338 && p->ItemId[4].Index)
			return;
		else if(p->ItemId[5].Index != 3338 && p->ItemId[5].Index)
			return;
		else if(p->ItemId[6].Index != 3338 && p->ItemId[6].Index)
			return;

		for(INT8 i = 0; i < sizeof(NotCharms) / sizeof(INT16); i++)
		{
			if(player->Inventory[p->Slot[2]].Index == NotCharms[i])
			{
				SendClientMessage(p->Header.ClientId, "Algo está errado com a combinação.");
				return;
			}
		}

		INT16 RefDoItem = GetItemSanc(&p->ItemId[2]);

		if(RefDoItem <= 233 || RefDoItem >= 250) 
		{
			SendClientMessage(p->Header.ClientId, "A refinação do item deve estar entre +11 e +14.");
			return;
		}

		UINT8 chances = 0;
		chances += (BASE_GetItemSanc(&p->ItemId[3]) + 2);
		chances += (BASE_GetItemSanc(&p->ItemId[4]) + 2);
		chances += (BASE_GetItemSanc(&p->ItemId[5]) + 2);
		chances += (BASE_GetItemSanc(&p->ItemId[6]) + 2);
		chances += GetChanceRefOdin(&p->ItemId[2]);

		for(INT8 e = 3; e < 7; e++)
			memset(&player->Inventory[p->Slot[e]], 0, sizeof st_Item);

		memset(&player->Inventory[p->Slot[0]], 0, sizeof st_Item);
		memset(&player->Inventory[p->Slot[1]], 0, sizeof st_Item);

		if(isVip(p->Header.ClientId))
			chances += 15;

		srand(time(NULL) / 5 * (rand() % 500) * 5);

		if((rand() % 100) <= chances)
		{
			SendNotice(" !!! ");

			RefinarItemMais(&player->Inventory[p->Slot[2]], 4);
		}
		else
			RefinarItemMais(&player->Inventory[p->Slot[2]], -4);

		SendALL(p->Header.ClientId);

		SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
		return;
	}

	SendClientMessage(p->Header.ClientId, "Há algo de errado com sua composição.");
}

void Ailyn(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *p = (st_Window*)m_PacketBuffer;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	if(p->Header.ClientId < 0 || p->Header.ClientId > MAX_PLAYER)
		return;

	for(INT8 i = 0; i < 7; i ++)
	{
		if(p->Slot[i] == 0xFF)
			return;

		else if(memcmp(&p->ItemId[i], &player->Inventory[p->Slot[i]], sizeof st_Item))
			return;

		else if(p->ItemId[i].Index != player->Inventory[p->Slot[i]].Index)
			return;

		if(p->ItemId[i].Index < 0 || p->ItemId[i].Index > MAX_ITEMLIST)
			return;
	}

	for(INT8 i = 0; i < sizeof(NotCharms) / sizeof(INT16); i++)
	{
		if(player->Inventory[p->Slot[0]].Index == NotCharms[i])
		{
			SendClientMessage(p->Header.ClientId, "Você não pode compor este item.");
			return;
		}
	}

	if(player->Gold < 50000000)
	{
		SendClientMessage(p->Header.ClientId, "É necessário possuir 50 Milhões(50kk) de Gold.");
		return;
	}

	if(GetItemSanc(&player->Inventory[p->Slot[0]]) != 9 || GetItemSanc(&player->Inventory[p->Slot[1]]) != 9)
	{
		SendClientMessage(p->Header.ClientId, "A refinação do item deve ser +9.");
		return;
	}

	if(p->ItemId[2].Index != 1774)
		return;

	for(INT8 i = 3; i < 7; i++)
	{
		if(p->ItemId[i].Index < 2441 || p->ItemId[i].Index > 2444)
			return;
	}

	INT16 AddItem = p->ItemId[3].Index - 2441;

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	INT8 Random = rand() % 100, Chances = 0;

	if(isVip(p->Header.ClientId))
		Chances += 15;

	char Message[260];

	INT8 Size = 0;

	if(Random <= 40 + Chances)
	{
		Size = 1;

		SetItemSanc(&player->Inventory[p->Slot[0]], (230 + AddItem));

		SendItem(p->Header.ClientId, INVENTORY, p->Slot[0], &player->Inventory[p->Slot[0]]);

		sprintf(Message, "%s obteve sucesso na composição do item %s. (%d/%d)", player->Name, ItemList[player->Inventory[p->Slot[0]].Index].Name, Random, Chances);
	}
	else
	{
		Size = 2;

		sprintf(Message, "Houve falha na composição do item.");
	}

	for(INT8 o = Size; o < 7; o++)
	{
		memset(&player->Inventory[p->Slot[o]], 0, sizeof(st_Item));

		SendItem(p->Header.ClientId, INVENTORY, p->Slot[o], &player->Inventory[p->Slot[o]]);
	}

	player->Gold -= 50000000;

	SendEtc(p->Header.ClientId);

	SendClientMessage(p->Header.ClientId, Message);

	SendClientSignalParm(p->Header.ClientId, 0x7530, 0x3A7, 2);
}