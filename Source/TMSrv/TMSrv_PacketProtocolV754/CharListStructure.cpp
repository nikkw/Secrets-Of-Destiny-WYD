#include "DLLMain.h"

void UpdateCharListStructure(st_CharList* newCharList, BYTE *m_PacketBuffer)
{
	INT16 clientid;

	memcpy(&clientid, &m_PacketBuffer[6], 2);

	st_CharList* oldCharList = &Users[clientid].CharList;

	memcpy(oldCharList, newCharList, sizeof(st_CharList));
}