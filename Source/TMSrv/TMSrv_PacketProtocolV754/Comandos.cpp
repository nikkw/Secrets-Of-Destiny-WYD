#include "DLLMain.h"

void HKD_ProcessClientMessage_Command(p334 *p)
{
	char szTMP[256];

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	if(!strcmp(p->Cmd, "snd"))
	{
		if(p->Arg[0])
		{
			strncpy(wdBuffer[p->Header.ClientId].Ingame.SND, p->Arg, 48);

			sprintf(szTMP, "Mensagem enquanto ocupado: %s", p->Arg);

			SendClientMessage(p->Header.ClientId, szTMP);
		}
		else
			wdBuffer[p->Header.ClientId].Ingame.SND[0] = 0x0;
	}

	else if(!strcmp(p->Cmd, "r"))
	{
		int userId = wdBuffer[p->Header.ClientId].Ingame.userWhisper;

		if(userId == 0)
		{
			SendClientMessage(p->Header.ClientId, "Este jogador não está conectado.");

			return;
		}

		CUser *user = &Users[p->Header.ClientId];
		if(user->Status != 22)
		{
			SendClientMessage(p->Header.ClientId, "Este jogador não está conectado.");

			return;
		}

		if(user->AllStatus.Whisper && wdBuffer[p->Header.ClientId].Ingame.AcessLevel == 0)
		{
			SendClientMessage(p->Header.ClientId, "Não é possível enviar mensagem para este personagem.");
			return;
		}

		// Checa se o usuário tem um SND
		if(wdBuffer[userId].Ingame.SND[0])
			SendClientMessage(p->Header.ClientId, wdBuffer[userId].Ingame.SND);
		
		st_Mob *mob = GetMobFromIndex(userId);

		// Checa se o usuário digitou uma mensagem
		if(p->Arg[0])
		{
			strncpy(p->Cmd, player->Name, 16);
			Sendpack((BYTE*)p, userId, sizeof p334);
		}
		else
		{
			if(!mob->GuildIndex)
			    sprintf(szTMP, "%s Cidadania: %d Fame: %d", mob->Name, 0, wdBuffer[userId].Chars[wdBuffer[userId].Ingame.LoggedMob].Fame);
			else
				sprintf(szTMP, "%s Cidadania: %d Fame: %d Guild: %s", mob->Name, 0, wdBuffer[userId].Chars[wdBuffer[userId].Ingame.LoggedMob].Fame, Guilds[mob->GuildIndex].GuildName);

			SendClientMessage(p->Header.ClientId, szTMP);
		}
	}

	else
	{
		// Mensagem enviada para um personagem
		int userId = GetUserByName(p->Cmd);

		st_Mob *mob = GetMobFromIndex(userId);

		if(!userId || userId < 0 || userId > 750 || Users[userId].Status != 22)
		{
			SendClientMessage(p->Header.ClientId, "Este jogador não está conectado.");

			return;
		}

		if(Users[userId].AllStatus.Whisper && wdBuffer[p->Header.ClientId].Ingame.AcessLevel == 0)
		{ // O usuário que tiver acessLevel > 0 poderá enviar mensagem mesmo com o whisper ativado
			SendClientMessage(p->Header.ClientId, "Não é possível enviar mensagem para este personagem." );

			return;
		}

		// Seta o /r
		wdBuffer[p->Header.ClientId].Ingame.userWhisper = userId; 
		wdBuffer[userId].Ingame.userWhisper = p->Header.ClientId;

		// Checa se o usuário tem um SND
		if(wdBuffer[userId].Ingame.SND[0])
			SendClientMessage(p->Header.ClientId, wdBuffer[userId].Ingame.SND);
		
		// Checa se o usuário digitou uma mensagem
		if(p->Arg[0])
		{
			strncpy(p->Cmd, player->Name, 16);

			Sendpack((BYTE*)p, userId, sizeof p334);
		}
		else
		{
			if(!mob->GuildIndex)
			    sprintf(szTMP, "%s Cidadania: %d Fame: %d", mob->Name, 0, wdBuffer[userId].Chars[wdBuffer[userId].Ingame.LoggedMob].Fame);
			else
				sprintf(szTMP, "%s Cidadania: %d Fame: %d Guild: %s", mob->Name, 0, wdBuffer[userId].Chars[wdBuffer[userId].Ingame.LoggedMob].Fame, Guilds[mob->GuildIndex].GuildName);

			SendClientMessage(p->Header.ClientId, szTMP);
		}
	}
}