#include "DLLMain.h"

void FixAddPoint_CLIENT(BYTE *m_PacketBuffer, bool *pRetn)
{
	p277 *p = (p277*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > MAX_PLAYER)
		return;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);	

	switch(p->Mode)
	{
		case 0:
		{
			if(player->StatusPoint > 200)
			{
				if(!p->Info)
				{
					if((player->Status.STR + 100) <= 32000)
					{
						player->bStatus.STR += 99;
						player->StatusPoint -= 99;
					}
					else if(player->Status.STR + 1 <= 32000)
						return;
					else
					{
						*pRetn = true;
						return;
					}
				}
				else if(p->Info == 1)
				{
					if((player->Status.INT + 100) <= 32000)
					{
						player->bStatus.INT += 99;
						player->StatusPoint -= 99;
					}
					else if(player->Status.INT + 1 <= 32000)
						return;
					else
					{
						*pRetn = true;
						return;
					}
				}
				else if(p->Info == 2)
				{
					if((player->Status.DEX + 100) <= 32000)
					{
						player->bStatus.DEX += 99;
						player->StatusPoint -= 99;
					}
					else if(player->Status.DEX + 1 <= 32000)
						return;
					else
					{
						*pRetn = true;
						return;
					}
				}
				else if(p->Info == 3)
				{
					if((player->Status.CON + 100) <= 32000)
					{
						player->bStatus.CON += 99;
						player->StatusPoint -= 99;
					}
					else if(player->Status.CON + 1 <= 32000)
						return;
					else
					{
						*pRetn = true;
						return;
					}
				}

				BASE_GetHpMp(player);
			}
		}
		break;
		case 2:
		{
			int skillID = (p->Info - 5000) % 24,
			    skillDiv = ((p->Info - 5000) % 24 / 8) + 1;

			if((skillID % 24) % 8 == 7)
			{
				for(int i = 1;i<8;i++)
				{
					int Have = player->Learn & (1 << (skillID - i));

					if(Have == 0)
					{
						SendClientMessage(p->Header.ClientId, "Necessário todas as skills da linhagem.");
						//SendLog(Users[p->Header.ClientId].Username, " %s tentou adquirir oitava sem ter todas as skills.", player->Name);

						*pRetn = true;

						return;
					}
				}

				for(int i = 1;i<4;i++)
				{
					if(i == skillDiv)
						continue;

					int Have = player->Learn & (1 << ((i * 8) - 1));
					if(Have != 0)
					{
						SendClientMessage(p->Header.ClientId, "Só é possível obter uma oitava skill por personagem.");
						//SendLog(Users[p->Header.ClientId].Username, "%s tentou obter uma segunda oitava skill.", player->Name);

						*pRetn = true;

						return;
					}
				}
				if(player->Gold < 50000000)
				{
					SendClientMessage(p->Header.ClientId, "São necessários 50 Milhões(50.000.000) de gold.");
					//(Users[p->Header.ClientId].Username, "%s tentou obter uma oitava skill sem gold suficiente.", player->Name);

					*pRetn = true;
					
					return;
				}
			}
			
			// Já possui a skill
			if(!(player->Learn & (1 << skillID)))
				return;

			// Não possui a skill e possui todas as funções passaram, então, retira o gold
			// TODO : Falta verificação de level + mastery
			if((skillID % 24) % 8 == 7)
				player->Gold -= 50000000;

			SendEtc(p->Header.ClientId);
			SendScore(p->Header.ClientId);
			//SendLog(Users[p->Header.ClientId].Username, "%s obteve oitava skill.", player->Name);
		}

		break;
	}
}