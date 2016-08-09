#include "AddMessage.h"

static char tmp[1024];

int __stdcall HKD_AddMessage(int instModule, PacketHeader *oldPacketBuffer, int packetSize)
{
	int retnValue = 0;
	int clientId = GetUserFromSocket(*(WORD*)instModule);

	BYTE *newPacketBuffer = (BYTE*)malloc(packetSize);
	if(newPacketBuffer == NULL)					
		return 0;		
		
	memcpy(newPacketBuffer, oldPacketBuffer, packetSize);

	// Compara o size do pacote no header e passado por parametro
	if(*(WORD*)newPacketBuffer != (WORD)packetSize)
	{
		*(WORD*)newPacketBuffer = (WORD)packetSize;
	}

	// Faz as modificações necessárias no pacote
	bool clear = SendPacketControl(newPacketBuffer, oldPacketBuffer, clientId);
	if(clear)			
		memset(newPacketBuffer, 0x0, packetSize);

	// Chama a função original
	__asm
	{
		PUSH DWORD PTR SS:[packetSize]
		PUSH DWORD PTR SS:[newPacketBuffer]
		MOV ECX, instModule
		CALL _AddMessage

		MOV retnValue, EAX
	}

	free(newPacketBuffer);

	return retnValue;
}