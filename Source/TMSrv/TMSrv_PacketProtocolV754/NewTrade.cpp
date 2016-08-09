#include "DLLMain.h"

void __stdcall NKD_SystemTrade(BYTE *m_PacketBuffer, int ClientID)
{
    SendTrade *p = (SendTrade*)m_PacketBuffer;

	if(ClientID < 0 || p->OtherClientid < 0 || p->OtherClientid > 750 || ClientID > 750)
		return;
	
	
	if(Users[ClientID].Status != 22)
		return;
	else if(Users[p->OtherClientid].Status != 22)
	{
		SendClientMessage(ClientID, "Jogador indisponível para a troca.");

	    return;
	}
   
    if(!Trade[p->OtherClientid].isTrading && !Trade[ClientID].isTrading)
    {
        // Verifica se nenhum dos dois jogadores está com trade
        // Se os dois não estiverem, quer dizer que foi enviado um pedido para Trade
        Sleep(2000);

        OpenTrade(ClientID, p->OtherClientid);

        Trade[ClientID].WaitingData = true;
        Trade[ClientID].Timer = clock();
        Trade[ClientID].isTrading = true;
        Trade[ClientID].ClientID = p->OtherClientid;
        Trade[ClientID].Confirm = false;

        Trade[p->OtherClientid].Timer = clock();
        Trade[p->OtherClientid].isTrading = true;
        Trade[p->OtherClientid].ClientID = ClientID;
        Trade[p->OtherClientid].Confirm = false;
    }
    else if(Trade[p->OtherClientid].isTrading && Trade[p->OtherClientid].ClientID != ClientID)
    {
        // Se você está sem o modo trade e o usuário que foi pedido estiver em negociação
        // a mensagem abaixo é mostrada
        SendClientMessage(ClientID, "O outro jogador já está em negociação!");
    }
    else 
	{ // Caso não seja um request, será feito as verificações para envio de item/confirm etc.
        if(Trade[ClientID].isTrading && Trade[ClientID].ClientID != p->OtherClientid)
        {
            // Para evitar qualquer tipo de bug se o jogador já está em troca
            // o trade do mesmo é fechado
            SendClientMessage(ClientID, "Você já está em modo troca!");
            CloseTrade(ClientID);
        }
        else if(Trade[p->OtherClientid].isTrading && !Trade[ClientID].isTrading && Trade[p->OtherClientid].WaitingData)
        {
            // Checa se o usuário que foi pedido o trade está sem trade novamente e se
            // o usuário que enviou o trade está realmente esperando o trade
            Trade[ClientID].isTrading = true;
            Trade[ClientID].WaitingData = true;
            Trade[ClientID].Confirm = false;
            Trade[ClientID].Timer = clock();
            Trade[ClientID].ClientID = p->OtherClientid;
            OpenTrade(ClientID, p->OtherClientid);
        }
        else if(p->Confirma)
        {
            if(clock() - Trade[ClientID].Timer < 2 *CLOCKS_PER_SEC)
            {
                // O próprio cliente existe proteção, mas como o packet pode ser manipulado e/ou enviado
                // pelo próprio usuário como forma de hack, é feito a proteção no servidor também
                // Caso queira, coloque um CloseTrade ao final dessa condição porque o client provavelmente não se enganará
                SendClientMessage(ClientID, "Aguarde 2 segundos e confirme.");
                Trade[ClientID].Timer = clock();
            }
            else 
			{
                Trade[ClientID].Confirm = p->Confirma;
                if(Trade[p->OtherClientid].Confirm)
                {
                    int amount_TradeOID = GetAmountItemOnTrade(p->OtherClientid);
                    int amount_TradeCID = GetAmountItemOnTrade(ClientID);
                    if(GetAmountItem(ClientID) < amount_TradeOID)
                    {
                        // Checa se a quantidade de itens nulos no inventário do usuário é igual ou maior
                        // que a quantidade de itens colocadas no trade
                        SendClientMessage(ClientID, "Você não possui espaço no inventário");
                        SendClientMessage(p->OtherClientid, "O outro jogador não possui espaço no inventário");
                        CloseTrade(ClientID);
                    }
                    else if(GetAmountItem(p->OtherClientid) < amount_TradeCID)
                    {
                        // Checa se a quantidade de itens nulos no inventário do usuário é igual ou maior
                        // que a quantidade de itens colocadas no trade
                        SendClientMessage(p->OtherClientid, "Você não possui espaço no inventário");
                        SendClientMessage(ClientID, "O outro jogador não possui espaço no inventário");
                        CloseTrade(ClientID);
                    } 
					else 
					{
                        st_Mob *player = GetMobFromIndex(ClientID);
                        st_Mob *mob = GetMobFromIndex(p->OtherClientid);

						// Adiciona o gold colocado no trade
						if((player->Gold + Trade[p->OtherClientid].Gold) <= 2000000000)
						{
                            player->Gold += Trade[p->OtherClientid].Gold;
							mob->Gold -= Trade[p->OtherClientid].Gold;
						}
						else
							CloseTrade(ClientID);
						

						if((mob->Gold + Trade[ClientID].Gold) <= 2000000000)
						{
							// Adiciona o gold colocado no trade do outro player
							mob->Gold += Trade[ClientID].Gold;
							// Retira o gold colocado no trade
							player->Gold -= Trade[ClientID].Gold;
						}
						else
							CloseTrade(p->OtherClientid);

						// Atualiza o gold do inventário dos dois players
						SendStats(ClientID);
                        SendStats(p->OtherClientid);

                        int SlotID = 0;
                        int SlotOID = 0;

                        for(UINT8 i=0;i<15;i++)
                        {
                            // Faz o loop para todos os itens do trade
                            // Slot livre do inventário
                            if(Trade[ClientID].Itens[i].Index)
                                SlotID = GetFirstSlot(p->OtherClientid, 0, INVENTORY);
                            // Slot livre do inventário
                            if(Trade[p->OtherClientid].Itens[i].Index)
                                SlotOID = GetFirstSlot(ClientID, 0, INVENTORY);
                            // Checa se os valores retornados são válidos
                            // Se retornar -1 quer dizer que a funçaõ anterior (GetAmountItem) aconteceu algum erro
                            if(SlotID == -1 || SlotOID == -1) 
							{
                                // O erro aconteceu então a mensagem é enviada aos dois players e o trade dos mesmos é fechado
                                SendClientMessage(ClientID, "Ocorreu um erro!");
                                SendClientMessage(p->OtherClientid, "Ocorreu um erro!");
                                CloseTrade(ClientID);
                            }
                            // Checa se existe algum item no slot correspondente do trade
                            if(Trade[ClientID].Itens[i].Index) 
							{
                                // Proteção contra criação de itens
								if(memcmp(&Trade[ClientID].Itens[i], &player->Inventory[Trade[ClientID].TradeItemSlot[i]], sizeof st_Item))
								{
									CloseTrade(ClientID);
									CloseTrade(p->OtherClientid);

									SendClientMessage(ClientID, "Ocorreu um erro!");
                                    SendClientMessage(p->OtherClientid, "Ocorreu um erro!");
								}
								else 
								{
									// Copia o item que está no trade do outro usuário
									memcpy(&mob->Inventory[SlotID], &Trade[ClientID].Itens[i], sizeof st_Item);
									// Apaga o item do inventário do outro usuário
									memset(&player->Inventory[Trade[ClientID].TradeItemSlot[i]], 0, sizeof st_Item);
									// Atualiza o slot do personagem em que o item foi apagado
									SendItem(ClientID, INVENTORY, Trade[ClientID].TradeItemSlot[i], &player->Inventory[Trade[ClientID].TradeItemSlot[i]]);
									SendItem(p->OtherClientid, INVENTORY, SlotID, &mob->Inventory[SlotID]);

									memset(&Trade[ClientID].Itens[i], 0, sizeof st_Item);
								}
                            }
                            // Checa se existe algum item no slot correspondente do trade
                            if(Trade[p->OtherClientid].Itens[i].Index) 
							{              
								// Proteção contra criação de itens
								if(memcmp(&Trade[p->OtherClientid].Itens[i], &mob->Inventory[Trade[p->OtherClientid].TradeItemSlot[i]], sizeof st_Item))
								{
									CloseTrade(ClientID);
									CloseTrade(p->OtherClientid);
									SendClientMessage(ClientID, "Ocorreu um erro!");
                                    SendClientMessage(p->OtherClientid, "Ocorreu um erro!");
								}
								else
								{
									// Copia o item que está no trade do outro usuário
									memcpy(&player->Inventory[SlotOID], &Trade[p->OtherClientid].Itens[i], sizeof st_Item);
									// Apaga o item do inventário do outro usuário
									memset(&mob->Inventory[Trade[p->OtherClientid].TradeItemSlot[i]], 0, sizeof st_Item);
									// Atualiza o slot do personagem em que o item foi apagado
									SendItem(p->OtherClientid, INVENTORY, Trade[p->OtherClientid].TradeItemSlot[i], &mob->Inventory[Trade[p->OtherClientid].TradeItemSlot[i]]);
									SendItem(ClientID, INVENTORY, SlotOID, &player->Inventory[SlotOID]);

									memset(&Trade[p->OtherClientid].Itens[i], 0, sizeof st_Item);
								}
                            }
                        }

                        CloseTrade(ClientID);
                    }
                } 
				else
                    // Se o outro usuário não confirmou ainda o trade, apenas é enviado para o outro usuário
                    // o botão de confirmação juntamente com os itens/gold do trade
                    SendAllTrade(ClientID, p->OtherClientid);
            }
        }
        else 
		{
            // Aqui o usuário apenas colocou os itens no slot
            if(!AddItensOnTrade(p))  // Aconteceu algum erro ao adicionar os itens ao trade
                CloseTrade(ClientID);
            else 
			{
                // Não aconteceu erro, então é setado tudo normalmente
                Trade[ClientID].Gold = p->Gold;
                Trade[ClientID].Confirm = false;
                Trade[Trade[ClientID].ClientID].Confirm = false;
                Trade[ClientID].Timer = clock();
                Trade[ClientID].Confirm = false;

                SendAllTrade(ClientID, p->OtherClientid);
            }
        }
    }

    ZeroMemory(m_PacketBuffer, 156);
}