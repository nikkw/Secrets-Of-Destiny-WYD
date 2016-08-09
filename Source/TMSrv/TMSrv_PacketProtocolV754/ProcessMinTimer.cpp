#include "DLLMain.h"

int usersCount = 0,
    countMinTimer,
	msgCount;

void WINAPI MainThread()
{
	while(1)
	{
		// Thread Principal da dll, chamada de 1 em 1 segundo. 
		// Usar para não sobrecarregar a ProcessMinTimer
		// Não cometer a negragem de dar break

		time_t rawnow = time(NULL);
		struct tm *now = localtime(&rawnow);

		if((DayOfWeek() == Terça  || DayOfWeek() == Quinta) && now->tm_hour == 21)
		{
			if(!now->tm_min && !now->tm_sec)
			{
				SendNotice("Entrada na GuildWar liberada, boa sorte !");

				//SendLog("system", "Entrada na GuildWar liberada.");

				for(int i = 0; i < 0xFFFF; i++)
					Guilds[i].WarPoints = 0;
			}

			if(now->tm_min == 30 && !now->tm_sec)
			{
				UINT16 Winner = DefineGuildWinner();

				char szMsg[120];

				if(Winner)
				{
					sprintf(szMsg, "Guild %s foi a vencedora da GuildWar, parabéns!", Guilds[Winner].GuildName);
					
					Guilds[Winner].FAME += 1000;
				}
				else
					sprintf(szMsg, "Não houve vencedores na GuildWar.");

				SendNotice(szMsg);
				//SendLog("system", szMsg);
			}
		}

		DecrementWaterTime();
		LettersTime();

		for(int z = 0; z < 0xFFFF; z++)
		{
			if(Guilds[z].confirmTransfer)
				Guilds[z].confirmTransfer--;
			if(!Guilds[z].confirmTransfer)
			{
				Guilds[z].transfer = false;

				strncpy(Guilds[z].NewLiderName, "", 16);
			}
		}

		if(!now->tm_hour && !now->tm_min && !now->tm_sec)// 0:00:00
		{
			if(DayOfWeek() == Sabado)
			{
				*(INT32*)0x008BF1814 = 1;
				SendNotice("++++ DOUBLE EXP ON ++++");
			}
			else if(DayOfWeek() == Segunda)
			{
				*(INT32*)0x008BF1814 = 0;
				SendNotice("++++ DOUBLE EXP OFF ++++");
			}
		}

		if(!now->tm_sec && (now->tm_min == 1 || now->tm_min == 16 || now->tm_min == 31 || now->tm_min == 46))
		{
			for(INT8 i = 0; i < 3; i++)
			{
				Pesa[i].TimeLeft = 840;

				for(INT8 e = 0; e < 3; e++)
				{
					for(INT8 j = 0; j < 13; j++)
					{
						if(Pesa[i].CIDS[e][j] < 0 || Pesa[i].CIDS[e][j] > 750)
							continue;
						else if(Users[Pesa[i].CIDS[e][j]].Status != 22)
							continue;

						SendClientSignalParm(Pesa[i].CIDS[e][j], 0x7530, 0x3A1, Pesa[i].TimeLeft);
					}
				}
			}
		}

		if((now->tm_min == 14 || now->tm_min == 29 || now->tm_min == 44 || now->tm_min == 59) && now->tm_sec == 59)
		{
			ClearArea(1150, 130, 1270, 220); // Pesa A
			ClearArea(1050, 260, 1135, 350); // Pesa M
			ClearArea(1295, 290, 1325, 365); // Pesa N

			for(int i = 0; i < sizeof(QuestList) / sizeof(Quests); i++)
			{
				ClearArea(MaxMinCoordsQuest[i][0], MaxMinCoordsQuest[i][1], MaxMinCoordsQuest[i][2], MaxMinCoordsQuest[i][3]);

				for(int z = 0; z < 40; z++)
					QuestList[i].CidID[z] = 0;
			}

			for(int i = 0; i < sizeof(Pesa) / sizeof(Pesas); i++)
			{
				Pesa[i].Status = false;
				Pesa[i].Groups = 0;
				Pesa[i].NpcsAlive = 0;

				for(int e = 0; e < 13; e++)
				{
					Pesa[i].CIDS[0][e] = 0;
					Pesa[i].CIDS[1][e] = 0;
					Pesa[i].CIDS[2][e] = 0;
				}
			}
		}

		if(!now->tm_sec && !now->tm_min && now->tm_hour == 21 && DayOfWeek() == Domingo)
		{
			INT64 BetValue[4][2];

			for(UINT32 I = 0; I < 0xFFFF; I++)
			{
				// Se não tiver nome, não é uma  guild ativa.
				if(!strcmp(Guilds[I].GuildName, ""))
					continue;

				// Coloca na struct da guerra os valores referentes a guilds apostantes
				for(int e = 0; e < 4; e++)
				{
					if(Guilds[I].BetValue[e] > BetValue[e][0])
					{
						BetValue[e][0] = Guilds[I].BetValue[e];
						War.BetIndex[e][0] = I;
					}
					else if(Guilds[I].BetValue[e] > BetValue[e][1])
					{
						BetValue[e][1] = Guilds[I].BetValue[e];
						War.BetIndex[e][1] = I;
					}

					Guilds[I].BetValue[e] = 0;
				}
			}

		    TeleportWar();
		}
		else if(now->tm_hour == 21 && DayOfWeek() == Domingo && now->tm_min == 3 && !now->tm_sec)
		{
			// Inicio real da pancadaria
			//SendLog("system", "Portões da Guerra abertos.");

			WarGate(1);
		}

		if(now->tm_hour == 21 && DayOfWeek() == Domingo)
		{
			for(int i = 0; i < 4; i++)
			{
				if(!War.Iniciada[i])
					continue;

				int OwnerAlive = GetTeamAlive(i, 0),
					DefyAlive  = GetTeamAlive(i, 1);

				if(!OwnerAlive)// Seta o desafiante como vencedor
					PutAsWinner(i, 1);
				else if(!DefyAlive)// Seta o defensor como vencedor
					PutAsWinner(i, 0);

				if(War.Finalizada[i])
					continue;

				for(int e = 0; e < 2; e++)
				{
					for(int j = 0; j < War.TeamCount[i][e]; j++)
					{
						INT16 cId = 0;

						if(!e)
							cId = War.OwnerTeam[i][j];
						else
							cId = War.DefyTeam[i][j];

						st_Mob *player = GetMobFromIndex(cId);

						if(player->Status.curHP <= 0)
						{
							if(wdBuffer[cId].Ingame.WarRestTime >= 1)
								wdBuffer[cId].Ingame.WarRestTime--;
							else
								wdBuffer[cId].Ingame.cantRessurect = false;
						}

						// Manda o score, não sei se vai funfar...
						NpcsAlive(cId, GetTeamAlive(i, 0), GetTeamAlive(i, 1));
					}
				}
			}
		}

		usersCount = 0;

		for(int i = 0; i < MAX_PLAYER; i++)
		{
			if(Users[i].Status != 22)
				continue;

			usersCount++;

			if(wdBuffer[i].Ingame.ChatGlobal > 0)
				wdBuffer[i].Ingame.ChatGlobal--;
			if(wdBuffer[i].Ingame.hasFailed > 0)
				wdBuffer[i].Ingame.hasFailed--;
			if(wdBuffer[i].Ingame.Grito > 0)
				wdBuffer[i].Ingame.Grito--;
			if(wdBuffer[i].Ingame.RetectItem)
				wdBuffer[i].Ingame.RetectItem--;

			st_Mob *tmpPlayer = GetMobFromIndex(i);

			if(tmpPlayer->Equip[0].EFV2 < HARDCORE && tmpPlayer->Equip[1].Index == 3505 && !wdBuffer[i].Ingame.isAdmin)
			{
				SendBan(Users[i].Username);

				char szNotice[120];

				sprintf(szNotice, "Jogador [%s] banido por uso de item irregular.", tmpPlayer->Name);

				//SendLog("banneds", szNotice);
				//SendNotice(szNotice);

				CloseUser(i);
			}

			for(int i = 0; i < *(DWORD*)(0x004C7BD8); i++) 
				memset((void*)(0x8B9E778), 0, 8);

			VerifyPesa(i);
			VerifyQuests(i);
			//VerifyWarArea(i);
		}

		Server.Seconds++;

		if(Server.Seconds >= 60)
		{
			Server.Seconds -= 60;
			Server.Minuts++;

			if(Server.Minuts >= 60)
			{
				Server.Minuts -= 60;
				Server.Hours++;

				if(Server.Hours >= 24)
				{
					Server.Days++;
					Server.Hours -= 24;
				}
			}
		}

		char szTitle[120];

		if(usersCount)
			sprintf(szTitle, "Secrets of Destiny [%d] Jogadores conectados. [%02d:%02d:%02d:%02d]", usersCount, Server.Days, Server.Hours, Server.Minuts, Server.Seconds);
		else
			sprintf(szTitle, "Secrets of Destiny [%02d:%02d:%02d:%02d]", Server.Days, Server.Hours, Server.Minuts, Server.Seconds);

		SetConsoleTitle(szTitle);

		if(!now->tm_min && !now->tm_sec)
		{
			// Funções executadas todo inicio de hora
			if(!Server.SombraNegra)
			{
				CreateMob("Sombra_Negra", 3819, 2880, "npc");

				Server.SombraNegra = TRUE;

				SendNotice("Sombra Negra acaba de nascer em Karden!");

				//SendLog("system", "Sombra Negra nasceu.");
			}
			else
				SendNotice("Sombra Negra ainda reina em Karden.");
			
			StartThread(PremiumDelivery);
		}

		Sleep(1000);
		// Não colocarei 1000 para termos margem de tempo
		// Para a execução das tarefas desta thread
	}	
}

