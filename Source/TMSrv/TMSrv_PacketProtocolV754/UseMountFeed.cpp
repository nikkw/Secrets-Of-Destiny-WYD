#include "DLLMain.h"

void HKD_ProcessClientMessage_UseMountFeed(WORD *mountId, WORD feedId)
{
	switch(*mountId)
	{
		case 19: // Tigre de Fogo
			if(feedId == 7)
				*mountId = 7;
			break;

		case 20: // Dragão Vermelho
			if(feedId == 8)
				*mountId = 8;
			break;

		case 21:
		case 22: // Unicornios
		case 23:
			if(feedId == 9)
				*mountId = 9;
			break;

		case 24:
		case 25: // Grifos
		case 26:
			if(feedId == 10)
				*mountId = 10;
			break;

		case 27: // Svadilfire
			if(feedId == 6)
				*mountId = 6;
			break;

		case 28: // Sleipnir
			if(feedId == 9)
				*mountId = 9;
			break;
	}
}