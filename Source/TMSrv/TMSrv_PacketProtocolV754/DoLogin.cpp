#include "DLLMain.h"

void DoLogin(BYTE *m_PacketBuffer, bool *pRetn)
{
	FILE *pFile = NULL;

	p20D *p = (p20D*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	// Evita que se faça login em conta banida
	for(int i = 0 ; i < 16; i++)
		if(p->Login[i] == ' ')
			p->Login[i] = 0x0;

	if(!p->Login[0])
		*pRetn = true;	

	else if(cId > MAX_PLAYER || cId < 0)
	{
		SendClientMessage(cId, "Servidor cheio no momento. Tente novamente mais tarde");

		*pRetn = true;

		//SendLog(p->Login, "Não pode acessar por conta de limite de conexões.");

		return;
	}

	else if(p->Version != CLIVER)
	{
		*pRetn = true;

		SendClientMessage(cId, "Execute o Launcher ou visite o site para baixar as novas atualizações.");

		//SendLog(p->Login, "Tentou fazer login com o cliver %d.", p->Version);

		return;
	}
				
	else if(CheckBan(p->Login))
	{
		*pRetn = true;

		SendClientMessage(cId, "Conta desativada, entre em contato com o suporte.");

		//SendLog(p->Login, "Tentou fazer login enquanto banido.");

		return;
	}

	memset(&wdBuffer[cId], 0, sizeof wdBase);

	char szTMP[1024];	

	sprintf_s(szTMP, "Plugin/TMSRV_SOD/Data/%s.bin", p->Login);

	fopen_s(&pFile, szTMP, "rb");

	if(pFile)
	{
		int mobSize = sizeof wdBase - (sizeof wdBuffer[0].Ingame);
		
		fread(&wdBuffer[cId], 1, mobSize, pFile);

		fclose(pFile);
	}
	else
		return;

	wdBuffer[cId].Ingame.isMod = false;	
	wdBuffer[cId].Ingame.isAdmin = false;	
	wdBuffer[cId].Ingame.canLog  = false;

	//SendLog(p->Login, "Fez login no servidor.");
}