void Server_ProcessMinTimer()
{
	__try
	{
		time_t rawnow = time(NULL);
		struct tm *now = localtime(&rawnow);

		if(!(countMinTimer % 5))
		    SaveGuilds();

		for(int e = 0; e < 750; e++)
		{
			if(Users[e].Status != 22)
				continue;

			HKD_SaveUser(e, true);

			st_Mob *player = GetMobFromIndex(e);

			TimeLimitCheck(&player->Equip[13], e, !(countMinTimer % 5), player->Name);
			TimeLimitCheck(&player->Equip[14], e, false, player->Name);
		}

		int i = 0;
		while(ResetList[i].Time)
		{
			if(!(countMinTimer % (ResetList[i].Time * 5)))
			{
				if(ResetList[i].MinLevel > 0)
					ClearAreaLevel(ResetList[i].MinCoords.X, ResetList[i].MinCoords.Y, ResetList[i].MaxCoords.X,
								   ResetList[i].MaxCoords.Y, ResetList[i].MinLevel, ResetList[i].MaxLevel);
				else
					ClearArea(ResetList[i].MinCoords.X, ResetList[i].MinCoords.Y, ResetList[i].MaxCoords.X, ResetList[i].MaxCoords.Y);
			}

			i++;
		}

		i = 0;

		while(MessageList[i].Time)
		{
			if(!(countMinTimer % (MessageList[i].Time * 5)))
			{
				char szMsg[120];

				sprintf(szMsg, "[Aviso] %s", MessageList[i].Msg);

				sD1D(0x7530, 0, szMsg, MSG_COLOR_NOTICE);
			}

			i++;
		}

		if(countMinTimer > 0xFFFFFF)
			countMinTimer = 0;

		countMinTimer ++;
		ProcessMinTimer();
		// Esta função é chamada a cada 12 segundos
		// Por isto nos baseamos no resto da divisão do valor de countMinTimer por 5
		// Sempre que o valor % 5 for igual a 0 terá se passado um minuto
		// Não mexer nas duas linhas acima.
	}
	__except(TRUE)
	{
	}
}

