#include "DLLMain.h"

int BASE_GetBonusScorePoint(st_Mob* mob) //00401fc0 - ok
{
	int clsInfo = mob->ClassInfo;
	if(clsInfo < 0 || clsInfo > 3)
		return FALSE;

	INT16 clientId = GetUserFromMob(mob);

	int decStr = mob->bStatus.STR - BaseSIDCHM[clsInfo][1];
	int decInt = mob->bStatus.INT - BaseSIDCHM[clsInfo][2];
	int decDes = mob->bStatus.DEX - BaseSIDCHM[clsInfo][3];
	int decCon = mob->bStatus.CON - BaseSIDCHM[clsInfo][4];

	int calcDecs = decStr + decInt + decDes + decCon;
	int lvl = mob->bStatus.Level;
	int totalStats = 0;
	
	switch(mob->Equip[0].EFV2)
	{
		case MORTAL:
		{
			totalStats += lvl * 5;

			if(lvl >= 254)
				totalStats += ((lvl - 254) * 5);
			if(lvl >= 299)
				totalStats += ((lvl - 299) * 10);
			if(lvl >= 355)
				totalStats -= ((lvl - 355) * 8);

			break;
		}
		case ARCH: 
		{
			totalStats += lvl * 6;

			if(lvl > 354)
				totalStats += (lvl - 354) * 6;

			// Este if é uma tentativa de acabar com os casos de arch com os pontos bugados
			if((Users[clientId].CharList.Status[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal].Level - 299) > 0)
				totalStats += (Users[clientId].CharList.Status[wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].RespectiveMortal].Level - 299) * 6;

			break;
		}
		case CELESTIAL: case SCELESTIAL: case HARDCORE: case SHARDCORE:
		{
			// Bônus pelas quests que foram feitas no arch
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.CristalElime)
				totalStats += 100;
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.CristalSylphed)
				totalStats += 100;
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.CristalThelion)
				totalStats += 100;
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.CristalNoas)
				totalStats += 100;

			// Bônus pelo level que o celestial foi feito
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.Level355)
				totalStats += 100;
			else if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.Level370)
				totalStats += 300;
			else if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.Level380)
				totalStats += 600;
			else if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.Level398)
				totalStats += 900;
			else if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.Level399)
				totalStats += 1200;

			// Pontos base de celestial 
			totalStats += 1001; 

			// Pontos de level
			totalStats += lvl * 10; 

			if(mob->Equip[0].EFV2 == HARDCORE || mob->Equip[0].EFV2 == SHARDCORE)
				totalStats += lvl * 2;

			// Bônus pelo level cele/sub
			if(wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Quests.SubCeleMade && mob->Equip[0].EFV2 <= SCELESTIAL)
			{
				UINT16 otherPersoPoints = 0;

				if(mob->Equip[0].EFV2 == CELESTIAL)
					otherPersoPoints += (wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Persos[1].Stats.Level * 6);
				else if(mob->Equip[0].EFV2 == SCELESTIAL)
					otherPersoPoints += (wdBuffer[clientId].Chars[wdBuffer[clientId].Ingame.LoggedMob].Persos[0].Stats.Level * 6);

				if(otherPersoPoints)
					totalStats += otherPersoPoints;
			}

			// Bônus por ter atingido o level 191
			if(lvl > 189)
				totalStats += 290;

			break;
		}
	}

	mob->StatusPoint = totalStats - calcDecs;

	if((totalStats - calcDecs) < 0)
		mob->StatusPoint = 0;

	return TRUE;
}

int HKD_BASE_GetBonusSkillPoint(st_Mob* mob)
{
	int skillPoints = 0;

	if(mob->Equip[0].EFV2 == MORTAL || mob->Equip[0].EFV2 == ARCH)
		skillPoints = mob->bStatus.Level * 3;
	else if(mob->Equip[0].EFV2 >= CELESTIAL)
	{
		// Ganha 4 pontos de skill por level
		// Mais os 1500 ganhos ao criar o personagem
		skillPoints = mob->bStatus.Level * 4;
		skillPoints += 1500;
	}

	return skillPoints;
}