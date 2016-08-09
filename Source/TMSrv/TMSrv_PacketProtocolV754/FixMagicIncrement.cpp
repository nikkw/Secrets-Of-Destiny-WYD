#include "DLLMain.h"

INT32 GetIndexStruct(UINT32 pBase, UINT32 pStruct, size_t sizeStruct)
{
	if(!pBase || !pStruct || !sizeStruct)
		return -1;

	return ((pStruct - pBase) / sizeStruct);
}


int MobPointer(int type, int clientId)
{
	// Tem algo de errado aqui nesta func
	// Interpretar o que ela faz e depois arrumar
    if(clientId < 0 || clientId > 750)
        return 0;
    
    return wdBuffer[clientId].Ingame.MagicIncrement;
}

int HKD_ChangeMagicIncrement(st_Mob *mob)
{
	int clientId = GetIndexStruct(0x15C69B8, (UINT32)mob, 0x410);
	if(clientId < 0 || clientId > 750)
		return 0;

	return wdBuffer[clientId].Ingame.MagicIncrement;
}