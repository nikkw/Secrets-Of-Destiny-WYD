#include "DLLMain.h"

void Numerica(BYTE *m_PacketBuffer)
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

			player->Ingame.canLog = true;

			Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);

		}
		else
		{
			if(p->RequestChange == 1 && player->Ingame.canLog)
			{
				strncpy(player->Numerica, p->num, 6);

				Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);
			}
			else if(!strncmp(player->Numerica, p->num, 6))
			{
				Sendpack(m_PacketBuffer, p->Header.ClientId, sizeof pFDE);
				player->Ingame.canLog = true;
			}
			else
			{
				player->Ingame.IncorrectNumeric ++;

				if(player->Ingame.IncorrectNumeric > 3)
				{
					CloseUser_OL2(p->Header.ClientId);
					
					return;
				}

				Sendpack((BYTE*)&header, p->Header.ClientId, 12);
			}
		}
	}

	return;
}