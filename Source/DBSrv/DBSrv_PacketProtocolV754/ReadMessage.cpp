#include "DLLMain.h"

BYTE *HKD_ReadMessage(BYTE *packetBuffer, DWORD packetSize)
{
	PacketHeader *Header = (PacketHeader*)packetBuffer;

	switch(Header->PacketId)
	{
		case 0x802:
			{
				CreateChar(packetBuffer);

				if(packetBuffer[32] > 4) 
				{
					packetBuffer[32] = 0;
				}
			}
			break;

		case 0x1C10:
			ZeroMemory(packetBuffer, Header->Size);
			break;
	}

	return packetBuffer;
}