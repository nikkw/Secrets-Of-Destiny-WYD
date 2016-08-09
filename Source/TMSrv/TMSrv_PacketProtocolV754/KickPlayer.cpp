#include "DLLMain.h"

void RemoveParty(INT32 conn)
{
	//criado por Bruno Garcia de Oliveira

	if(conn<0 || conn>=750)
		return;

	st_Mob *player = GetMobFromIndex(conn);

	int leader = player->Leader;
	if(leader == 0) 
		leader = conn;

	if  (leader <0 || leader >= 30000)
		return;

	st_Mob *lea = GetMobFromIndex(leader);

	INT32 i;

	SendRemoveParty(conn, 0);
	
	if(conn != leader) //quando um membro sai do grupo
	{ //sem erros
		SendRemoveParty(leader, conn);
		player->Leader = 0;		

		for(i = 0; i < 12; i ++)
		{
			int member = lea->PartyList[i];
	   	  	if  (member <= 0)
				continue;
	        
			if(member == conn) 
			{
				memcpy(&(lea->PartyList[i]), &(lea->PartyList[i+1]), sizeof(INT32) * (12-i-1));
				lea->PartyList[12-1] = 0;
				member = lea->PartyList[i];
			}

			if (member > 0 && member < 750)
				SendRemoveParty(member, conn);
		}		
	}	
	else //quando um lider sai do grupo
	{   //o erro está nessa parte
		leader = player->PartyList[0];
		memcpy(lea->PartyList, &(player->PartyList[1]), sizeof(int) * (12-1));
		lea->Leader = 0; 	
				
		SendRemoveParty(leader, 0);
	
 		for(i = 0; i < 12; i++)
		{   
			INT32 member = lea->PartyList[i];

   	  		if  (member <=0 || member>30000)
				continue;
						
			GetMobFromIndex(member)->Leader = leader;
		
			if (member > 0 && member < 750)
				SendRemoveParty(member, conn);
		}
	
		memset(player->PartyList, 0, sizeof(int) * 12);	
		player->Leader = 0;
	}
}


