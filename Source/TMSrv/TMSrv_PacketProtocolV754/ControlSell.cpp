#include "DLLMain.h"

void Control37A(BYTE *m_PacketBuffer, bool *pRetn)
{
	p37A *p = (p37A*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > 750)
		return;

	INT16 cId = p->Header.ClientId;

    if(p->type != INVENTORY)
	{
		*pRetn = true;
			
        return;
	}

	st_Mob *player = GetMobFromIndex(cId);

	st_Item *SellItem = GetItemPointer(player, Users[cId].Storage.Item, p->type, p->sellSlot);

	if(SellItem == NULL)
	{
		*pRetn = true;

		return;
	}

    for(INT8 i = 0; i < sizeof(NotSell) / sizeof(INT16); i++)
	{
        if(SellItem->Index == NotSell[i])
		{
			*pRetn = true;

			SendClientMessage(cId, "Este item não pode ser vendido.");

			//SendLog(Users[cId].Username, "%s %s tentou vender o item %s.",  player->Name, ItemList[SellItem->Index]);

			return;
		}
	}

	//SendLog(Users[cId].Username, "%s vendeu o item %s.", player->Name, ItemList[SellItem->Index]);
}

void Control398(BYTE *m_PacketBuffer, bool *pRetn)
{
	p398 *p = (p398*)m_PacketBuffer;

	if(p->mobId < 1 || p->mobId > MAX_PLAYER)
		return;

	else if(p->Header.ClientId < 1 || p->Header.ClientId > MAX_PLAYER)
		return;

	else if(p->Slot < 0 || p->Slot > 12)
		return;

	INT16 cId = p->Header.ClientId;

	st_Mob *buyer  = GetMobFromIndex(cId),
		   *seller = GetMobFromIndex(p->mobId);	

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	char szMsg[256];

	for(INT8 i = 0; i < sizeof(NotSell) / sizeof(INT16); i++)
	{
		if(Users[cId].AutoTrade.Item[p->Slot].Index == NotSell[i])
		{
			*pRetn = true;

			SendClientMessage(p->Header.ClientId, "Impossível negociar este item.");
				
			return;
		}
	}

	// Bloqueia o usuário ter mais que 2kkk no baú na loja.
	if((Users[p->mobId].Storage.Gold + Users[p->mobId].AutoTrade.Price[p->Slot]) > 2000000000)
	{
		*pRetn = true;

		SendClientMessage(cId, "Não é possível carregar mais que 2 bilhões de gold.");

		return;
	}

	sprintf_s(szMsg, "![%s] comprou [%s] por [%d] às [%d:%d:%d] de [%d/%d/%d]", buyer->Name, ItemList[p->Item.Index].Name, Users[p->mobId].AutoTrade.Price[p->Slot], now->tm_hour, now->tm_min, now->tm_sec, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
		
	SendClientMessage(p->mobId, szMsg);

	//SendLog(Users[cId].Username, szMsg);

	War.CityTaxs[buyer->Info.CityID] += (Users[p->mobId].AutoTrade.Price[p->Slot] / 100) * War.Tax[buyer->Info.CityID];
}