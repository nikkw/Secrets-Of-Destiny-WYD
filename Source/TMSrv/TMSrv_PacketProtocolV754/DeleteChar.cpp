#include "DLLMain.h"

void DeleteChar(BYTE* m_PacketBuffer, bool *pRetn)
{
	REQDELETECHAR *p = (REQDELETECHAR*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > 1000)
	{
		//SendLog("system", "Packet Delete Person inválido recebido.");

		return;
	}

	wdBase Buffer;

	memset(&Buffer, 0x0, sizeof wdBase);
	memcpy(&wdBuffer[p->Header.ClientId].Chars[p->SlotIndex], &Buffer.Chars[0], sizeof(Buffer.Chars[0]));
}