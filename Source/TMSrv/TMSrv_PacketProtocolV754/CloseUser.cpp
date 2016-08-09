#include "DLLMain.h"

void HKD_CloseUser(int clientId) 
{
	if(Trade[clientId].isTrading)
		CloseTrade(clientId);

	SaveAccount(clientId);
}