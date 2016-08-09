// ---
// by ptr0x
// ---

#ifndef __DLL_MAIN_H__
#define __DLL_MAIN_H__

#include <Windows.h>
#include "PE_Patch.h"
#include "PE_DefConst.h"

BYTE *HKD_AddMessage(BYTE *packetBuffer, DWORD packetSize);
BYTE *HKD_ReadMessage(BYTE *packetBuffer, DWORD packetSize);
void CreateChar(BYTE *packetBuffer);
BYTE __stdcall CreateAccount(p20D *p, UINT32 addr);

typedef struct
{
	PacketHeader *Header;
	char Nome[16];
	int Face;
	int Class;
	int Slot;
}nArch;

#endif // __DLL_MAIN_H__