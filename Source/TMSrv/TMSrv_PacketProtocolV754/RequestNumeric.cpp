#include "DLLMain.h"

void RequestNumeric(BYTE *m_PacketBuffer, bool *pRetn)
{
	__try
	{
		pFDE *p = (pFDE*)m_PacketBuffer;

	wdBase *player = &wdBuffer[p->Header.ClientId];

	PacketHeader header;
	memset(&header, 0, sizeof header);

	header.Size = 12;
	header.ClientId = 0x0;
	header.PacketId = 0xFDF;

	if(!player->Ingame.canLog || p->RequestChange == 1)
	{
		if(!player->Numerica[0])
		{
			strncpy(player->Numerica, p->num, 6);

			char szMsg[256];
			sprintf(szMsg, "Account [%s] definiu sua senha [%s]. IP: [%s]", Users[p->Header.ClientId].Username, player->Numerica, inet_n2a(Users[p->Header.ClientId].In_Addr));
			SaveLog(szMsg, "Server.txt");

			player->Ingame.canLog = true;

			Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);
		}
		else
		{
			if(p->RequestChange == 1 && player->Ingame.canLog)
			{
				strncpy(player->Numerica, p->num, 6);

				char szMsg[256];
				sprintf(szMsg, "Account [%s] mudou sua senha [%s]. IP: [%s]", Users[p->Header.ClientId].Username, player->Numerica, inet_n2a(Users[p->Header.ClientId].In_Addr));
				SaveLog(szMsg, "Server.txt");

				Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);
			}
			else if(!strncmp(player->Numerica, p->num, 6))
			{
				Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);

				player->Ingame.canLog = true;
			}
			else
			{
				Sendpack((BYTE*)&header, p->Header.ClientId, 12);
			}
		}
	}
	return;
}
	__except(1)
	{
	}
}

