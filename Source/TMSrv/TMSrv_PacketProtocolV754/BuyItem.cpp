#include "DLLMain.h"

void FixBuyItem_SERVER(BYTE *m_PacketBuffer, bool *pRetn)
{
	p379 *p = (p379*)m_PacketBuffer;
	
	if(p->Header.ClientId < 0 || p->Header.ClientId > MAX_PLAYER)
		return;

	if(p->mobID > 30000 || p->mobID < MAX_PLAYER)
		return;

	if(p->sellSlot < 0 || p->sellSlot > 64)
		return;

	*pRetn = true;

	INT16 cId = p->Header.ClientId;

	st_Mob *Npc    = GetMobFromIndex(p->mobID),
		   *player = GetMobFromIndex(cId);

	st_Item *item = &Npc->Inventory[p->sellSlot];

	if(Npc->Status.DEX == 601)
	{
		// Função do Donate		
		for(int i = 0; i < sizeof(DonateList) / sizeof(Donate); i++)
		{
			if(!DonateList[i].Item.Index)
				continue;

			// memcmp retorna 0 quando os dois tipos comparados são iguais
			// quando o retorno é diferente de 0 quer dizer que não são totalmente compatíveis
			// se o retorno é diferente de 0, então é true
			if(memcmp(item, &DonateList[i].Item, sizeof(st_Item)))
				continue;

			char tmp[108];

			*pRetn = true;

			//if(DonateList[i].Store <= 0)
			//{
			//	sD1D(0x7530, cId, "Não há unidades disponíveis deste item para a venda.", MSG_COLOR_DONATE);

			//	//SendLog(Users[cId].Username, "%s tentou comprar item %s sem unidades disponíveis no donate.", player->Name, ItemList[DonateList[i].Item.Index].Name);

			//	return;
			//}

			if(DonateList[i].Price > wdBuffer[cId].Cash)
			{
				sD1D(0x7530, cId, "Não possui SOD Coins suficientes.", MSG_COLOR_DONATE);

				//SendLog(Users[cId].Username, "%s tentou comprar item %s sem SODcoins suficientes.", player->Name, ItemList[DonateList[i].Item.Index].Name);

				return;
			}

			if(wdBuffer[cId].Ingame.LastClicked != item->Index)
			{
				// Confirmação de compra do item, para evitar aquilo de "Comprei sem querer"
				// Dessa forma é necessário clicar duas vezes para comprar o item
				// Posteriormente tentar adicionar clock junto a essa info
				// Para colocar para sumir 1 minuto depois a confirmação
				sprintf(tmp, "Deseja adquirir [%s] por [%d] SOD Coins? %d unidades disponíveis.", ItemList[item->Index].Name, DonateList[i].Price, DonateList[i].Store);

				sD1D(0x7530, cId, tmp, MSG_COLOR_DONATE);

				wdBuffer[cId].Ingame.LastClicked = item->Index;

				return;
			}

			wdBuffer[cId].Ingame.LastClicked = 0;

			int freeSlot = -1;

			for(int e = 0; e < sizeof(Users[0].Storage.Item) / sizeof(st_Item); e++)
			{
				// Procura por slot vazio no Baú

				if(Users[cId].Storage.Item[e].Index)
					continue;
				else
				{
					freeSlot = e;

					break;
				}
			}

			if(freeSlot == -1 || freeSlot < 0 || freeSlot > 127)
			{
				sD1D(0x7530, cId, "Não possui espaço suficiente no cargo.", MSG_COLOR_DONATE);

				//SendLog(Users[cId].Username, "%s tentou comprar item %s sem espaço suficiente.",  player->Name, ItemList[DonateList[i].Item.Index].Name);

				return;
			}
			
			wdBuffer[cId].Cash -= DonateList[i].Price;

			SaveAccount(cId);

			/*DonateList[i].Store--;*/

			memcpy(&Users[p->Header.ClientId].Storage.Item[freeSlot], &DonateList[i].Item, sizeof(st_Item));

			sprintf(tmp, "Item [%s] adquirido por [%d] SOD Coins.", ItemList[item->Index].Name, DonateList[i].Price);

			sD1D(0x7530, cId, tmp, MSG_COLOR_DONATE);

			SendItem(cId, CARGO, freeSlot, &DonateList[i].Item);
			//SendLog(Users[cId].Username, "%s %s", player->Name, tmp);

			return;
		}
	}
	else
	{
		if(player->Gold < ItemList[item->Index].Price)
		{
			SendClientMessage(cId, "Gold insuficiente.");

			return;
		}

		// Tenta adicionar no inventário normal
		if(!PutItem(cId, item))
		{
			// Se não der, tenta adicionar no segundo inventário
			if(!PutItemnInv(cId, item))
			{
				SendClientMessage(cId, "Espaço insuficiente.");

				return;
			}
		}

		player->Gold -= ItemList[item->Index].Price;

		SendEtc(cId);

		//SendLog(Users[cId].Username, "Item %s adquirido por %d no npc %s.", ItemList[item->Index].Name, ItemList[item->Index].Price, Npc->Name);

		War.CityTaxs[player->Info.CityID] += (ItemList[item->Index].Price / 100) * War.Tax[player->Info.CityID];
	}
}