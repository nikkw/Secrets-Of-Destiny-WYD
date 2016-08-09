#include "DLLMain.h"

void __stdcall HKD_ProcessDBMessage_LoadBuffs(INT32 clientid)
{
	memcpy(&mBuffer[clientid].Affects[0], &wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Affect[0], sizeof(stAffects) * 16);		

	GetCurrentScore(clientid);
	SendScore(clientid);			
	SendEtc(clientid);
}