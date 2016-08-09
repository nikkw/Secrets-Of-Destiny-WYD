#include "DLLMain.h"

void __stdcall HKD_ControlEXP(INT32 clientid, INT32 exp, INT32 type)
{
	if(exp <= 0)
		return;

	st_Mob *player = GetMobFromIndex(clientid);		

	INT8 mCLASS = player->Equip[0].EFV2;
	INT16 mLEVEL = player->bStatus.Level;

	exp *= 6;
		
	switch(mCLASS)
	{
		case 0:
			exp = 0;
			break;

		case 1:
			break;

		case 2:

			// Travas de level
			if(player->Status.Level == 354 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Block355Arch)
			{
				SendClientMessage(clientid, "Seu nível está travado. Para continuar destrave-o.");

				exp = 0;

				return;
			}
			else if(player->Status.Level == 369 && !wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].Quests.Block370Arch)
			{
				SendClientMessage(clientid, "Seu nível está travado. Para continuar destrave-o.");

				exp = 0;

				return;
			}

			if(mLEVEL >= 299)
				exp /= 3;
			else
				exp /= 2;			

			break;					

		case 3: case 4: case 5: case 6:
			exp /= 6;

			if(mLEVEL >= 149)
				exp /= 2; // Cai pela metade
			if(mLEVEL >= 159)
				exp /= 2; // Cai pela metade
			if(mLEVEL >= 169)
				exp /= 2; // Cai pela metade
			if(mLEVEL >= 179)
				exp /= 2; // Cai pela metade
			if(mLEVEL >= 189)
				exp /= 2; // Cai pela metade

			break;

		default:
			exp = 0;
			break;
	}
		
	if(*(INT32*)0x008BF1814) //doubleExp
		exp <<= 1;		

	if(type == 1)
		if(exp > 1000)
			exp = 1000;

	if(wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].ExpBonus > 0)
		exp += (exp / 100) * wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].ExpBonus;

	if(player->Exp + exp > 4200000000)
	{
		// Trava para evitar a existência de exp negativa
		// Limite máximo 4.200.000.000
		exp = 42000000000 - player->Exp;
	}

	if(exp <= 0)
		return;

	player->Exp += exp;
}

INT32 HKD_ExpInPesaAllArea(UINT32 ClientID, INT32 X, INT32 Y)
{
    // retornar 0 caso não queira que dê a experiência
    // retornar 1 caso queira que dê a experiência
	INT32 retn = 0;

	st_Mob *player = GetMobFromIndex(ClientID);

	if((player->LastX >= 1150 && player->LastY >= 130 && 
		 player->LastX <= 1270 && player->LastY <= 220) || // Pesa A
		(player->LastX >= 1040 && player->LastY >= 260 && 
		 player->LastX <= 1135 && player->LastY <= 350) || // Pesa M
		(player->LastX >= 1295 && player->LastY >= 290 && 
		 player->LastX <= 1325 && player->LastY <= 365))   // Pesa N
		retn = 1;
	else if((player->LastX >= 3335 && player->LastY >= 1410 && 
			 player->LastX <= 3451 && player->LastY <= 1465) ||
	        (player->LastX >= 3209 && player->LastY >= 1714 && 
			 player->LastX <= 3316 && player->LastY <= 1781))
		retn = 1;

    return retn;
}