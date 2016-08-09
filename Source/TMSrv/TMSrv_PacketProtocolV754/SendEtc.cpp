#include "SendEtc.h"

void FixSendEtc_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	p754_SendEtc *new_SendEtc = (p754_SendEtc*)m_PacketBuffer;
	p613_SendEtc *def_SendEtc = (p613_SendEtc*)packetBuffer;

	memcpy(&new_SendEtc->Exp, &def_SendEtc->Exp, 20);
	memset(&new_SendEtc->Hold, 0x0, sizeof(new_SendEtc->Hold));
}