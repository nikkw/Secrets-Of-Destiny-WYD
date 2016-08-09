#include "SendTrade.h"

void FixSendTrade_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	p754_SendTrade *new_SendTrade = (p754_SendTrade*)m_PacketBuffer;
	p613_SendTrade *def_SendTrade = (p613_SendTrade*)packetBuffer;

	memset(&new_SendTrade->TradeItem[0], 0x0, sizeof(st_Item) * 15);
	memcpy(&new_SendTrade->TradeItem[0], &def_SendTrade->TradeItem[0], sizeof(st_Item) * 8);

	memset(&new_SendTrade->TradeItemSlot[0], 0xFF, 15);
	memcpy(&new_SendTrade->TradeItemSlot[0], &def_SendTrade->TradeItemSlot[0], 8);

	new_SendTrade->Unknow = 0x0;

	memcpy(&new_SendTrade->TradeInfo[0], &def_SendTrade->TradeInfo[0], 8);
}

void FixSendTrade_CLIENT(BYTE *packetBuffer)
{
	p754_SendTrade *new_SendTrade = (p754_SendTrade*)packetBuffer;
	p613_SendTrade *def_SendTrade = (p613_SendTrade*)packetBuffer;

	memcpy(&def_SendTrade->TradeItem[0], &new_SendTrade->TradeItem[0], sizeof(st_Item) * 8);

	memcpy(&def_SendTrade->TradeItemSlot[0], &new_SendTrade->TradeItemSlot[0], 8);

	memcpy(&def_SendTrade->TradeInfo[0], &new_SendTrade->TradeInfo[0], 8);
}