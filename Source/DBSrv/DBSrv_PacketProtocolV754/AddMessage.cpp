#include "DLLMain.h"

BYTE *HKD_AddMessage(BYTE *packetBuffer, DWORD packetSize)
{
	PacketHeader *Header = (PacketHeader*)packetBuffer;

	return packetBuffer;
}