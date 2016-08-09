#include "DLLMain.h"

bool HKD_CorrectPositionGoWorld(INT32 ClientID, INT16* PosX, INT16* PosY)
{
	st_Mob *player = GetMobFromIndex(ClientID);	

	if(player->bStatus.Level <= 34 && player->Equip[0].EFV2 == MORTAL)
	{
		*PosX = 2112;
		*PosY = 2042;
	}
	else
	{
		if(player->Info.CityID == 3) // Cidade de Karden implementada.
		{
			*PosX = 3645 + (Rand() % 3);
			*PosY = 3122 + (Rand() % 3);
		}			
	}

	BASE_GetEmptyMobGrid(ClientID, (int*)&PosX, (int*)&PosY);					

	SendEtc(ClientID);		

	return true;
}