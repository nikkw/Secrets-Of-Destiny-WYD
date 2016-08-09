//---
// Secrets Of Destiny TEAM
//---

#include "main.h"

bool file_exists(const char *filename)
{
	FILE *arquivo;
	if(arquivo = fopen(filename, "r"))
	{
		fclose(arquivo);
		return TRUE;
	}
	return FALSE;
}

void Change_D1D_color(int color)
{
	DWORD dwOldProt = 0x40;
	VirtualProtect((void*)0x0049A477, 4, dwOldProt, &dwOldProt);
	*(DWORD*)0x0049A477 = color;
	VirtualProtect((void*)0x0049A477, 4, dwOldProt, &dwOldProt);
}

void Change_TAB_color(int color)
{
	DWORD dwOldProt = 0x40;
	VirtualProtect((void*)0x0050542B, 4, dwOldProt, &dwOldProt);
	*(DWORD*)0x0050542B = color;
	VirtualProtect((void*)0x0050542B, 4, dwOldProt, &dwOldProt);
}

void Change_SMS_color(int color)
{
	DWORD dwOldProt = 0x40;
	VirtualProtect((void*)0x00499DE0, 4, dwOldProt, &dwOldProt);
	*(DWORD*)0x00499DE0 = color;
	VirtualProtect((void*)0x00499DE0, 4, dwOldProt, &dwOldProt);
}