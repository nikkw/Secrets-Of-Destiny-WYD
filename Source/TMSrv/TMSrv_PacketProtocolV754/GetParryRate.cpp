#include "DLLMain.h"

INT32 __stdcall HKD_GetParryRate_FixEvasion(INT32 clientid, INT32 otherClientId, INT32 parry)
{
	st_Mob *player = GetMobFromIndex(clientid);
	st_Mob *otherPlayer = GetMobFromIndex(otherClientId);

	//Desativa essa função pras evocações.
	for(INT8 i = 0; i < sizeof(MobFaces) / sizeof(INT16); i++)
		if(player->Equip[0].Index == MobFaces[i])
			return 0;

	if(player->Learn & (1 << 100))
		parry = (parry / 100) * 80;

	// Player x Player
	if(otherClientId < MAX_PLAYER && clientid < MAX_PLAYER)
	{							
		INT32 mCALCPLAYER = (INT32)(player->Status.DEX / 1000);
		if(mCALCPLAYER <= 0)
			mCALCPLAYER = 1;
		else if(mCALCPLAYER > 15)
			mCALCPLAYER = 15;

		INT32 mCALCAFFECTED = (INT32)(otherPlayer->Status.DEX / 1000);
		if(mCALCAFFECTED <= 0)
			mCALCAFFECTED = 1;
		else if(mCALCAFFECTED > 15)
			mCALCAFFECTED = 15;

		INT32 mREDUCTION = mCALCPLAYER * 140;

		if(mCALCPLAYER > mCALCAFFECTED)
			mREDUCTION = mCALCAFFECTED * 140;			

		if(mREDUCTION < 100)
			mREDUCTION = 100;
			
		if(mREDUCTION > ((parry >> 1) + 150))
			mREDUCTION = (parry >> 1) + 100;							

		parry -= mREDUCTION;

		for(UINT8 i = 0; i < 16; i ++)			
			if(mBuffer[clientid].Affects[i].Index == 8)				
				if((mBuffer[clientid].Affects[i].Value & 64))	
					parry -= 100;						

		if(!(player->Learn & (1 << 100)))				
			parry -= 100;

		if(parry < 100)
			parry = 100;

		if(parry > 850)
			parry = 850;

		return parry;
	}

	// MOB x Player
	else if(clientid < MAX_PLAYER && otherClientId >= MAX_PLAYER)
	{
		if(parry > 400)
			parry = 400;			

		else if(parry < 50)
			parry = 50;

		return parry;
	}
}
	
INT32 GetParryRate(st_Mob *player, INT32 Parry)
{
	INT32 result[2];

	if (Parry > 100)
		Parry = 100;
	else if (Parry < 0)
		Parry = 0;

	result[0] = player->Status.DEX;

	if (result[0] > 15000)
		result[0] = 15000;

	result[0] /= 10;

	result[1] = result[0] + Parry;

	if(player->AffectInfo.Value & 8)
		result[1] += 70;

	if(player->AffectInfo.Value & 32)
		result[1] += 50;

	if(player->AffectInfo.Value & 128)
		result[1] += 50;

	return result[1];
}