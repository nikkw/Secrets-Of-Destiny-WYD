#include "DLLMain.h"

INT32 HKD_ControlTeleportPosition(INT16 clientId, INT16 *ptrX, INT16 *ptrY)
{
	INT16 posX = (*ptrX & 0xFFC),
		    posY = (*ptrY & 0xFFC);

	st_Mob *player = (st_Mob*)GetMobFromIndex(clientId);

	// Noatum para Armia
   	if(posX == 1056 && posY == 1724)
	{
       	*ptrX = 2096;
       	*ptrY = 2096;
		return 0;
   	}
	// Deserto para Kefra
	else if(posX == 1312 && posY == 1900)
	{
		*ptrX = 2366;
		*ptrY = 4064;
		return 1000;
	}
	// Kefra para Deserto
	else if(posX == 2364 && posY == 4072)
	{
		*ptrX = 1314;
		*ptrY = 1897;
		return 1000;
	}
	// Noatum para Gelo
 	else if(posX == 1052 && posY == 1708)
   	{
       	*ptrX = 3649;
       	*ptrY = 3109;

		player->Info.CityID = 3;
       	return 1000;
   	}
	// Gelo para Noatum
   	else if(posX == 3648 && posY == 3108)
   	{
       	*ptrX = 1053;
       	*ptrY = 1710;
       	return 1000;
   	}	
		
	return -1;
}