#include "DLLMain.h"

//arch
BOOL HKD_ProcessClientMessage_ReadKingMerchant(int clientId, int npcId)
{
	st_Mob *player = GetMobFromIndex(clientId),
	       *npc    = GetMobFromIndex(npcId);

	BOOL findItens = FALSE;
	if(player->Status.Level >= 299 && player->Equip[0].EFV2 == MORTAL) // Level
	{
		if(player->Equip[10].Index != 1742) // Imortalidade
		{
			SendSay(npcId, "Onde está a Imortalidade ?");

			return TRUE;
		}

		else if(player->Equip[11].Index < 1760 || player->Equip[11].Index > 1763)
		{
			SendSay(npcId, "Traga-me um sephirot para a composição.");

			return TRUE;
		}		

		INT8 FreeSlot = -1;
		for(int i = 0; i < 4; i++)
		{
			if(!strcmp(Users[clientId].CharList.Name[i], "\0"))
			{
				FreeSlot = i;
				break;
			}
		}

		if(FreeSlot == -1)
		{
			SendSay(npcId, "Você não tem espaço suficiente para um novo personagem.");

			return TRUE;
		}						

		INT32 pClass = player->Equip[11].Index - 1760;

		memset(&player->Equip[10], 0, sizeof(st_Item));
		memset(&player->Equip[11], 0, sizeof(st_Item));

		wdBuffer[clientId].Chars[FreeSlot].RespectiveMortal = wdBuffer[clientId].Ingame.LoggedMob;

		SendCharList(clientId);

		MSG_DBCreateArch pServer;		

		pServer.Header.ClientId = clientId;
		pServer.Header.PacketId = 0x80F;
		pServer.Header.Size = sizeof MSG_DBCreateArch;		

		pServer.charSlot = FreeSlot;

		memcpy(&pServer.mob, &MobArch, sizeof MobArch);		
		
		pServer.mob.ClassInfo = pClass;		
		strcpy((char*)pServer.mob.Name, (char*)player->Name);
		INT16 face = (player->ClassInfo == 2? (21 + 5) + pClass : (player->Equip[0].Index + 5) + pClass);
		pServer.mob.Equip[0].Index = face;		
		pServer.mob.Equip[0].EFV2 = 2;
		pServer.mob.Equip[0].EFV3 = face;
		pServer.mob.ClassInfo = pClass;

		pServer.mob.bStatus.Move.Speed = 3;
		pServer.mob.Status.Move.Speed = 3;				
		
		SendDBPacket((BYTE*)&pServer, sizeof MSG_DBCreateArch);

		SendClientSignalParm(clientId, clientId, 0x3B4, FreeSlot);

		SendClientMessage(clientId, "Que a força dos Deuses esteja sempre com você!");		

		return TRUE;
	}
}
/*
Na DB: 
// Desativa leitura das guilds
*(INT8*)0x0040DFB0 = 0xC3; 
*(INT8*)0x0040E350 = 0xC3; 
// No check for nick 
*(BYTE*)0x00414706 = 0xEB; 

Na TM: 
// Desativa as guerras originais 
JMP_NEAR(0x004013D9, (void*)0x0045792A); 
JMP_NEAR(0x00457A20, (void*)0x00458921);
*/