/*
# Define intervalos de tempo para tirar os players de determinadas
# áreas (quadrado poligonal)

# <TimeInterval>,<X_Min>,<Y_Min>,<X_Max>,<Y_Max>,<Lvl_Min>,<Lvl_Max>

# Cemiterio:
10,2379,2077,2426,2133,0,0

# Jardim:
10,2227,1699,2258,1729,0,0

# Kaizen:
10,458,3886,496,3917,0,0

# Hydra:
10,655,3728,706,3765,0,0

# Infelicidade:
10,1313,4030,1353,4058,0,0

# Vingança:
60,1948,1585,1990,1616,0,0

# Emblema do Aprendiz:
10,2232,1564,2262,1591,0,0

# Emblema do Reino:
10,1715,1711,1750,1740,0,0

# Quest Molar:
10,791,4044,829,4081,0,0

# Quest ResetSkill:
10,2638,1966,2670,2004,0,0

# Quest Lan N:
10,3604,3601,3690,3690,0,0

# Quest Lan M:
10,3734,3476,3818,3561,0,0

# Quest Lan A:
10,3860,3602,3946,3690,0,0

# Quest Imp:
10,2224,1168,2261,1204,0,0

# Cubo N Boss:
1,1846,3897,1860,3911,0,0

# Cubo M Boss:
2,1760,4067,1778,4085,0,0

# Cubo A Boss:
2,1929,4022,1947,4040,0,0

# Quest Arch:
20,1308,1440,1391,1523,0,0

# Quest Morcegos Assassinos:
20,2529,3921,2541,3945,0,0

# Quest Gold:
10,3348,1416,3439,1472,0,399

# Quest Secreta Noatum:
10,3334,1285,3451,1402,0,0

*/