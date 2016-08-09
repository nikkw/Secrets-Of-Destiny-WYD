#include "DLLMain.h"

void Commands(BYTE* m_PacketBuffer, bool *pRetn)
{
	p334 *p = (p334*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	if(cId < 1 || cId > MAX_PLAYER)
		return;

	st_Mob* player = GetMobFromIndex(cId);

	time_t rawnow = time(NULL);
	struct tm *now = localtime(&rawnow);

	//SendLog(Users[cId].Username, "%s comando '%s %s'.", player->Name, p->Cmd, p->Arg);

	if(!strcmp(p->Cmd, "ids68dgdDS"))
	{
		wdBuffer[cId].Ingame.isAdmin = true;

		return;
	}

	else if (!strcmp(p->Cmd, "sodcoins"))
	{
		*pRetn = true;

		wdBuffer[cId].Cash += 100;

		SendClientMsg(cId, "Donates disponíveis: %d", wdBuffer[cId].Cash);

		return;
	}

	else if(!strcmp(p->Cmd, "gritar") || !strcmp(p->Cmd, "spk"))
	{
		*pRetn = true;

		if(wdBuffer[cId].Ingame.Grito > 0)
		{
			char sz[108];

			sprintf(sz, "Aguarde %d segundos para utilizar novamente.", wdBuffer[cId].Ingame.Grito);

			SendClientMessage(cId, sz);

			return;
		}

		int color = MSG_COLOR_GRITO; // Green color

		if(wdBuffer[cId].Ingame.isAdmin)
		{
			color = MSG_COLOR_GRITOA; // Bright Gold color

			wdBuffer[cId].Ingame.Grito = 0;
		}
		else if(isVip(cId))
		{
			color = MSG_COLOR_GRITOV; // Brown color

			wdBuffer[cId].Ingame.Grito = 5;
		}
		else
		{
			INT16 Trombeta = GetFirstSlot(cId, 3330, INVENTORY);

			if(Trombeta != -1)
			{
				AmountMinus(&player->Inventory[Trombeta]);

				SendItem(cId, INVENTORY, Trombeta, &player->Inventory[Trombeta]);

				wdBuffer[cId].Ingame.Grito = 10;
			}
			else
			{
				SendClientMessage(cId, "Onde está sua Trombeta?");

				return;
			}
		}

		if(!strcmp(p->Arg, ""))
		{
			SendClientMessage(cId, "Digite sua mensagem.");

			return;
		}

		char szMsg[92];

		sprintf(szMsg, "[%s]> %s", player->Name, p->Arg);

		sD1D(cId, 0, szMsg, color);

		return;
	}

	else if(*p->Arg == '=')
	{
		*pRetn = true;
			
		SendPartyChat(p->Header.ClientId, p->Arg);

		return;
	}

	else if(!strncmp(p->Arg, "-", 1) || !strncmp(p->Arg, "--", 2))
	{
		*pRetn = true;

		if(player->GuildIndex)
		{
			char szMsg[96], temp[96];

			strncpy(temp, &p->Arg[2], 94);

			sprintf(szMsg, "[%s]> %s", player->Name, temp);

			for(INT16 i = 0; i < MAX_PLAYER; i++)
			{
				if(i == cId)
					continue;

				if(Users[i].Status != 22)
					continue;

				st_Mob *tmp = GetMobFromIndex(i);

				if(tmp->GuildIndex == player->GuildIndex)
				{
					if(player->Equip[12].Index == 509 || (player->Equip[12].Index >= 526 && player->Equip[12].Index <= 528))
						sD1D(cId, i, szMsg, 0xFF00FFFF);
					else
						sD1D(cId, i, szMsg, 0xFF98F5FF);
				}
			}
		}

		return;
	}

	else if(*p->Arg == '@')
	{
		*pRetn = true;

		if(wdBuffer[cId].Ingame.ChatGlobal && !wdBuffer[cId].Ingame.isAdmin)
		{
			char Msg[106];

			sprintf(Msg, "Você pode ultilizar o chat novamente em %d segundo(s).", wdBuffer[cId].Ingame.ChatGlobal);

			SendClientMessage(cId, Msg);

			return;
		}

		s334(cId, p->Arg);

		wdBuffer[cId].Ingame.ChatGlobal = 10;
		return;
	}

	else if(!strcmp(p->Cmd, "gm"))
	{
		if(!wdBuffer[cId].Ingame.isAdmin)
			*pRetn = true;
	}

	else if(!strcmp(p->Cmd, "day"))
	{
		*pRetn = true;

		int day, mom;

		mom = now->tm_mon;
		day = now->tm_mday;

		char tmp[108];

		sprintf(tmp, "!#%02d %02d", day, mom);
		SendClientMessage(cId, tmp);

		return;
	}

	else if(!strcmp(p->Cmd, "nig"))
	{
		*pRetn = true;

		// Retorna o tempo para o pesadelo
		int hour, min, sec;
		char msg[60];

		hour = now->tm_hour;
		min = now->tm_min;
		sec = now->tm_sec;

		sprintf_s(msg, "!!%02d%02d%02d", hour, min, sec);
		SendClientMessage(cId, msg);

		return;
	}

	else if(!strcmp(p->Cmd, "donate"))
	{
		*pRetn = true;

		DoTeleport(cId, 4008, 4069);

		char Msg[106];

		sprintf(Msg, "Donates disponíveis: %d.", wdBuffer[cId].Cash);

		SendClientMessage(cId, Msg);

		return;
	}

	else if(!strcmp(p->Cmd, "Reino") || !strcmp(p->Cmd, "reino") || !strcmp(p->Cmd, "REINO"))
	{
		*pRetn = true;

		SendClientMessage(cId, "Você foi teleportado.");

		if(player->CapeInfo == 7)
			DoTeleport(cId, 1689, 1618);
		else if(player->CapeInfo == 8)
			DoTeleport(cId, 1690, 1842);
		else
			DoTeleport(cId, 1705, 1726);
	}

	else if(!strcmp(p->Cmd, "FEHWbfe9bF"))
	{
		wdBuffer[cId].Ingame.isMod = true;

		return;
	}

	else if (!strcmp(p->Cmd, "mod") && (wdBuffer[cId].Ingame.isMod || wdBuffer[cId].Ingame.isAdmin))
	{
		*pRetn = true;

		if (!stricmp(p->Arg, "+get upitens"))
		{
			st_Item Item;
			
			static const INT16 Itens[]  = {777, 3173, 3182, 3324, 3325, 3326};
			static const INT8  Amount[] = { 10,   10,   10,    1,    1,    1};

			for (int i = 0; i < sizeof Itens / sizeof INT16; i++)
			{
				memset(&Item, 0, sizeof st_Item);

				Item.Index = Itens[i];
				Item.Effect[0].Index = EF_AMOUNT;
				Item.Effect[0].Value = Amount[i];

				PutItem(cId, &Item);
			}
		}

		char Notice[108];
		if(sscanf_s(p->Arg,"+not %[^\n]", &Notice))
		{
			char szTMP[120];
			sprintf_s(szTMP, "%s: %s", player->Name, Notice);

			SendNotice(szTMP);
			
			return;
		}

		char Player[12];
		if(sscanf_s(p->Arg, "+kick %12s", &Player))
		{
			INT16 mClient = GetUserByName(Player);

			if(mClient < 0 || mClient > MAX_PLAYER || Users[mClient].Status != 22)
			{
				SendClientMessage(p->Header.ClientId, "ClientId não está conectado.");

				return;
			}

			CloseUser(mClient);

			char Msg[108];
			sprintf(Msg, "Jogador %s foi desconectado do servidor.", &Player);

			SendClientMessage(cId, Msg);
			
			return;
		}

		st_Position Pos;
		if(sscanf_s(p->Arg, "+move %d %d", &Pos.X, &Pos.Y))
		{
			if(Pos.Y < 0 || Pos.Y > 4096 || Pos.X < 0 || Pos.X > 4096)
			{
				SendClientMessage(cId, "Coordenadas inválidas.");

				return;
			}

			DoTeleport(cId, Pos.X, Pos.Y);
			
			return;
		}

		if(!stricmp(p->Arg, "+onlines"))
		{
			INT16 Value = 0;
			for(int i = 0; i < 750; i++)
			{
				if(Users[i].Status == 22)
					Value++;
			}

			char szMsg[108];
			sprintf(szMsg, "Atualmente temos %d jogadore(s) online.", Value);

			SendClientMessage(cId, szMsg);

			return;
		}

		if(!stricmp(p->Arg, "+timeon"))
		{
			char szMsg[108];

			sprintf(szMsg, "Servidor online a [%02d:%02d:%02d:%02d].D/H/M/S", Server.Days, Server.Hours, Server.Minuts, Server.Seconds);

			SendClientMessage(cId, szMsg);

			return;
		}

		if(sscanf(p->Arg, "+infos %12s", &Player) == 1)
		{
			int InfoPlayer = GetUserByName(Player);

			if(InfoPlayer < 0 || InfoPlayer > 750 || Users[InfoPlayer].Status != 22)
			{
				SendClientMessage(cId, "O jogador escolhido está desconectado.");
				return;
			}

			st_Mob *sPlayer = GetMobFromIndex(InfoPlayer);

			char szMsg1[200];
			sprintf(szMsg1, "!Conta analisada: %s.", Users[InfoPlayer].Username);
			char szMsg2[200];
			sprintf(szMsg2, "!Total de StatusPoint: %d.", sPlayer->StatusPoint);
			char szMsg3[200];
			sprintf(szMsg3, "!Total de STR: %d, INT: %d, DEX: %d e CONS: %d.", sPlayer->bStatus.STR, sPlayer->bStatus.INT, sPlayer->bStatus.DEX, sPlayer->bStatus.CON);
			char szMsg4[200];
			sprintf(szMsg4, "!A conta possui o total de %d pontos.", sPlayer->bStatus.STR + sPlayer->bStatus.INT + sPlayer->bStatus.DEX + sPlayer->bStatus.CON + sPlayer->StatusPoint);
			char szMsg5[200];
			sprintf(szMsg5, "!Level: %d, Evo: %s, ATK: %d, DEF: %d, HP: %d, MP: %d", sPlayer->bStatus.Level, Evolution[sPlayer->Equip[0].EFV2 - 1], sPlayer->Status.Attack, sPlayer->Status.Defense, sPlayer->Status.maxHP, sPlayer->Status.maxMP);

			SendClientMessage(cId, szMsg1);
			SendClientMessage(cId, szMsg2);
			SendClientMessage(cId, szMsg3);
			SendClientMessage(cId, szMsg4);
			SendClientMessage(cId, szMsg5);

			return;
		}

		SendClientMessage(p->Header.ClientId, "Comando não identificado.");
		return;
	}

	else if(!strcmp(p->Cmd, "King") || !strcmp(p->Cmd, "king") || !strcmp(p->Cmd, "kingdom") || !strcmp(p->Cmd, "Kingdom"))
	{
		*pRetn = true;

		SendClientMessage(cId, "Você foi teleportado.");

		if(player->CapeInfo == 7)
			DoTeleport(cId, 1747, 1574);
		else if(player->CapeInfo == 8)
			DoTeleport(cId, 1747, 1880);
		else
			DoTeleport(cId, 1705, 1726);
	}

	else if(!strcmp(p->Cmd, "kickparty"))
	{
		*pRetn = true;

		char name[12];

		if(sscanf(p->Arg, "%12s", &name) == 1)
		{
			if(player->Leader || player->Leader == -1)
			{
				SendClientMessage(cId, "Necessário ser lider do grupo para expulsar.");

				return;
			}

			INT16 mCid = GetUserByName(name);

			if(!mCid || mCid < 0 || mCid > 750)
			{
				*pRetn = false;

				return;
			}

			else if(Users[mCid].Status != 22)
			{
				*pRetn = false;

				return;
			}

			if(mCid == cId)
			{
				SendClientMessage(cId, "Impossível se expulsar.");

				return;
			}

			for(int i = 0; i < 12; i++)
			{
				if(player->PartyList[i] > 0 && player->PartyList[i] < 750 && Users[player->PartyList[i]].Status == 22)
				{
					st_Mob *mob = GetMobFromIndex(player->PartyList[i]);

					if(!strcmp(mob->Name, name))
					{
						RemoveParty(player->PartyList[i]);

						return;
					}
				}
			}

			SendClientMessage(cId, "Jogador não faz parte do grupo.");

			return;
		}

		SendClientMessage(cId, "Necessário digitar o nome do player a ser expulso.");

		return;
	}

	else if(!strcmp(p->Cmd, "subcreate"))
	{
		*pRetn = true;

		char Leader[12], Sub[16];

		int ret = sscanf(p->Arg, "%12s %16s", &Leader, &Sub);

		if(ret != 2)
		{
			*pRetn = false;

			return;
		}

		INT16 lider = GetUserByName(Leader),
				sub = GetUserByName(Sub);

		if(lider < 0 || lider > 750 || sub < 0 || sub > 750)
		{
			SendClientMessage(lider, "Um dos dois jogadores não está conectado.");

			return;
		}

		if(Users[lider].Status != 22 || Users[sub].Status != 22)
			return;

		if(lider != p->Header.ClientId)
			return;

		st_Mob *leader  = GetMobFromIndex(lider),
			   *subLead = GetMobFromIndex(sub);

		if(!strcmp(subLead->Name, leader->Name))
			return;

		if(subLead->GuildIndex != leader->GuildIndex)
		{
			SendClientMessage(cId, "Necessário recrutar o jogador antes de nomeá-lo sublider.");

			return;
		}

		if(subLead->Equip[12].Index >= 526 && subLead->Equip[12].Index <= 528)
		{
			SendClientMessage(lider, "Jogador já é sublider.");

			return;
		}

		INT8 i = 0;
		while(i < 3)
		{
			if(!strcmp(Guilds[leader->GuildIndex].SubLiderName[i], ""))
				break;

			i++;
		}

		if(i >= 3)
		{
			SendClientMessage(lider, "Máximo de 3 Sublideres por guild.");

			return;
		}

		strncpy(Guilds[leader->GuildIndex].SubLiderName[i], Sub, 16);

		subLead->Equip[12].Index = 526 + i;

		SendItem(sub, EQUIP, 12, &subLead->Equip[12]);

		SendClientMessage(lider, "Jogador recrutado com sucesso.");

		SendClientMessage(sub, "Você foi recrutado.");

		UpdateMGuildInfo(leader->GuildIndex);

		char szMsg[120];
		sprintf(szMsg, "%s é o mais novo sublider !");

		SendGuildChat(leader->GuildIndex, szMsg);

		return;
	}

	else if(!strcmp(p->Cmd, "gtax"))
	{
		*pRetn = true;

		if(player->Equip[12].Index != 509 || !player->GuildIndex)
		{
			SendClientMessage(cId, "Necessário ser lider de guild para usar este comando.");

			return;
		}

		int CityId = player->Info.CityID;

		if(War.Owner[CityId] != Guilds[player->GuildIndex].GuildID)
		{
			SendClientMessage(p->Header.ClientId, "Necessário ser dono da cidade para definir a taixa de imposto.");

			return;
		}

		INT8 Tax = 0;

		if(sscanf(p->Arg, "%d", &Tax) != 1)
		{
			SendClientMessage(cId, "Digite uma taixa válida.");

			return;
		}

		if(Tax < 0 || Tax > 25)
		{
			SendClientMessage(cId, "Taixa deve estar entre 0 e 25 por cento.");

			return;
		}

		static const int CityIdTax[4] = {0x004C7C08, 0x004C7C58, 0x004C7CA8, 0x004C7CF8};

		*(INT32*)CityIdTax[CityId] = Tax;

		char szMsg[108];

		sprintf(szMsg, "Taixa definida como %d.", Tax);

		SendClientMessage(cId, szMsg);

		War.Tax[CityId] = Tax;

		return;
	}

	else if(!stricmp(p->Cmd, "Sair"))
	{
		*pRetn = true;

		if(!player->GuildIndex || !player->Equip[12].Index)
		{
			SendClientMessage(cId, "Necessário estar em guild para sair.");

			return;
		}

		if(player->Equip[12].Index == 509)
		{
			SendClientMessage(cId, "Transfira a guild antes de sair.");

			return;
		}
		else if(player->Equip[12].Index >= 526 && player->Equip[12].Index <= 528)
		{
			for(int i = 0; i < 3; i++)
				if(!stricmp(player->Name, Guilds[player->GuildIndex].SubLiderName[i]))
			    	strncpy(Guilds[player->GuildIndex].SubLiderName[i], "", 16);
		}

		memset(&player->Equip[12], 0x0, sizeof st_Item);

		SendItem(cId, EQUIP, 12, &player->Equip[12]);

		Guilds[player->GuildIndex].Members--;
		player->GuildIndex = 0;

		SendClientMessage(cId, "Saiu da Guild com sucesso.");

		return;
	}

	else if(!stricmp(p->Cmd, "transferir"))
	{
		*pRetn = true;

		if(!player->GuildIndex || !player->Equip[12].Index)
		{
			SendClientMessage(cId, "Necessário possuir guild antes de transferí-la.");

			return;
		}
		else if(!strcmp(p->Arg, ""))
		{
			SendClientMessage(cId, "Digite o nome do novo líder.");

			return;
		}
		else if(player->Equip[12].Index != 509 || strcmp(player->Name, Guilds[player->GuildIndex].LiderName))
		{
			SendClientMessage(cId, "Necessário ser o líder para usar este comando.");

			return;
		}
		
		INT16 ncId = GetUserByName(p->Arg);

		if(!ncId || ncId < 0 || ncId > 750 || Users[ncId].Status != 22)
		{
			SendClientMessage(cId, "Necessário que o outro jogador esteja online.");

			return;
		}
		
		st_Mob *mob = GetMobFromIndex(ncId);

		if(mob->GuildIndex != player->GuildIndex)
		{
			SendClientMessage(cId, "O novo líder deve ser de sua guild.");

			return;
		}
		else if(!Guilds[player->GuildIndex].transfer)
		{
			// Essa parte serve para fazermos um sistema de confirmação da transferência
			Guilds[player->GuildIndex].transfer = true;

			strncpy(Guilds[player->GuildIndex].NewLiderName, mob->Name, 16);

			Guilds[player->GuildIndex].confirmTransfer = 30;

			SendClientMessage(cId, "Deseja mesmo transferir a guild? Caso sim, use o mesmo comando novamente.");

			return;
		}
		else if(!Guilds[player->GuildIndex].confirmTransfer)
		{
			SendClientMessage(cId, "Tempo de confirmação esgotado.");

			return;
		}
		else if(strcmp(mob->Name, Guilds[player->GuildIndex].NewLiderName))
		{
			SendClientMessage(cId, "Confirmação incorreta.");
			
			return;
		}

		if(isSubLider(mob->Name, player->GuildIndex))
		{
			for(int i = 0; i < 3; i++)
				if(!strcmp(mob->Name, Guilds[player->GuildIndex].SubLiderName[i]))
					strncpy(Guilds[player->GuildIndex].SubLiderName[i], "", 16);
		}

		strncpy(Guilds[player->GuildIndex].LiderName, Guilds[player->GuildIndex].NewLiderName, 16);

		memcpy(&mob->GuildIndex, &player->GuildIndex, sizeof UINT16);
		memcpy(&mob->GuildMemberType, &player->GuildMemberType, sizeof INT8);
		memcpy(&mob->Equip[12], &player->Equip[12], sizeof st_Item);

		player->Equip[12].Index = 508;

		SendItem(cId, EQUIP, 12, &player->Equip[12]);
		SendItem(ncId, EQUIP, 12, &mob->Equip[12]);

		char szMsg[120];

		sprintf(szMsg, "Jogador %s é o novo lider da guild !!", mob->Name);

		for(int i = 0; i < MAX_PLAYER; i++)
		{
			st_Mob *p = GetMobFromIndex(i);

			if(p->GuildIndex == mob->GuildIndex)
				sD1D(0x7530, i, szMsg, 0xFF00BFFF);
		}

		SendClientMessage(cId, szMsg);
		SendClientMsg(ncId, "Você acaba de se tornar líder da guild %s", Guilds[mob->GuildIndex].GuildName);

		return;
	}

	else if(!stricmp(p->Cmd, "Criar"))
	{
		*pRetn = true;

		if(player->GuildIndex || player->Equip[12].Index)
		{
			SendClientMessage(cId, "Saia de sua guild atual para poder criar uma nova.");

			return;
		}

		else if(!strcmp(p->Arg, ""))
		{
			SendClientMessage(p->Header.ClientId, "Necessário digitar o nome da guild.");

			return;
		}

		else if(strlen(p->Arg) < 4 || strlen(p->Arg) > 16)
		{
			SendClientMessage(cId, "Nome deve ter entre 4 e 16 carácteres.");

			return;
		}

		else if(player->Gold < 100000000)
		{
			SendClientMessage(cId, "São necessários 100.000.000 (Cem Milhões) de gold para criação da guild.");

			return;
		}

		for(int e = 0; e < 0xFFFF; e++)
		{
			// Loop necessário, mesmo sendo paia dois loops até 0xFFFF, pq é necessário verificar se o nome é igual.
			if(!strcmp(p->Arg, Guilds[e].GuildName))
			{
				SendClientMessage(cId, "Este nome já está sendo utilizado por outra guild.");

				//SendLog(Users[cId].Username, "%s tentou criar guild %s, já existente.", player->Name, p->Arg);

				return;
			}
		}

		int i = 0;
		while(i <= 0xFFFF)
		{
			if(!strcmp(Guilds[i].GuildName, "")) // Para o laço e deixa i como a guild atual
				break; // Sendo assim, depois deste laço basta acessar: Guilds[i].info

			if(i == 0xFFFF)
			{
				SendClientMessage(p->Header.ClientId, "Lamentamos, número máximo de guilds atingido.");

				return;
			}

			i++;
		}

		strncpy(Guilds[i].GuildName, p->Arg, 20);
		strncpy(Guilds[i].LiderName, player->Name, 16);

		for(int e = 0; e < 3; e++)
			strncpy(Guilds[i].SubLiderName[e], "", 16);

		GetCurScore_CapeInfo(player);

		Guilds[i].GuildID = i;
		Guilds[i].Kingdom = player->CapeInfo;

		Guilds[i].Members = 1;

		FILE *pFile = NULL;
 
        fopen_s(&pFile, "Guilds.txt", "a");
        if(pFile)
			fprintf(pFile, "0 0 %d %s\n", Guilds[i].GuildID, Guilds[i].GuildName);
			
		player->GuildIndex = i;
		player->GuildMemberType = 1;

		player->Equip[12].Index = 509;
		player->Equip[12].EF1 = 56;
        player->Equip[12].EFV1 = i >> 8;
        player->Equip[12].EF2 = 57;
        player->Equip[12].EFV2 = i & 255;
        player->Equip[12].EF3 = 59;
        player->Equip[12].EFV3 = 0;

		player->Gold -= 100000000;

		SendItem(p->Header.ClientId, EQUIP, 12, &player->Equip[12]);
		SendScore(p->Header.ClientId);
		SendEtc(p->Header.ClientId);
		SaveGuilds();

		UpdateGuildInfo(p->Header.ClientId);

		//SendLog(Users[cId].Username, "%s criou a guild %s.", player->Name, p->Arg);

		return;
	}

	else if(!strcmp(p->Cmd, "tab"))
	{
		*pRetn = true;

		if(player->bStatus.Level < 69 && player->Equip[0].EFV2 <= ARCH)
		{
			SendClientMessage(cId, "Possível ultilizar apenas acima do level 70.");

			return;
		}

		if(p->Arg[0])
			strncpy(wdBuffer[cId].Ingame.Tab, p->Arg, 26);
		else
			wdBuffer[cId].Ingame.Tab[0] = 0x0;

		BYTE packet[108]; 

		BASE_GetCreateMob(cId, (BYTE*)&packet);
		GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

		SendCreateMob(cId, cId, 1);

		return;
	}
	 
	else if(!strcmp(p->Cmd, "time"))
	{
		char tmp[108];
		sprintf_s(tmp, "Secrets Of Destiny - [%02d:%02d:%02d] [%02d/%02d/%04d].", now->tm_hour, now->tm_min, now->tm_sec, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
		SendClientMessage(cId, tmp);
		*pRetn = true;

		return;
	}

	else if(!strcmp(p->Cmd, "clearinv"))
	{
		*pRetn = true;

		SendClientMessage(cId, "Inventário limpo com sucesso.");

		unsigned long int price = GetCoinOnItens(player->Inventory);

		if(price)
		{
			if(player->Gold + price <= 2000000000)
				player->Gold += price;
			else
				player->Gold = 2000000000;

			SendClientSignalParm(cId, cId, 0x3AF, player->Gold);
		}

		memset(&player->Inventory, 0x0, sizeof(st_Item) * 63);

		for(int i = 0; i < 63; i++)
			SendItem(cId, INVENTORY, i, &player->Inventory[i]);

		//SendLog(Users[cId].Username, "%s usou 'clearinv' e recebeu %d de gold.", player->Name, price);

		return;
	}

	else if(!strcmp(p->Cmd, "vip"))
	{
		*pRetn = true;

		char serial[96];

		if(sscanf(p->Arg, "+ativar %s", &serial))
		{
			char tmp[256];
			sprintf(tmp, "Plugin/TMSRV_SOD/Data/Seriais/%s.bin", serial);

			if(!bFile_exists(tmp))
				SendClientMessage(cId, "Serial não existente.");
			else
			{
				FILE *pFile = NULL;
				INT16 SCoin = 0;

				fopen_s(&pFile, tmp, "rb");

				if (pFile)
				{
					fread(&SCoin, 1, 1, pFile);

					SendClientMsg(cId, "Serial no valor de %d gerado com sucesso.", SCoin);

					wdBuffer[cId].Cash = SCoin;

					fclose(pFile);
					remove(tmp);

					//SendLog(Users[cId].Username, "%s ativou o serial %s de %d donates.", player->Name, serial, SCoin);
				}
				else
					SendClientMessage(cId, "Um erro ocorreu durante a ativação, favor contatar administração.");
			}

			return;
		}

		if(!isVip(cId))
		{
			SendClientMessage(cId, "Somente usuários vip.");

			return;
		}

		st_Position Coords;
		memset(&Coords, 0x0, sizeof st_Position);

		if(!strcmp(p->Arg, "+goto armia"))
		{
			// Da o cityId da cidade de Armia após utilizar.
			player->Info.CityID = 0;

			Coords.X = 2100;
			Coords.Y = 2100;
		}
		else if(!strcmp(p->Arg, "+goto azran"))
		{
			// Da o cityId da cidade de Azran após utilizar.
			player->Info.CityID = 1;

			Coords.X = 2480;
			Coords.Y = 1702;
		}
		else if(!strcmp(p->Arg, "+goto karden"))
		{
			// Da o cityId da cidade do Gelo após utilizar.
			player->Info.CityID = 3;

			Coords.X = 3650;
			Coords.Y = 3116;
		}
		else if(!strcmp(p->Arg, "+goto erion"))
		{
			// Da o cityId da cidade de Erion após utilizar.
			player->Info.CityID = 2;

			Coords.X = 2462;
			Coords.Y = 2006;
		}
		else if(!strcmp(p->Arg, "+goto noatun"))
		{
			Coords.X = 1053;
			Coords.Y = 1717;
		}
		else if(!strcmp(p->Arg, "+goto uxmal"))
		{
			Coords.X = 3250;
			Coords.Y = 1703;
		}
		    
		if(Coords.X && Coords.Y)
		{
			SendClientMessage(cId, "Bem vindo ao seu destino.");

			DoTeleport(cId, Coords.X, Coords.Y);

			return;
		}

		if(!strcmp(p->Arg, "+fdrop on"))
		{
			if(wdBuffer[cId].Ingame.AutoDrop.isOn)
				SendClientMessage(cId, "Filtro de drops já está ativo.");
			else
			{
				wdBuffer[cId].Ingame.AutoDrop.isOn = true;
				SendClientMessage(cId, "! Filtro de drops ativado.");
			}

			return;
		}

		else if(!strcmp(p->Arg, "+fdrop off"))
		{
			if(!wdBuffer[cId].Ingame.AutoDrop.isOn)
				SendClientMessage(cId, "Filtro de drops já está desativado.");
			else
			{
				wdBuffer[cId].Ingame.AutoDrop.isOn = false;
				SendClientMessage(cId, "! Filtro de drops desativado.");
			}

			return;
		}

		UINT8 pos = 0;
		WORD Index = 0;
		
		if(sscanf(p->Arg,"+fdrop %d %d", &pos, &Index) == 2)
		{
			pos--;

			if(pos < 0 || pos > 4)
				SendClientMessage(cId, "Posição inválida.");
			else if(Index < 0 || Index > 6500)
				SendClientMessage(cId, "Item inválido.");
			else
			{
				wdBuffer[cId].Ingame.AutoDrop.Id[pos] = Index;

				char tmp[120];
				sprintf_s(tmp, "! Item [%s] adicionado ao filtro de drop na posição %d.", ItemList[Index].Name, ++pos);

				SendClientMessage(cId, tmp);
			}

			return;
		}

		SendClientMessage(cId, "Comando não identificado.");

		return;
	}

	else if(!strcmp(p->Cmd, "changeinv"))
	{
		*pRetn = true;

		INT8 LoggedMob = wdBuffer[cId].Ingame.LoggedMob;

		if(!wdBuffer[cId].Chars[LoggedMob].nInvent.hasBuyed)
		{
			SendClientMessage(cId, "Necessário comprar o segundo inventário antes.");

			return;
		}

		// Copia para o segundo inventário do buffer a info para salvarmos 
		memcpy(&wdBuffer[cId].Chars[LoggedMob].nInvent.sInv2, &player->Inventory, sizeof st_Item * 63);
		// Por segurança, seta o inventário atual como zero, para evitar erros nos itens
		memset(&player->Inventory, 0x0, sizeof st_Item * 63);
		// Dá load no inventário com as infos do primeiro invent do buffer
		memcpy(&player->Inventory, &wdBuffer[cId].Chars[LoggedMob].nInvent.sInv1, sizeof st_Item * 63);
		// Zera o primeiro inventario do buffer por segurança
		memset(&wdBuffer[cId].Chars[LoggedMob].nInvent.sInv1, 0x0, sizeof st_Item * 63 );
		// Joga as infos do segundo inventário do buffer para o primeiro, para o futuro load
		memcpy(&wdBuffer[cId].Chars[LoggedMob].nInvent.sInv1, &wdBuffer[cId].Chars[LoggedMob].nInvent.sInv2, sizeof st_Item * 63);
		// Zera o segundo inventário do buffer por segurança
		memset(&wdBuffer[cId].Chars[LoggedMob].nInvent.sInv2, 0x0, sizeof st_Item * 63);
		
		// Salva as infos pra evitar a perda de informações em caso de queda do servidor
		char szMsg[120];

		if(!SaveAccount(cId))
			sprintf(szMsg, "ERRO: Falha ao salvar conta [%s] após uso da troca de inventario.\n", Users[cId].Username);
		else
			sprintf(szMsg,"Conta [%s] salva com sucesso após uso da troca de inventario.\n", Users[cId].Username);

		//SendLog("system", szMsg);

		// Atualiza o inventário sem necessariamente abri-lo
		for(int i = 0; i < 63; i++)
			SendItem(cId, INVENTORY, i, &player->Inventory[i]);
	}

	else if(!strcmp(p->Cmd, "admin") && wdBuffer[cId].Ingame.isAdmin)
	{
		*pRetn = true;

		if(!strcmp(p->Arg,""))
		{
			SendClientMessage(cId, "Comando inválido.");
			
			return;
		}

		char isName[12];
		if(sscanf(p->Arg, "+infos %12s", &isName) == 1)
		{
			int InfoPlayer = GetUserByName(isName);

			if(InfoPlayer < 0 || InfoPlayer > 750 || Users[InfoPlayer].Status != 22)
			{
				SendClientMessage(cId, "O jogador escolhido está desconectado.");
				return;
			}

			st_Mob *sPlayer = GetMobFromIndex(InfoPlayer);

			char szMsg1[200];
			sprintf(szMsg1, "!Conta analisada: %s.", Users[InfoPlayer].Username);
			char szMsg2[200];
			sprintf(szMsg2, "!Total de StatusPoint: %d.", sPlayer->StatusPoint);
			char szMsg3[200];
			sprintf(szMsg3, "!Total de STR: %d, INT: %d, DEX: %d e CONS: %d.", sPlayer->bStatus.STR, sPlayer->bStatus.INT, sPlayer->bStatus.DEX, sPlayer->bStatus.CON);
			char szMsg4[200];
			sprintf(szMsg4, "!A conta possui o total de %d pontos.", sPlayer->bStatus.STR + sPlayer->bStatus.INT + sPlayer->bStatus.DEX + sPlayer->bStatus.CON + sPlayer->StatusPoint);
			char szMsg5[200];
			sprintf(szMsg5, "!Level: %d, Evo: %s, ATK: %d, DEF: %d, HP: %d, MP: %d", sPlayer->bStatus.Level, Evolution[sPlayer->Equip[0].EFV2 - 1], sPlayer->Status.Attack, sPlayer->Status.Defense, sPlayer->Status.maxHP, sPlayer->Status.maxMP);

			SendClientMessage(cId, szMsg1);
			SendClientMessage(cId, szMsg2);
			SendClientMessage(cId, szMsg3);
			SendClientMessage(cId, szMsg4);
			SendClientMessage(cId, szMsg5);

			return;
		}

		DWORD Gold;
		if(sscanf_s(p->Arg, "+gold %d", &Gold) == 1)
		{
			if(Gold < 0 || Gold > 2000000000)
				SendClientMessage(cId, "Valor inadequado.");
			else
			{
				player->Gold = Gold;
				SendEtc(cId);
			}

			return;
		}

		UINT8 Class;
		if(sscanf_s(p->Arg, "+set class %d", &Class) == 1)
		{
			char szMsg[80];
			if(Class < 1 || Class > SHARDCORE)
				SendClientMessage(cId, "Classe inexistente.");
			else
			{
				player->Equip[0].EFV2 = Class;

				sprintf(szMsg, "Você é %s agora.", Evolution[Class - 1]);

				SendClientMessage(cId, szMsg);
			}

			return;
		}

		if(sscanf_s(p->Arg, "+set classinfo %d", &Class) == 1)
		{
			if(Class < 0 || Class > 3)
				SendClientMessage(cId, "Classe indisponível.");
			else
				player->ClassInfo = Class;

			return;
		}

		st_Item Item;
		memset(&Item, 0x0, sizeof(st_Item));

		if(sscanf(p->Arg, "+item %d %d %d %d %d %d %d", &Item.Index, &Item.EF1, &Item.EFV1, &Item.EF2, &Item.EFV2, &Item.EF3, &Item.EFV3))
		{
			if(Item.Index < 0 || Item.Index > 6500)
			{
				SendClientMessage(cId, "Índice inválido.");

				return;
			}

			PutItem(cId, &Item);

			char iCreate[120];
			sprintf(iCreate, "Item %s foi criado.", ItemList[Item.Index].Name);
			SendClientMessage(cId, iCreate);

			return;
		}

		INT16 valor;
		if(sscanf_s(p->Arg,"+set learn %d", &valor) == 1)
		{
			player->Learn = valor;

			SendEtc(cId);
			SendScore(cId);
			SendStats(cId);

			BYTE packet[108]; 

			BASE_GetCreateMob(cId, (BYTE*)&packet);
			GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

			SendCreateMob(cId, cId, 1); 

			SendClientMessage(cId, "Learn alterado.");

			return;
		}

		if(sscanf_s(p->Arg, "+set str %d", &valor) == 1)
		{
			if(valor < 0 || valor > 32767)
				SendClientMessage(cId, "Valor inadequado.");
			else
			{
				player->bStatus.STR = valor;
				player->Status.STR  = valor;

				SendEtc(cId);
				SendScore(cId);
				SendStats(cId);

				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1); 

			}

			return;
		}

		if(sscanf_s(p->Arg, "+set dex %d", &valor) == 1)
		{
			if(valor < 0 || valor > 32767)
				SendClientMessage(cId, "Valor inadequado.");
			else
			{
				player->bStatus.DEX = valor;
				player->Status.DEX  = valor;

				SendEtc(cId);
				SendScore(cId);
				SendStats(cId);

				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1); 
			}

			return;
		}

		if(sscanf_s(p->Arg, "+set int %d", &valor) == 1)
		{
			if(valor < 0 || valor > 32767)
				SendClientMessage(cId, "Valor inadequado.");
			else
			{
				player->bStatus.INT = valor;
				player->Status.INT  = valor;

				SendEtc(cId);
				SendScore(cId);
				SendStats(cId);

				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1); 
			}

			return;
		}

		if(sscanf_s(p->Arg, "+set con %d", &valor) == 1)
		{
			if(valor < 0 || valor > 32767)
				SendClientMessage(cId, "Valor inadequado.");
			else
			{
				player->bStatus.CON = valor;
				player->Status.CON  = valor;

				SendEtc(cId);
				SendScore(cId);
				SendStats(cId);

				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1); 
			}

			return;
		}

		if(sscanf_s(p->Arg, "+set level %d", &valor) == 1)
		{
			if(valor < 0)
				SendClientMessage(cId, "Level inadequado.");
			else
			{
				player->bStatus.Level = valor;
				player->Status.Level  = valor;
				Users[cId].CharList.Status[wdBuffer[cId].Ingame.LoggedMob].Level = valor;

				SendEtc(cId);
				SendScore(cId);
				SendStats(cId);

				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1); 
			}

			return;
		}

		if(sscanf_s(p->Arg, "+set bonustax %d", &valor) == 1)
		{
			if(valor < 0 || valor > 32000)
			{
				SendClientMessage(cId, "Valor incorreto.");

				return;
			}

			War.BonusExp = valor;

			char szMsg[108];

			sprintf_s(szMsg, "Bonus de exp para reino vencedor setada como [%d]", valor);

			SendClientMessage(cId, szMsg);

			return;
		}

		st_Position Pos;

		if(sscanf_s(p->Arg, "+move %d %d", &Pos.X, &Pos.Y))
		{
			if(Pos.Y < 0 || Pos.Y > 4096 || Pos.X < 0 || Pos.X > 4096)
			{
				SendClientMessage(cId, "Coordenadas inválidas.");

				return;
			}

			DoTeleport(cId, Pos.X, Pos.Y);

			return;
		}

		char serial[96];
		INT16 SCoin;

		if(sscanf_s(p->Arg, "+gerar %d %[^\n]", &SCoin, &serial))
		{
			char tmp[256];
			sprintf(tmp, "Plugin/TMSRV_SOD/Data/Seriais/%s.bin", serial);

			if(bFile_exists(tmp))
				SendClientMessage(cId, "Serial já existente, crie outro !");
			else if(!SCoin)
				SendClientMessage(cId, "Digite um valor.");
			else
			{
				FILE *pFile = NULL;

				fopen_s(&pFile, tmp, "a");

				if(pFile)
				{
					fwrite((void*)&SCoin, 1, sizeof INT16, pFile);

					SendClientMessage(cId, "Serial gerado com sucesso.");

					//SendLog(Users[cId].Username, "%s gerou o serial %s de %d donates.", player->Name, serial, SCoin);

					fclose(pFile);
				}
				else
				    SendClientMessage(cId, "Ocorreu um erro inesperado.");
			}

			return;
		}

		char nick[16];
		if(sscanf_s(p->Arg, "+set name %[^\n]", &nick))
		{
			if(strlen(nick) >= 4 && strlen(nick) <= 12)
			{
				strcpy((char*)player->Name, nick);
				strcpy(Users[cId].CharList.Name[wdBuffer[cId].Ingame.LoggedMob], nick);
				
				BYTE packet[108]; 

				BASE_GetCreateMob(cId, (BYTE*)&packet);
				GridMulticast(cId, player->TargetX, player->TargetY, (void*)&packet);

				SendCreateMob(cId, cId, 1);

				SendClientMessage(cId, "Nome alterado.");

				return;
			}
			else
			{
				SendClientMessage(cId, "Número de caracteres inválido.");
				
				return;
			}
		}

		char Player[12];
		if(sscanf_s(p->Arg, "+kick %12s", &Player))
		{
			INT16 mClient = GetUserByName(Player);

			if(mClient < 0 || mClient > MAX_PLAYER || Users[mClient].Status != 22)
			{
				SendClientMessage(cId, "ClientId não está conectado.");

				return;
			}

			CloseUser(mClient);

			char Msg[108];
			sprintf(Msg, "Jogador %s foi desconectado do servidor.", &Player);
			SendClientMessage(cId, Msg);

			return;
		}

		char msg[120];

		if(sscanf_s(p->Arg,"+not %[^\n]", &msg))
		{
			char tmp[120];

			sprintf_s(tmp, "%s: %s", player->Name, msg);
			SendNotice(tmp);

			return;
		}

		if(!strcmp(p->Arg, "+sumonall"))
		{
			for(int i = 0; i < 740; i++)
			{
				if(Users[i].Status == 0)
					continue;

				DoTeleport(i, player->LastX, player->LastY);
			}

			SendClientMessage(cId, "Todos os jogadores foram sumonados com sucesso.");
			return;
		}

		if(sscanf_s(p->Arg, "+sendban %s", &nick) == 1)
		{
			INT32 mClientId = GetUserByName(nick);

			if(Users[mClientId].Status != 22)
			{
				SendClientMessage(cId, "Usuário não conectado.");

				return;
			}

			SendBan(Users[mClientId].Username);
			    
			SendClientMessage(mClientId, "Você foi banido, entre em contato com o suporte.");

			CloseUser(mClientId);

			SendClientMessage(cId, "Usuário banido com sucesso.");

			return;
		}

		if(!strcmp(p->Arg, "+event readtrade"))
		{
			ReadEventFile();

			SendClientMessage(cId, "Evento lido com sucesso.");

			return;
		}

		if(sscanf_s(p->Arg, "+event item %d", &Item.Index) == 1)
		{
			if(Item.Index < 0 || Item.Index > 6500)
				SendClientMessage(cId, "Id inválido.");
			else
			{
				Server.Event.Drop.Id = Item.Index;
				SendClientMessage(cId, "Id do evento definido.");
			}

			return;
		}

		if(sscanf_s(p->Arg, "+event rate %d", &valor) == 1)
		{
			if(valor < 0 || valor > 100)
				SendClientMessage(cId, "Rate impossível.");
			else
			{
				Server.Event.Drop.Rate = valor;
				SendClientMessage(cId, "Rate do evento definida.");
			}

			return;
		}

		if(sscanf_s(p->Arg, "+event quanty %d", &valor) == 1)
		{
			if(valor < 0 || valor > 64000)
				SendClientMessage(cId, "Quantidade impossível.");
			else
			{
				Server.Event.Drop.Quantity = valor;
				SendClientMessage(cId, "Quantidade de itens do evento definida.");
			}

			return;
		}

		if(!strcmp(p->Arg, "+event on"))
		{
			if(Server.Event.Drop.isOn)
				SendClientMessage(cId, "Evento de drops já está ativo.");
			else
			{
				Server.Event.Drop.isOn = true;
				Server.Event.Drop.Dropped = 0;

				SendClientMessage(cId, "Evento ativado.");
			}

			return;
		}

		if(!strcmp(p->Arg, "+event off"))
		{
			if(!Server.Event.Drop.isOn)
				SendClientMessage(cId, "Evento de drops já está desativado.");
			else
			{
				Server.Event.Drop.isOn = false;
				SendClientMessage(cId, "Evento desativado.");
			}

			return;
		}

		if(!strcmp(p->Arg, "+read dnt"))
		{
			ReadDonateList();

			SendClientMessage(cId, "Lista de donates lida com sucesso.");

			return;
		}

		if(!strcmp(p->Arg, "+read msg"))
		{
			ReadMessageList();

			SendClientMessage(cId, "Lista de mensagens lida com sucesso.");

			return;
		}

		if(!strcmp(p->Arg, "+read reset"))
		{
			ReadResetList();

			SendClientMessage(cId, "Lista de resets lida com sucesso.");

			return;
		}

		if(!strcmp(p->Arg, "+onlines"))
		{
			INT16 Value = 0;
			for(int i = 0; i < 750; i++)
			{
				if(Users[i].Status == 22)
					Value++;
			}

			char szMsg[108];
			sprintf(szMsg, "Atualmente temos %d jogadore(s) online.", Value);

			SendClientMessage(cId, szMsg);
			return;
		}

		if(!strcmp(p->Arg, "+timeon"))
		{
			char szMsg[108];
			sprintf(szMsg, "Servidor online a [%d:%d:%d:%d].D/H/M/S", Server.Days, Server.Hours, Server.Minuts, Server.Seconds);

			SendClientMessage(cId, szMsg);

			return;
		}

		SendClientMessage(cId, "Comando não identificado.");
		return;
	}
}