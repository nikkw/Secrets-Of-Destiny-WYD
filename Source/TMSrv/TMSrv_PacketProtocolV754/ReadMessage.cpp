#include "ReadMessage.h"

static char tmp[1024];

BYTE* __stdcall HKD_ReadMessage(int instModule, int *unkParam1, int *unkParam2)
{
	BYTE* packetBuffer = NULL;
	int clientId = GetUserFromSocket(*(WORD*)instModule);

	// Chama função original
	__asm
	{
		PUSH DWORD PTR SS:[unkParam2]
		PUSH DWORD PTR SS:[unkParam1]
		MOV ECX, instModule

		CALL ReadMessage

		MOV packetBuffer, EAX
	}

	if(!packetBuffer)	
		return packetBuffer;		

	// Faz as modificações necessárias no pacote
	bool clear = RecvPacketControl((PacketHeader*)packetBuffer, clientId);
	if(clear)			
		memset(packetBuffer, 0x0, *(WORD*)packetBuffer);

	return packetBuffer;
}