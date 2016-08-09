#include "ExitParty.h"

void FixExitParty_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	PacketHeader *packetHeader = (PacketHeader*)packetBuffer;

	*(WORD*)&m_PacketBuffer[14] = packetHeader->ClientId;
	*(WORD*)&m_PacketBuffer[14] = 0x0;
}	


void FixExitParty_CLIENT(BYTE *packetBuffer)
{
	PacketHeader *packetHeader = (PacketHeader*)packetBuffer;

	*(WORD*)&packetBuffer[12] = packetHeader->ClientId;
}
	