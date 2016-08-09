#include "DLLMain.h"

static const INT16 NotDesequip[] = {508, 509, 526, 527, 528, 3503, 3504, 3505, 3506};

void VerifyItemMovement(BYTE *m_PacketBuffer, bool *pRetn)
{
	p376 *p = (p376*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > 750)
		return;

	INT16 cId = p->Header.ClientId;

	st_Mob *player = GetMobFromIndex(cId);

	st_Item *srcItem = GetItemPointer(player, Users[cId].Storage.Item, p->SrcType, p->SrcSlot),
		    *dstItem = GetItemPointer(player, Users[cId].Storage.Item, p->DstType, p->DstSlot);

	if(p->SrcType == CARGO && p->DstType == EQUIP)
	{
		*pRetn = true;

		SendClientMessage(cId, "Passe o item para o inventário antes de equipá-lo.");

		//SendLog(Users[cId].Username, "%s tentou equipar item %s direto do cargo.", player->Name, ItemList[srcItem->Index].Name);


		return;
	}
	else if(player->Equip[0].EFV2 >= HARDCORE)
	{
		if((p->DstType == EQUIP && p->DstSlot == 1) ||
		   (p->SrcType == EQUIP && p->SrcSlot == 1))
		{
			*pRetn = true;

			SendClientMessage(cId, "Movimento não permitido.");

			//SendLog(Users[cId].Username, "%s tentou mover para o elmo do HardCore.", player->Name);

			return;
		}
	}

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	if(srcItem)
	{
		for(INT8 i = 0; i < sizeof(NotDesequip) / sizeof(INT16); i++)
		{
			if(srcItem->Index == NotDesequip[i])
			{
				SendClientMessage(p->Header.ClientId, "Não é possível movimentar este item.");

				*pRetn = true;

				return;
			}
		}

		if((srcItem->Index >= 4152 && srcItem->Index <= 4158) && ((player->Equip[0].Index >= 22 && player->Equip[0].Index <= 25) || player->Equip[0].Index == 32)) // Trajes
		{	
			*pRetn = true;

			SendClientMessage(cId, "Impossível equipar traje enquanto transformado.");

			//SendLog(Users[cId].Username, "%s tentou ativar traje transformado.", player->Name);

			return;
		}

		if(p->DstType == EQUIP && (!srcItem->EF1 && !srcItem->EFV1 && !srcItem->EF2 && !srcItem->EFV2 && !srcItem->EF3 && !srcItem->EFV3))
		{
			UINT8 Time = 0;

			if(p->DstSlot == 13)
			{
				if(srcItem->Index >= 3900 || srcItem->Index <= 3908) // Fadas
				{
					if(srcItem->Index > 3899 && srcItem->Index < 3903)
						Time = 2;// 3 Dias
					else if(srcItem->Index > 3902 && srcItem->Index < 3906)
						Time = 4;// 5 Dias
					else if(srcItem->Index > 3905 && srcItem->Index < 3909)
						Time = 6;// 7 Dias

					srcItem->EF1 = 106;
					srcItem->EFV1 = Time;
					srcItem->EF2 = 107;
					srcItem->EFV2 = 23;
					srcItem->EF3 = 108;
					srcItem->EFV3 = 59;

					SendItem(cId, INVENTORY, p->SrcSlot, srcItem);

					//SendLog(Users[cId].Username, "%s ativou %s.", player->Name, ItemList[srcItem->Index].Name);

					return;
				}
				else if(srcItem->Index >= 4152 && srcItem->Index <= 4158) // Trajes
					Time = 30;
			}
			else if(p->DstSlot == 14 && srcItem->Index >= 3980 && srcItem->Index <= 3989) // Esferas
			{
				if(srcItem->Index > 3979 && srcItem->Index < 3983)
					Time = 3;
				else if(srcItem->Index > 3982 && srcItem->Index < 3986)
					Time = 15;
				else if(srcItem->Index > 3985 && srcItem->Index < 3990)
					Time = 30;
			}

			if(Time)
			{
				srcItem->EF1 = 106;
				srcItem->EFV1 = now->tm_mday + Time; // Dia atual + tempo da mount
				srcItem->EF2 = 110;
				srcItem->EFV2 = ++now->tm_mon; // Aqui incrementamos a variável do mês para depois atribuirmos ao EFV2 o valor dela
				srcItem->EF3 = 109;
				srcItem->EFV3 = now->tm_year - 100; // Ano com um decrescimo de 100 pq o client é bagudo e lê essa porra toda doida

				CheckItemTime(srcItem);

				SendItem(cId, INVENTORY, p->SrcSlot, srcItem);
				//SendLog(Users[cId].Username, "%s ativou %s.", player->Name, ItemList[srcItem->Index].Name);
			}
		}
	}

	if(dstItem)
	{
		for(INT8 i = 0; i < sizeof(NotDesequip) / sizeof(INT16); i++)
		{
			if(dstItem->Index == NotDesequip[i])
			{
				SendClientMessage(cId, "Não é possível movimentar este item.");

				*pRetn = true;

				return;
			}
		}
	}
}