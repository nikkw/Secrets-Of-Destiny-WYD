#include "DLLMain.h"

int HKD_GenerateSummon_CanSummon(int mobId, int faceId) 
{ 
	// by shepher 
	// Retorne 0 caso não deseje que seja summonado outro mob igual 
	// Retorne 1 para summonar 
	
	// Evocs de bm
	for(INT8 i = 0; i < sizeof(MobFaces) / sizeof(INT16); i++)
		if(faceId == MobFaces[i])
			return 1;

    return 0;
}
	
bool ReadEvokFile(char *szMob, int evokId) 
{
	FILE *hFile = NULL; 
	char szTMP[128]; 
	sprintf_s(szTMP, "npc_base\\%s", szMob); 
	fopen_s(&hFile, szTMP, "rb"); 
	if(hFile != NULL) 
	{ 
		stMOB754 *mobs = (stMOB754*)0x7B08520; 
		fread(&mobs[evokId], 1, 756, hFile); fclose(hFile); 
		return true; 
	} 
	return false; 
}



