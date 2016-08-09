#include "DLLMain.h"

UINT8 GetSanc(st_Mob &player)
{
	INT32 sanc = (unsigned char)(player.Status.Mastery[3] / 22);

	if(sanc > 9)
		sanc = 9;	

	else if(player.Equip[0].EFV2 >= 3)
		sanc = 9;		
		
	return sanc;
}
	

void __stdcall HKD_Base_GetCurrentScore_FixTrans(st_Mob &player, INT32 transId)
{	
	UINT16 value;
	if(transId == 4)		
		value = 32;			
	else
		value = transId + 22;

	INT32 clientid = GetUserFromMob((int)&player);		

	if(!(player.Equip[0].Index >= 22 && player.Equip[0].Index <= 25 || player.Equip[0].Index == 32))				
		player.Equip[0].EFV3 = player.Equip[0].Index;			

	player.Equip[0].Index = value;	

	if(player.Equip[0].Index == 32)
	{
		player.Equip[0].EF1 = 43;
		player.Equip[0].EFV1 = GetSanc(player);					
		SendEquip(clientid);

		BYTE packet[108]; 
		BASE_GetCreateMob(clientid, (BYTE*)&packet);
		GridMulticast(clientid, player.TargetX, player.TargetY, (void*)&packet);
	}		
}

void __stdcall HKD_Base_GetCurrentScore_FixFaceArch(st_Mob &player)
{
	if(player.Equip[0].Index >= 22 && player.Equip[0].Index <= 25 || player.Equip[0].Index == 32)								
		player.Equip[0].Index = player.Equip[0].EFV3;
}