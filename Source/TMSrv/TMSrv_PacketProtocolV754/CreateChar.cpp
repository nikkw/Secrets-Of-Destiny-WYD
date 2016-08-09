#include "DLLMain.h"

struct pC_CreateChar
{
	PacketHeader Header; // Offset 00
	int PosID; // Offset 12
	char NewCharName[16]; // Offset 16
	int ClassID; // Offset 32
};

#define NAMECOUNT 18

static char NameCantCreate[NAMECOUNT][16] = {
    "CARALHO", "PINTO", "PORRA", "BUCETA", "cuzao", "gritar", "criar", "sair", "donate", "reino", "kingdom", "king", "kickparty", 
	"gtax", "transferir", "clearinv", "changeinv", "admin"
};

void CreateChar(BYTE *m_PacketBuffer, bool *pRetn)
{
	pC_CreateChar *p = (pC_CreateChar*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	if(cId < 0 || cId > 750)
		return;
	else if(p->ClassID < 0 || p->ClassID > 3)
		return;
	else if(p->PosID < 0 || p->PosID > 3)
		return;

	if(Users[cId].Status == 22)
	{
		*pRetn = true;

		CloseUser(cId);

		//SendLog("system", "Packet CreateChar enviado de dentro do game pelo clientId %d.", cId);

		return;
	}

	for(int i = 0; i < NAMECOUNT; i++)
	{
		if(!stricmp(p->NewCharName, NameCantCreate[i]))
		{
			*pRetn = true;

			SendClientMsg(cId, "Nome %s não está disponível.", p->NewCharName);

			//SendLog("system", "%d tentou criar personagem com o nick %s", cId, p->NewCharName);

			return;
		}
	}
}