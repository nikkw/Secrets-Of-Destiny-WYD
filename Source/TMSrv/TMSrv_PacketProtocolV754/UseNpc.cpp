#include "DLLMain.h"

void UseNpcs(BYTE *m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > MAX_PLAYER)
		return;

	if(p->npcid > 32760 || p->npcid < 1000)
		return;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId),
		   *npc    = GetMobFromIndex(p->npcid);

	if(BASE_GetDistance(player->LastX, player->LastY, npc->LastX, npc->LastY) > 12)
	{
		*pRetn = true;

		SendClientMessage(p->Header.ClientId, "Você está muito distante do npc. Aproxime-se mais.");

		return;
	}

	//SendLog(Users[p->Header.ClientId].Username, "%s usou o npc %s.", player->Name, npc->Name);

	//Perzens
	if(npc->Info.Merchant == 8 && (npc->Status.Level > 0 && npc->Status.Level < 4))
	{
		Perzens(m_PacketBuffer, pRetn);
		*pRetn = true;
		return;
	}

	//Npcs de Skill
	if(npc->Info.Merchant == 19 && player->Equip[10].Index == 1742)
	{
		Sephirot(m_PacketBuffer, pRetn);
		*pRetn = true;
		return;
	}

	if(npc->Info.Merchant == 30)
	{
		switch(npc->bStatus.Level)
		{
			case 1: case 2:
				Juli(m_PacketBuffer, pRetn);
				*pRetn = true;
				break;

			case 3:
				GuardaReal(m_PacketBuffer, pRetn);
				*pRetn = true;
				break;

			default:
				break;
		}
	}

	if(npc->Info.Merchant == 42)
	{
		switch(npc->bStatus.Level)
		{
			case 1:
				Kibita(p->Header.ClientId, p->npcid);
				*pRetn = true;
				return;

			case 2:
				MestreHab(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			case 3:
				GodGovernament(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			case 4: case 5: case 6: case 7: case 8:
			{
				*pRetn = true;

				EntradasQuest(p->Header.ClientId, p->npcid, npc->bStatus.Level - 4);

				break;
			}

			case 9:
				KingDomBroker(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			case 10:
				Oraculo(m_PacketBuffer, pRetn);
				*pRetn = true;
				return;

			case 11:
				 Cosmos(p->Header.ClientId, p->npcid);
				 *pRetn = true;
				 break;

			case 33:
				KingDom(m_PacketBuffer, pRetn);
				*pRetn = true;
				return;

			case 34:
				Arch(m_PacketBuffer, pRetn);
				*pRetn = true;
				return;

			case 35:
				Khadin(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			case 36:
				NpcDeTroca(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			default:
				break;
		}
	}

	if(npc->Info.Merchant == 43)
	{
		switch(npc->bStatus.Level)
		{
			case 1:
				*pRetn = true;
				break;

			case 3: case 4:
				QuestCapaVerde(m_PacketBuffer, pRetn);
				*pRetn = true;
				break;

			case 5: case 6: case 7:
			{
				*pRetn = true;

				Unis(p->Header.ClientId, p->npcid, npc->Status.Level - 5);

				break;
			}

			case 8:
				CarbWind(p->Header.ClientId, p->npcid);
				*pRetn = true;
				break;

			default:
				break;
		}
	}
}

void Cosmos(INT16 cId, INT16 npcId)// Quest Molar do Gárgula
{
	st_Mob *player = GetMobFromIndex(cId),
		   *npc    = GetMobFromIndex(npcId);

	if(player->Equip[0].EFV2 != MORTAL)// Mortais apenas
	{
		SendSay(npcId, "Quest exclusiva aos Mortais.");

		return;
	}

	if(player->Status.Level < 200 || player->Status.Level > 249)// 201 ao 250
	{
		SendSay(npcId, "Nível permitido: 201 ao 250.");

		return;
	}

	DoTeleport(cId, 798, 4062);
}

void NpcDeTroca(INT16 cId, INT16 npcId)
{
	st_Mob *player = GetMobFromIndex(cId),
		   *npc    = GetMobFromIndex(npcId);

	INT8 TradeCount = npc->Status.DEX - 1500;

	if(TradeCount < 0 || TradeCount > 5)
	{
		SendSay(npcId, "Desculpe.");
		
		return;
	}

	INT8 slots[5] = {-1, -1, -1, -1, -1};

	for(int i = 0; i < 5; i++)
	{
		INT16 id = Server.Event.Trade[TradeCount].RequestItem[i].Index;

		if(!id)
			continue;

		INT8 slot = GetFirstSlot(cId, id, INVENTORY);

		if(slot == -1)
		{
			SendClientMsg(cId, "Onde está o item %s?", ItemList[id].Name);

			return;
		}

		slots[i] = slot;
	}

	for(int i = 0; i < 5; i++)
	{
		if(slots[i] == -1)
			continue;

		memset(&player->Inventory[slots[i]], 0, sizeof st_Item);

		SendItem(cId, INVENTORY, slots[i], &player->Inventory[slots[i]]);
	}

	INT8 pos = -1;

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	do
	{
		// Garante que uma posição com prêmio válido será gerada
		pos = rand() % 3;
	}while(!Server.Event.Trade[TradeCount].SendedItem[pos].Index);

	st_Item premio;

	memcpy(&premio, &Server.Event.Trade[TradeCount].SendedItem[pos], sizeof st_Item);

	if(!PutItem(cId, &premio))
		PutItemnInv(cId, &premio); // Precaução.	
}

void CarbWind(INT16 cId, INT16 npcId)
{
	st_Mob *player = GetMobFromIndex(cId);

	if(player->Equip[0].EFV2 != MORTAL && player->bStatus.Level >= 40)
	{
		SendSay(npcId, "Você precisa ser mortal e nível inferior a 35.");

		return;
	}

	SendSay(npcId, "Sente-se mais forte agora?");

	Buff(cId, 2000, 2000, 43);
	Buff(cId, 2000, 2000, 44);
	Buff(cId, 2000, 2000, 45);

	GetCurrentScore(cId);
	SendScore(cId);
	return;
}

void Unis(INT16 cId, INT16 npcId, INT8 QuestId)
{
    static UINT8 AddsDelivery[3][4] =
	{
		{EF_SANC, 5, EF_DAMAGE, 45},
		{EF_SANC, 5, EF_DAMAGE, 45},
		{EF_SANC, 5, EF_MAGIC, 20}
	};
 
    // QuestId é qual uni ele clicou
    st_Mob *player = GetMobFromIndex(cId),
           *npc    = GetMobFromIndex(npcId);
 
    if(player->Status.Level < 4 || player->Status.Level > 254 || player->Equip[0].EFV2 != MORTAL)
    {
        SendSay(npcId, "Somente mortais entre os níveis 5 e 255.");
 
        return;
    }
 
    if(QuestId < 3)
    {
        INT8 slot = GetFirstSlot(cId, ItensReceive[QuestId], EQUIP);

		st_Item *pItem = &player->Equip[slot];
 
		if(slot == -1)
		{
			char msg[120];

			sprintf(msg, "Traga-me %s para realizar a troca.", ItemList[ItensReceive[QuestId]].Name);

			SendSay(npcId, msg);
 
			return;
		}

        else if(GetItemSanc(&player->Equip[slot]) != 3)
		{
			SendSay(npcId, "É necessário que este item esteja +3.");
 
			return;
		}
 
        AmountMinus(pItem);
 
		pItem->Index = ItensDelivery[QuestId];

        PutAddOnItem(pItem, AddsDelivery[QuestId][0], AddsDelivery[QuestId][2], AddsDelivery[QuestId][1], AddsDelivery[QuestId][3]);
 
        SendItem(cId, EQUIP, slot, pItem);

        SendSay(npcId, "Você ficou muito bem com sua nova arma!");
    }
}

void Khadin(INT16 clientId, INT16 npcId)
{
	st_Mob *player = GetMobFromIndex(clientId),
		   *npc = GetMobFromIndex(npcId);

	if(player->Equip[0].EFV2 < CELESTIAL || player->Equip[0].EFV2 > SCELESTIAL)
	{
		SendClientMessage(clientId, "Somente celestiais ou acima.");

		return;
	}

	if(player->Equip[11].Index < 1760 || player->Equip[11].Index > 1763)
	{
		SendClientMessage(clientId, "Traga-me o Sephirote da classe desejada.");

		return;
	}

	if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame < 200)
	{
		SendClientMessage(clientId, "Necessário possuir 200 de Fame para prosseguir.");

		return;
	}

	player->ClassInfo = player->Equip[11].Index - 1760;

	INT16 face = 0;

	// Puxa a face que deveria ser pela face do mortal
	// Caso seja bm transformado faz 21 (face de bm mortal) + 5 (para ir para as faces de arch) + classInfo (já alterada para a nova)
	// Caso não, pega diretamente pela face do mortal soma 5 e a clasInfo
	if((Users[clientId].CharList.Equip[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal][0].Index >= 22 &&
		Users[clientId].CharList.Equip[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal][0].Index <= 25) ||
		Users[clientId].CharList.Equip[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal][0].Index == 32)
		face = 21 + 5 + player->ClassInfo;
	else
		face = Users[clientId].CharList.Equip[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal][0].Index + 5 + player->ClassInfo;

	player->Equip[0].Index = face;
	player->Equip[0].EFV3  = face;

	wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame -= 200;

	memset(&player->Equip[11], 0, sizeof(st_Item));

	SendClientMessage(clientId, "Sua classe foi alterada.");

	SendCharList(clientId);

	return;
}

void GodGovernament(INT16 clientId, INT16 npcId)
{
	char szMsg[256];

	st_Mob *player = (st_Mob*)GetMobFromIndex(clientId);

	if(player->Equip[0].EFV2 >= HARDCORE)
	{
		if(BASE_GetItemSanc(&player->Equip[1]) < 9)
		{
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame >= 100)
			{
				RefinarItemMais(&player->Equip[1], 1);

				SendItem(clientId, EQUIP, 1, &player->Equip[1]);

				wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame -= 100;

				SendClientMessage(clientId, "Quest concluida.");
			}
			else
				SendClientMessage(clientId, "Traga-me 100 de fame para a refinação.");

			return;
		}
	}

	if(GetTotKill(clientId) < 100)
	{
		SendSay(npcId, "Troco 100 de Frags por 10 Fames Player/Guild.");
		return;
	}

	wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame += 10;

	Guilds[player->GuildIndex].FAME += 10;

	SetTotKill(clientId, GetTotKill(clientId) - 100);

	SendEtc(clientId);
	SendScore(clientId);
	SendStats(clientId);

	BYTE packet[108]; 

	BASE_GetCreateMob(clientId, (BYTE*)&packet);
	GridMulticast(clientId, player->TargetX, player->TargetY, (void*)&packet);

	SendCreateMob(clientId, clientId, 1); 

	SendSay(npcId, "Troca realizada com sucesso.");
}

void Kibita(INT16 clientId, INT16 npcId)
{
	st_Mob *player = (st_Mob*)GetMobFromIndex(clientId);

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	if(!wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Cidadania)
	{
		if(player->Gold < 5000000)
		{
			SendClientMessage(clientId, "Preciso de 5 Milhões(5kk) para cadastrar você nesse servidor.");
			return;
		}

		player->Gold -= 5000000;

		wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Cidadania = SERV_1;

		SendClientMessage(clientId, "Você se cadastrou nesse servidor.");

		return;
	}
	else
	{
		if((DayOfWeek() >= Segunda && DayOfWeek() <= Sexta) && now->tm_hour == 21 && player->Equip[0].EFV2 == MORTAL && player->bStatus.Level < 369)
		{
			INT16 RestLac = GetFirstSlot(clientId, 420, INVENTORY);

			if(RestLac == -1)
			{
				SendSay(npcId, "Traga-me um Resto de Lactolerium.");

				return;
			}

			bool hasSoulOn = false;

			for(INT8 i = 0; i < 16; i++)
			{
				if(mBuffer[clientId].Affects[i].Index == 29)
				{
					hasSoulOn = true;
					mBuffer[clientId].Affects[i].Master = 11;
					mBuffer[clientId].Affects[i].Time = 10800;
					mBuffer[clientId].Affects[i].Value = 4;
					break;
				}
				if(!hasSoulOn)
				{
					if(!mBuffer[clientId].Affects[i].Index)
					{
						mBuffer[clientId].Affects[i].Index = 29;
						mBuffer[clientId].Affects[i].Master = 11;
						mBuffer[clientId].Affects[i].Time = 10800;
						mBuffer[clientId].Affects[i].Value = 4;
						break;
					}
				}
			}

			DoTeleport(clientId, 2463, 1841);

			GetCurrentScore(clientId);

			AmountMinus(&player->Inventory[RestLac]);

			SendItem(clientId, INVENTORY, RestLac, &player->Inventory[RestLac]);

			return;
		}

		const WORD szStones [4] = {5334, 5336, 5335, 5337};

		if(player->Equip[15].Index != 3194 && player->Equip[15].Index != 3195 && player->Equip[15].Index != 3196)
		{
			if(player->bStatus.Level >= 369 && player->Equip[0].EFV2 == MORTAL)
			{
				if(player->ClassInfo < 0 || player->ClassInfo > 3)
				{
					SendClientMessage(clientId, "Há um erro na sua conta. Favor contatar a administração");

					return;
				}

				INT16 slotId = GetFirstSlot(clientId, szStones[player->ClassInfo], INVENTORY);

				if(slotId == -1)
				{
					char szMsg[256];

					sprintf(szMsg, " Traga-me a %s para adiquirir a soul.", ItemList[szStones[player->ClassInfo]].Name);

					SendClientMessage(clientId, szMsg);

					return;
				}

				memset(&player->Equip[15], 0, sizeof st_Item);
				memset(&player->Inventory[slotId], 0, sizeof st_Item);

				INT16 kingDom = 0;

				if(player->CapeInfo == 7)
					kingDom = 3194;
				if(player->CapeInfo == 8)
					kingDom = 3195;
				else
					kingDom = 3196;

				player->Equip[15].Index = kingDom;

				SendItem(clientId, EQUIP, 15, &player->Equip[15]);
			
				player->Learn |=  (1 << 30);

				SendCharList(clientId);

				SendClientMessage(clientId, "Que os Deuses de Kersef ilumine seu caminho.");

				SendClientSignalParm(clientId, clientId, 0x3B4, wdBuffer[clientId].Ingame.LoggedMob);
			}
		}
	}

	SendSay(npcId, "Desculpe.");
}

void Perzens(BYTE *m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
		   *npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	static const INT16 Itens[][2] =
	{
		{4129, 3987},
		{4130, 3989},
		{4128, 3986}
	};

	INT8 Index = npc->Status.Level - 1;

	INT32 freeSlot = GetFirstSlot(p->Header.ClientId, Itens[Index][0], INVENTORY);

	char szMsg[108];
	if(freeSlot == -1)
	{
		sprintf(szMsg, "Traga-me a %s.", ItemList[Itens[Index][0]].Name, ItemList[Itens[Index][1]].Name);
		SendSay(p->npcid, szMsg);
		return;
	}

	memset(&player->Inventory[freeSlot], 0x0, sizeof(st_Item));
	player->Inventory[freeSlot].Index = Itens[Index][1];

	sprintf(szMsg, "Recebeu [%s].", ItemList[Itens[Index][1]].Name);

	SendSay(p->npcid, szMsg);
	SendItem(p->Header.ClientId, INVENTORY, freeSlot, &player->Inventory[freeSlot]);
	return;
}

void Juli(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
		   *npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	st_Position Dest[2];

	Dest[0].X = 3649;
	Dest[0].Y = 3133;
	Dest[1].X = 2480;
	Dest[1].Y = 1651;

	if(player->Gold < 1000)
		SendSay(p->npcid, "Para ser teleportado traga-me 1.000 de gold.");
	else
	{
		DoTeleport(p->Header.ClientId, Dest[npc->bStatus.Level - 1].X, Dest[npc->bStatus.Level - 1].Y);
		player->Info.CityID = npc->bStatus.Defense;
	}
	return;
}

void Sephirot(BYTE *m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
		   *npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	if(p->ClickOk == 1)
	{
		*pRetn = true;

		short Stones[8];
		bool hasStones = true;

		for(int i = 0; i < 8; i++)
		{
			Stones[i] = GetFirstSlot(p->Header.ClientId, 1744 + i, INVENTORY);

			if(Stones[i] == -1)
			{
				hasStones = false;
				break;
			}
		}

		if(player->Gold < 30000000)
			SendSay(p->npcid, "São necessários 30 milhões de gold para compor Sephirot.");
		else
		{
			if(hasStones)
			{
				for(int i = 0; i < sizeof(Stones) / sizeof(short); i++)
				{
					memset(&player->Inventory[Stones[i]], 0, sizeof(st_Item));
					SendItem(p->Header.ClientId, INVENTORY, Stones[i], &player->Inventory[Stones[i]]);
				}

				st_Item sephirot;
				memset(&sephirot, 0x0, sizeof(st_Item));

				sephirot.Index = 1760 + npc->ClassInfo;
					
				PutItem(p->Header.ClientId, &sephirot);
					
				player->Gold -= 30000000;

				SendEtc(p->Header.ClientId);
				SendSay(p->npcid, "Recebeu Sephirot. Equipe-o e procure o rei.");
			}
			else
				SendSay(p->npcid, "Traga-me todas as oito pedras.");
		}
	}
	else
	{
		SendSay(p->npcid, "Deseja compor o sephirot ?");
		*pRetn = true;
	}
}

void ReceiveBets(BYTE *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	p28F *p = (p28F*)m_PacketBuffer;

	if(p->Header.ClientId < 1 || p->Header.ClientId > MAX_PLAYER)
		return;

	else if(p->npcid < 1000 || p->npcid > 32000)
		return;

	st_Mob *player  = GetMobFromIndex(p->Header.ClientId),
		   *npc     = GetMobFromIndex(p->npcid);

	static const INT16 MaxMinCoordsCitys[4][4] = 
	{
		{2063, 2062, 2150, 2159}, // Armia
		{2459, 1646, 2665, 1765}, // Azran
		{2449, 1968, 2474, 2023}, // Erion
		{3606, 3101, 3687, 3159}  // Karden
	};

	if(p->Header.PacketId == 0x28E)
	{
		if(DayOfWeek() != Sexta && DayOfWeek() != Sabado)
		{
			if(GetCity(p->Header.ClientId) != -1)
			{
				char szMsg[108];
				sprintf(szMsg, "Imposto recolhido: %d", War.CityTaxs[GetCity(p->Header.ClientId)]);
				SendSay(p->npcid, szMsg);
			}
		}
	}
	else
	{
		INT8 CityId = GetCity(p->Header.ClientId);
	
		if(CityId < 0 || CityId > 3)
		{
			// Cidade desconhecida
			SendSay(p->npcid, "Houve um erro durante a aposta, favor contatar a administração.");

			return;
		}

		if(BASE_GetDistance(player->LastX, player->LastY, npc->LastX, npc->LastY) > 12)
		{
			SendClientMessage(p->Header.ClientId, "Para usar o npc aproxime-se mais.");

			return;
		}

		if(player->Equip[12].Index != 509 && (player->Equip[12].Index < 526 || player->Equip[12].Index > 528))
		{
			// Não é Lider/Sub mas está tentando apostar.
			SendSay(p->npcid, "Somente líderes e sub-líderes podem apostar.");

			return;
		}

		if(player->GuildIndex == War.Owner[CityId]) // Dominante querendo apostar
		{
			SendSay(p->npcid, "Somente desafiantes podem apostar.");

			return;
		}

		if(p->BetValue < 0 || p->BetValue > 32760)
		{
			// Edição com WPE
			SendSay(p->npcid, "Valor de aposta inválido.");

			return;
		}

		if(p->BetValue > Guilds[player->GuildIndex].FAME)
		{
			SendSay(p->npcid, "Não possui fame suficiente.");

			return;
		}
	
		// Aumenta o valor total das apostas, que será entregue a guild vencedora
		War.BetValue[CityId] += p->BetValue;

		// Diminui a fame total e coloca como apostada
		Guilds[player->GuildIndex].FAME -= p->BetValue;
		Guilds[player->GuildIndex].BetValue[CityId] += p->BetValue;

		SendSay(p->npcid, "Aposta recolhida com sucesso, boa sorte!");
	}
}

void Arch(BYTE* m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
			*npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	*pRetn = true;

	if (player->Status.Level < 299)
	{
		SendSay(p->npcid, "Somente do nível 300 acima.");

		return;
	}
	else if (player->Equip[0].EFV2 != MORTAL)
	{
		SendSay(p->npcid, "Somente mortais.");

		return;
	}
	else if (player->Equip[10].Index != 1742)
	{
		SendSay(p->npcid, "Onde está a Imortalidade ?");

		return;
	}
	else if (player->Equip[11].Index < 1760 || player->Equip[11].Index > 1763)
	{
		SendSay(p->npcid, "Traga-me um sephirot para a composição.");

		return;
	}		

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
		SendSay(p->npcid, "Você não tem espaço suficiente para um novo personagem.");

		return;
	}						

	INT32 pClass = player->Equip[11].Index - 1760;

	memset(&player->Equip[10], 0, sizeof(st_Item));
	memset(&player->Equip[11], 0, sizeof(st_Item));

	wdBuffer[p->Header.ClientId].Chars[FreeSlot].RespectiveMortal = wdBuffer[p->Header.ClientId].Ingame.LoggedMob;

	MSG_DBCreateArch pServer;		

	pServer.Header.ClientId = p->Header.ClientId;
	pServer.Header.PacketId = 0x80F;
	pServer.Header.Size = sizeof MSG_DBCreateArch;		

	pServer.charSlot = FreeSlot;

	memcpy(&pServer.mob, &MobArch, sizeof MobArch);		
		
	pServer.mob.ClassInfo = pClass;		
	strcpy((char*)pServer.mob.Name, (char*)player->Name);
	INT16 face = (player->ClassInfo == 2? (21 + 5) + pClass : (player->Equip[0].Index + 5) + pClass);

	pServer.mob.Equip[0].Index = face;		
	pServer.mob.Equip[0].EFV2 = ARCH;
	pServer.mob.Equip[0].EFV3 = face;

	pServer.mob.ClassInfo = pClass;

	pServer.mob.bStatus.Move.Speed = 3;
	pServer.mob.Status.Move.Speed = 3;	

	SendCharList(p->Header.ClientId);
		
	SendDBPacket((BYTE*)&pServer, sizeof MSG_DBCreateArch);

	SendClientSignalParm(p->Header.ClientId, p->Header.ClientId, 0x3B4, FreeSlot);

	return;
}

void KingDom(BYTE* m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
			*npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	st_Item *Item = (st_Item*)&player->Equip[15];

	FindAmountItem Safiras = FindOcurrences(player->Inventory, 697);

	INT16 Agua = GetFirstSlot(p->Header.ClientId, 5334, INVENTORY),
		  Terra = GetFirstSlot(p->Header.ClientId, 5335, INVENTORY),
		  Sol = GetFirstSlot(p->Header.ClientId, 5336, INVENTORY),
		  Vento = GetFirstSlot(p->Header.ClientId, 5337, INVENTORY),
		  ItemReino = GetFirstSlot(p->Header.ClientId, 5339, INVENTORY);

	*pRetn = true;

	if(Agua != -1 && Terra != -1 && Sol != -1 && Vento != -1)
	{
		if(player->Equip[10].Index == 1742 && (player->Equip[11].Index >= 1760 && player->Equip[11].Index <= 1763))
		{
			AmountMinus(&player->Inventory[Agua]);
			AmountMinus(&player->Inventory[Terra]);
			AmountMinus(&player->Inventory[Sol]);
			AmountMinus(&player->Inventory[Vento]);
			AmountMinus(&player->Equip[10]);
			AmountMinus(&player->Equip[11]);

			SendItem(p->Header.ClientId, EQUIP, 10, &player->Equip[10]);    
			SendItem(p->Header.ClientId, EQUIP, 11, &player->Equip[11]);             
			SendItem(p->Header.ClientId, INVENTORY, Agua, &player->Inventory[Agua]);   
			SendItem(p->Header.ClientId, INVENTORY, Terra, &player->Inventory[Terra]); 
			SendItem(p->Header.ClientId, INVENTORY, Sol, &player->Inventory[Sol]);    
			SendItem(p->Header.ClientId, INVENTORY, Vento, &player->Inventory[Vento]);

			st_Item Ideal;
			memset(&Ideal, 0x0, sizeof(st_Item));

			Ideal.Index = 5338; 
			PutItem(p->Header.ClientId, &Ideal);

			SendClientMessage(p->Header.ClientId, "Pedra Ideal criada com sucesso.");
			return;
		}
	}

	if(player->Equip[0].EFV2 <= ARCH)
	{
		if(Item->Index == CapeBroker[2])
		{
			Item->Index = KingDomCape[npc->CapeInfo - 7][2];

			SendItem(p->Header.ClientId, EQUIP, 15, Item);

			SendClientMessage(p->Header.ClientId, "Que a luz de sephira esteja com você.");

			AmountMinus(&player->Inventory[ItemReino]);

			SendItem(p->Header.ClientId, INVENTORY, ItemReino, &player->Inventory[ItemReino]);

			return;
		}

		else if(Item->Index == CapeBroker[3])
		{
			Item->Index = KingDomCape[npc->CapeInfo - 7][3];

			SendItem(p->Header.ClientId, EQUIP, 15, Item);

			SendClientMessage(p->Header.ClientId, "Que a luz de sephira esteja com você.");

			AmountMinus(&player->Inventory[ItemReino]);

			SendItem(p->Header.ClientId, INVENTORY, ItemReino, &player->Inventory[ItemReino]);

			return;
		}

		if(player->bStatus.Level >= 219 && player->bStatus.Level <= 254)
		{
			if(Item->Index == KingDomCape[0][0] || Item->Index == KingDomCape[1][0])
			{
				SendClientMessage(p->Header.ClientId, "Você é um bravo guerreiro!");
				return;
			}

			Item->Index = KingDomCape[npc->CapeInfo - 7][0];

			SendItem(p->Header.ClientId, EQUIP, 15, Item);

			SendClientMessage(p->Header.ClientId, "Que a luz de sephira esteja com você.");

			AmountMinus(&player->Inventory[ItemReino]);

			SendItem(p->Header.ClientId, INVENTORY, ItemReino, &player->Inventory[ItemReino]);

			return;
		}

		else if(player->bStatus.Level >= 254 && player->bStatus.Level <= 399)
		{
			if(Item->Index == KingDomCape[0][1] || Item->Index == KingDomCape[1][1] ||
				Item->Index == KingDomCape[0][2] || Item->Index == KingDomCape[1][2] ||
				Item->Index == KingDomCape[0][3] || Item->Index == KingDomCape[1][3])
			{
				SendClientMessage(p->Header.ClientId, "Você é um bravo guerreiro!");
				return;
			}

			Item->Index = KingDomCape[npc->CapeInfo - 7][1];

			SendItem(p->Header.ClientId, EQUIP, 15, Item);

			SendClientMessage(p->Header.ClientId, "Que a luz de sephira esteja com você.");

			AmountMinus(&player->Inventory[ItemReino]);

			SendItem(p->Header.ClientId, INVENTORY, ItemReino, &player->Inventory[ItemReino]);

			return;
		}
	}
	else if(player->Equip[0].EFV2 >= CELESTIAL)
	{
		if(Item->Index == KingDomCape[0][4] || Item->Index == KingDomCape[1][4])
		{
			SendClientMessage(p->Header.ClientId, "Você é um bravo guerreiro!");
			return;
		}

		Item->Index = KingDomCape[npc->CapeInfo - 7][4];

		SendItem(p->Header.ClientId, EQUIP, 15, Item);

		SendClientMessage(p->Header.ClientId, "Que a luz de sephira esteja com você.");

		AmountMinus(&player->Inventory[ItemReino]);

		SendItem(p->Header.ClientId, INVENTORY, ItemReino, &player->Inventory[ItemReino]);

		return;
	}
	
	SendClientMessage(p->Header.ClientId, "Você é um bravo guerreiro!");
}

void Oraculo(BYTE* m_PacketBuffer, bool *pRetn)
{
	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
			*npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	INT16 Uni   = GetFirstSlot(p->Header.ClientId, 1740, INVENTORY),
			Fenix = GetFirstSlot(p->Header.ClientId, 1741, INVENTORY);

	FindAmountItem Safiras = FindOcurrences(player->Inventory, 697);

	if(Uni != -1 && Fenix != -1 && Safiras.Amount >= 10)
	{
		if(((Uni + 1) % 9 != 0) && (Uni + 1) == Fenix)
		{
			for(INT8 i = 0; i < 11; i++)
			{
				memset(&player->Inventory[Safiras.Slots[i]], 0x0, sizeof(st_Item));
				SendItem(p->Header.ClientId, INVENTORY, Safiras.Slots[i], &player->Inventory[Safiras.Slots[i]]);
			}
			
			AmountMinus(&player->Inventory[Uni]);
			AmountMinus(&player->Inventory[Fenix]);

			st_Item Ideal;
			memset(&Ideal, 0x0, sizeof(st_Item));

			Ideal.Index = 1742; 
			PutItem(p->Header.ClientId, &Ideal);
			
			SendItem(p->Header.ClientId, INVENTORY, Fenix, &player->Inventory[Fenix]);
			SendItem(p->Header.ClientId, INVENTORY, Uni, &player->Inventory[Uni]);

			SendSay(p->npcid, "Imortalidade composta com sucesso, boa sorte !");
			return;
		}
		else
		{
			SendSay(p->npcid, "Você precisa alinhar as Almas.");
			return;
		}
	}
	else
	{
		SendSay(p->npcid, "Preciso de 2 Almas e 10 Safiras soltas.");
		return;
	}
}

void EntradasQuest(INT16 clientId, INT16 npcId, INT8 questIndex)
{
	char szTMP[256];

	st_Mob *player = GetMobFromIndex(clientId);

	if(player->bStatus.Level < Quests_Level[questIndex][0] || player->bStatus.Level > Quests_Level[questIndex][1])
	{
		sprintf(szTMP, "Level permitido: [%d~%d].", Quests_Level[questIndex][0] + 1, Quests_Level[questIndex][1] + 1);

		SendSay(npcId, szTMP);

		return;
	}

	if(player->Equip[0].EFV2 != MORTAL)
	{
		SendSay(clientId, "Você não é mais um Mortal.");

		return;
	}

	INT16 itemId = 4038 + questIndex,
	      slotId = GetFirstSlot(clientId, itemId, INVENTORY);

	if(slotId == -1)
	{
		sprintf(szTMP, "Aonde está %s?", ItemList[itemId].Name);

		SendSay(npcId, szTMP);

		return;
	}

	for(int i = 0; i < 40; i++)
	{
		if(!QuestList[questIndex].CidID[i])
		{
			QuestList[questIndex].CidID[i] = clientId;
			break;
		}
		else if(i == 39)
		{
			SendSay(npcId, "Quest cheia, tente novamente mais tarde.");

			return;
		}
	}
	
	AmountMinus(&player->Inventory[slotId]);

	DoTeleport(clientId, CoordsQuest[questIndex][0], CoordsQuest[questIndex][1]);

	SendItem(clientId, INVENTORY, slotId, &player->Inventory[slotId]);

	sprintf(szTMP, "Quest iniciada para %s.", player->Name);

	SendSay(npcId, szTMP);

}

void QuestCapaVerde(BYTE* m_PacketBuffer, bool *pRetn)
{
	char szMsg[256];

	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
			*npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	if(player->Equip[15].Index)
	{
		SendSay(p->npcid, "Você já completou a quest.");
		return;
	}

	if(player->Equip[0].EFV2 != MORTAL || (player->bStatus.Level <= 99 || player->bStatus.Level >= 150))
	{
		SendSay(p->npcid, "Level inadequado [101~151].");
		return;
	}
		
	if(npc->Info.Merchant == 43 && npc->bStatus.Level == 4)
	{
		DoTeleport(p->Header.ClientId, 2243, 1580);

		sprintf(szMsg, "Quest iniciada para %s", player->Name);
		SendSay(p->npcid, szMsg);
	}

	else if(npc->Info.Merchant == 43 && npc->bStatus.Level == 3)
	{
		if(player->Equip[13].Index != 4080)
		{
			SendSay(p->npcid, "Traga-me o Emblema da Aprendizagem equipado.");
			return;
		}

		player->Equip[15].Index = 4006;

		AmountMinus(&player->Equip[13]);

		SendItem(p->Header.ClientId, EQUIP, 13, &player->Equip[13]);

		SendItem(p->Header.ClientId, EQUIP, 15, &player->Equip[15]);

		SendSay(p->npcid, "Parabéns, adquiriu o Manto do Aprendiz.");
	}
}

void GuardaReal(BYTE* m_PacketBuffer, bool *pRetn)
{
	char szMsg[256];

	p28B *p = (p28B*)m_PacketBuffer;

	st_Mob *player = (st_Mob*)GetMobFromIndex(p->Header.ClientId),
			*npc    = (st_Mob*)GetMobFromIndex(p->npcid);

	if(player->Equip[0].EFV2 != MORTAL || (player->bStatus.Level <= 219 || player->bStatus.Level >= 250))
	{
		SendSay(p->npcid, "Level inadequado [221~251].");
		return;
	}

	DoTeleport(p->Header.ClientId, 1729, 1732);

	sprintf(szMsg, "Quest iniciada para %s", player->Name);
	SendSay(p->npcid, szMsg);

}

void KingDomBroker(INT16 clientId, INT16 npcId)
{
	char szMsg[256];

	st_Mob *player = (st_Mob*)GetMobFromIndex(clientId);

	wdBase *isBuffer = &wdBuffer[clientId];

	if(player->CapeInfo != 7 && player->CapeInfo != 8)
	{
		SendSay(npcId, "Você não pertence a nenhum Reino.");

		return;
	}

	INT16 Fame = 0;
	if(player->Equip[0].EFV2 == MORTAL)
		Fame = 100;
	else if(player->Equip[0].EFV2 == ARCH)
		Fame = 200;
	else if(player->Equip[0].EFV2 >= CELESTIAL)
		Fame = 500;

	if(Fame > isBuffer->Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame)
	{
		sprintf(szMsg, "Você precisa de %d pontos de Fame.", Fame);
		SendClientMessage(clientId, szMsg);
			
		return;
	}

	INT16 Cape = 0;
	if(player->Equip[15].Index == KingDomCape[0][0] || player->Equip[15].Index == KingDomCape[1][0])
		Cape = CapeBroker[0];
	else if(player->Equip[15].Index == KingDomCape[0][1] || player->Equip[15].Index == KingDomCape[1][1])
		Cape = CapeBroker[1];
	else if(player->Equip[15].Index == KingDomCape[0][2] || player->Equip[15].Index == KingDomCape[1][2])
		Cape = CapeBroker[2];
	else if(player->Equip[15].Index == KingDomCape[0][3] || player->Equip[15].Index == KingDomCape[1][3])
		Cape = CapeBroker[3];
	else if(player->Equip[15].Index == KingDomCape[0][4] || player->Equip[15].Index == KingDomCape[1][4])
		Cape = CapeBroker[4];
		
	player->Equip[15].Index = Cape;

	isBuffer->Chars[wdBuffer[clientId].Ingame.LoggedMob].Fame -= Fame;

	SendCharList(clientId);

	SendClientMessage(clientId, "Que a luz de sephira esteja com você.");
}

void MestreHab(INT16 clientId, INT16 npcId)
{
	char szMsg[256];

	st_Mob *player = (st_Mob*)GetMobFromIndex(clientId);

	FindAmountItem Safiras = FindOcurrences(player->Inventory, 4131);

	if(Safiras.Amount < 3)
	{
		SendSay(npcId, "Traga-me 30 safira(s).");
		return;
	}

	for(INT8 i = 1; i < 8; i++)
	{
		if(player->Equip[i].Index != 0)
		{
			SendSay(npcId, "Desequipe seus equipamentos.");
			return;
		}
	}

	if(player->ClassInfo > 3 || player->ClassInfo < 0) 
	{
		SendSay(npcId, "Ocorreu um erro, contate à Administração!");
		return;
	}

	for(INT8 i = 0; i < 3; i++)
	{
		memset(&Safiras.Itens[Safiras.Slots[i]], 0, sizeof (st_Item));
		SendItem(clientId, INVENTORY, Safiras.Slots[i], &player->Inventory[Safiras.Slots[i]]);
	}

	if((player->bStatus.STR - 100) < BaseSIDCHM[player->ClassInfo][0])
		player->bStatus.STR = BaseSIDCHM[player->ClassInfo][0];
	else
		player->bStatus.STR -= 100;

	if((player->bStatus.INT - 100) < BaseSIDCHM[player->ClassInfo][1])
		player->bStatus.INT = BaseSIDCHM[player->ClassInfo][1];
	else
		player->bStatus.INT -= 100;

	if((player->bStatus.DEX - 100) < BaseSIDCHM[player->ClassInfo][2])
		player->bStatus.DEX = BaseSIDCHM[player->ClassInfo][2];
	else
		player->bStatus.DEX -= 100;

	if((player->bStatus.CON - 100) < BaseSIDCHM[player->ClassInfo][3])
		player->bStatus.CON = BaseSIDCHM[player->ClassInfo][3];
	else
		player->bStatus.CON -= 100;

	BASE_GetBonusSkillPoint(player);
	BASE_GetBonusScorePoint(player);
	BASE_GetHpMp(player);
		
	GetCurrentScore(clientId);

	SendEtc(clientId);
	SendScore(clientId);
	SendStats(clientId);

	SendSay(npcId, "Resetado com sucesso.");

	BYTE packet[108]; 

	BASE_GetCreateMob(clientId, (BYTE*)&packet);
	GridMulticast(clientId, player->TargetX, player->TargetY, (void*)&packet);

	SendCreateMob(clientId, clientId, 1);	
}