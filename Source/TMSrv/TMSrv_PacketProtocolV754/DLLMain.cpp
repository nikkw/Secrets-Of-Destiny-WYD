/*
 * Esta dll é protegida pelas leis internacionais de software
 * e pela lei de Deus.
 * 
 * Afinal de contas, só Deus sabe como essa merda funciona...
 * Não apagar nada no projeto.
 *
 * Secrets Of Destiny Team - ErickMota, Guerra.
 * Todos os direitos reservados
 */

#include "DLLMain.h"

GuildInfos     Guilds[0xFFFF];
Aguas          Agua[3];
Pesas          Pesa[3];
Quests         QuestList[5];
Donate         DonateList[300];
Resets         ResetList[50];
Messages       MessageList[50];
WarInfos       War;
CUser          Users[1000];
wdBase         wdBuffer[750];
stBuffer       mBuffer[30000];
st_TransBonus  TransBonus[5];
stMOBGener     Genner[10000];
stMOB754       MobArch;
st_ItemListCSV ItemList[6500];
st_MountData   MountBuffer[50];
st_Trade       Trade[1000];
ServerInfos    Server;
CartasQuest    Carta;
FILE *pLogFile;

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
    switch (catchReason)
    {
        case DLL_PROCESS_ATTACH:
		{			
			setlocale(LC_ALL, "Portuguese");
			DoIndirections();
			SetDefaultConstants();
			ReadAllData();
			StartThread(MainThread);
			LimitPlayers();		
			//SendLog("system","Servidor iniciado");	
			break;
		}

        case DLL_PROCESS_DETACH:
		{
			for(int i = 0; i < 750; i++)
				SaveAccount(i);

			FreeLibrary(hInstDLL);
			break;
		}
    }

    return TRUE;
}