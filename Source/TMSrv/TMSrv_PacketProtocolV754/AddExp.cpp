#include "AddExp.h"

void FixSendExp_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	*(DWORD*)&m_PacketBuffer[20] =*(DWORD*)&packetBuffer[16];

	*(DWORD*)&m_PacketBuffer[16] =*(DWORD*)&packetBuffer[12];
	
	*(DWORD*)&m_PacketBuffer[12] = 0x0;
}