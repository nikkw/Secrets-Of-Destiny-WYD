#include "DLLMain.h"

int	g_pBASE_IncrementStatus[4][6] = {
	//	MORTAL	-	ARCH	-	CELESTIAL+
	//	HP - MP - HP - MP - HP - MP
	{3, 1,     4, 1,     5, 2}, // Transknight
	{1, 3,     1, 3,     2, 4}, // Foema
	{1, 2,     1, 4,     2, 5}, // BeastMaster
	{2, 1,     2, 2,     3, 3}  // Hunter
};

int BASE_GetHpMp(st_Mob* mob) //00402110 - ok - atualizada(reconhece evolucao)
{
	int clsInfo = mob->ClassInfo;
	if(clsInfo < 0 || clsInfo > 3)
		return FALSE;

	int baseHP = BaseSIDCHM[clsInfo][4];
	int calcHP = ((mob->bStatus.CON - BaseSIDCHM[clsInfo][2]) << 1);
	int calcHPLvl = 0;

	if(mob->Equip[0].EFV2 == MORTAL)
		calcHPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][0];
	else if(mob->Equip[0].EFV2 == ARCH)
		calcHPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][2];
	else
		calcHPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][4];

	UINT32 fHP = baseHP + calcHP + calcHPLvl;

	if(fHP > MAX_HPMP)
		fHP = MAX_HPMP; 

	mob->bStatus.maxHP = fHP;
	mob->Status.maxHP = fHP;

	int baseMP = BaseSIDCHM[clsInfo][5];
	int calcMP = ((mob->bStatus.INT - BaseSIDCHM[clsInfo][3]) << 1);
	int calcMPLvl = 0;

	if(mob->Equip[0].EFV2 == MORTAL)
		calcMPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][1];
	else if(mob->Equip[0].EFV2 == ARCH)
		calcMPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][3];
	else
		calcMPLvl = mob->bStatus.Level * g_pBASE_IncrementStatus[clsInfo][5];

	UINT32 fMP = baseMP + calcMP + calcMPLvl;

	if(fMP > MAX_HPMP)
		fMP = MAX_HPMP;

	mob->bStatus.maxMP = fMP;
	mob->Status.maxMP = fMP;

	return TRUE;
}
