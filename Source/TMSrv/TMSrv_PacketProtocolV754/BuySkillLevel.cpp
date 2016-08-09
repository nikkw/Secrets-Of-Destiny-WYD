#include "DLLMain.h"

INT32 BuySkillCele(INT32 ClientID)
{
	// retornar 0 caso não queira utilizar a função.
	// retornar 1 caso queira utilizar a função.
	st_Mob *player = GetMobFromIndex(ClientID);

	if(player->Equip[0].EFV2 >= CELESTIAL)
		return 1;

	return 0;
}