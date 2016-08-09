// ---
// by ptr0x
// ---

#ifndef __FIX_SEND_TRADE_H__
#define __FIX_SEND_TRADE_H__

#include "DLLMain.h"

#pragma region Packet Struct v613
typedef struct
{
	PacketHeader Header;

	st_Item TradeItem[8];
	BYTE TradeItemSlot[8];

	BYTE TradeInfo[8];
} p613_SendTrade;
#pragma endregion

#pragma region Packet Struct v754
typedef struct
{
	PacketHeader Header;

	st_Item TradeItem[15];
	BYTE TradeItemSlot[15];

	BYTE Unknow;

	BYTE TradeInfo[8];
} p754_SendTrade;
#pragma endregion

void FixSendTrade_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);
void FixSendTrade_CLIENT(BYTE *packetBuffer);

#endif // __FIX_SEND_TRADE_H__