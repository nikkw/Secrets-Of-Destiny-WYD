#include "GetCreateMobTrade.h"

void FixGetCreateMobTrade_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	memset(&m_PacketBuffer[66], 0x0, 34);
	memcpy(&m_PacketBuffer[100], &packetBuffer[76], 28);

	memcpy(&m_PacketBuffer[172], &packetBuffer[106], 26);	
}