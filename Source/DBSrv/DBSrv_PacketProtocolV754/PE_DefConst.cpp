// ---
// by ptr0x
// ---

#include "PE_DefConst.h"

stMOB754 charBase[4];

void SetDefaultConstants()
{
	ChangeItemlistStructPointer();
	ChangeStructCharBase();
}

void CreateChar(BYTE *packetBuffer)
{
	int classe = packetBuffer[32];

    if(classe == 0)
	{
		// Caso seja um tk mortal seta todos equipamentos
		// para set de mortal, face, pontos e itens.
		charBase[0].Gold = 0;
		charBase[0].StatusPoint = 0;
		charBase[0].ClassInfo = 0;
		charBase[0].bStatus.Defense = 4;
		charBase[0].bStatus.Attack = 5;
		charBase[0].bStatus.STR = 4;
		charBase[0].bStatus.INT = 8;
		charBase[0].bStatus.DEX = 7;
		charBase[0].bStatus.CON = 6;
		//1 43 0 98 1
		charBase[0].Equip[0].Index = 1;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 98;
		charBase[0].Equip[0].EFV2 = 1;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		return;
	}
	for(int i=1;i<8;i++)
	{
		// Apaga todos itens para que o novo char (ARCH)
		// não venha com set de TK Mortal.
		charBase[0].Equip[i].Index = 0;
		charBase[0].Equip[i].EF1 = 0;
		charBase[0].Equip[i].EF2 = 0;
		charBase[0].Equip[i].EF3 = 0;
		charBase[0].Equip[i].EFV1 = 0;
		charBase[0].Equip[i].EFV2 = 0;
		charBase[0].Equip[i].EFV3 = 0;
	}
	// Gold
	charBase[0].Gold = 0;

	// TODAS CLASSES TK - X
	if(classe == 10)// TK - TK
	{
		charBase[0].Equip[0].Index = 6;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 0;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 11)// TK - FM
	{
		charBase[0].Equip[0].Index = 7;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 1;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 12)// TK - BM
	{
		charBase[0].Equip[0].Index = 8;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 2;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 13)// TK - HT
	{
		charBase[0].Equip[0].Index = 9;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 3;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	// TODAS CLASSES FM - X
	if(classe == 14)// FM - TK
	{
		charBase[0].Equip[0].Index = 16;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 0;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 15)// FM - FM
	{
		charBase[0].Equip[0].Index = 17;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 1;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 16)// FM - BM
	{
		charBase[0].Equip[0].Index = 18;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 2;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 17)// FM - HT
	{
		charBase[0].Equip[0].Index = 19;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 3;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	// TODAS CLASSES BM - X
	if(classe == 18)// BM - TK
	{
		charBase[0].Equip[0].Index = 26;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 0;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 19)// BM - FM
	{
		charBase[0].Equip[0].Index = 27;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 1;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 20)// BM - BM
	{
		charBase[0].Equip[0].Index = 28;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 2;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 21)// BM - HT
	{
		charBase[0].Equip[0].Index = 29;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 3;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	// TODAS CLASSES HT - X
	if(classe == 22)// HT - TK
	{
		charBase[0].Equip[0].Index = 36;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 0;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 23)// HT - FM
	{
		charBase[0].Equip[0].Index = 37;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 1;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 24)// HT - BM
	{
		charBase[0].Equip[0].Index = 38;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 2;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	if(classe == 25)// HT - HT
	{

		charBase[0].Equip[0].Index = 39;
		charBase[0].Equip[0].EF1 = 43;
		charBase[0].Equip[0].EFV1 = 0;
		charBase[0].Equip[0].EF2 = 0;
		charBase[0].Equip[0].EFV2 = 2;
		charBase[0].Equip[0].EF3 = 0;
		charBase[0].Equip[0].EFV3 = charBase[0].Equip[0].Index;
		charBase[0].bStatus.Level = 0;
		charBase[0].ClassInfo = 3;
		memset(&charBase[0].Inventory, 0, sizeof(charBase[0].Inventory) - sizeof(st_Item));
		return;
	}
	
	return;
}

void ChangeStructCharBase()
{
	// Altera na memoria o local salvo para a base dos chars TKs
	for(DWORD i = 0x401000, addrBase = 0x15AB710, addrFinal = 0x15ABA04;i<0x455FFF;i++)
	{
		if(*(DWORD*)i >= addrBase && *(DWORD*)i < addrFinal)
		{
		int diff = *(DWORD*)i - addrBase;
		*(DWORD*)i = (DWORD)&charBase[0] + diff;
		}
	}
	// Altera na memoria o local salvo para a base dos chars FMs
	for(DWORD i = 0x401000, addrBase = 0x15ABA04, addrFinal = 0x15ABCF8;i<0x455FFF;i++)
	{
		if(*(DWORD*)i >= addrBase && *(DWORD*)i < addrFinal)
		{
		int diff = *(DWORD*)i - addrBase;
		*(DWORD*)i = (DWORD)&charBase[1] + diff;
		}
	}
	// Altera na memoria o local salvo para a base dos chars BMs
	for(DWORD i = 0x401000, addrBase = 0x15ABCF8, addrFinal = 0x15ABFEC;i<0x455FFF;i++)
	{
		if(*(DWORD*)i >= addrBase && *(DWORD*)i < addrFinal)
		{
		int diff = *(DWORD*)i - addrBase;
		*(DWORD*)i = (DWORD)&charBase[2] + diff;
		}
	}
	// Altera na memoria o local salvo para a base dos chars HTs
	for(DWORD i = 0x401000, addrBase = 0x15ABFEC, addrFinal = (0x15ABFEC + 0x2F4);i<0x455FFF;i++)
	{
		if(*(DWORD*)i >= addrBase && *(DWORD*)i < addrFinal)
		{
		int diff = *(DWORD*)i - addrBase;
		*(DWORD*)i = (DWORD)&charBase[3] + diff;
		}
	}
}

void ChangeItemlistStructPointer()
{
	// Altera os endereços estáticos da estrutura do mob (STRUCT_MOB) para o buffer da dll.
	for(DWORD i = 0x401000, addrBase = 0x877580, addrFinal = 0x87760C; i < 0x456000; i++)
	{
		if(*(DWORD*)i >= addrBase && *(DWORD*)i <= addrFinal)
		{
			int diff = *(DWORD*)i - addrBase;

			*(DWORD*)i = (DWORD)GetItemlistBuffer() + diff;
		}
	}

	*(int*)0x0406091 = 6500 * sizeof(st_ItemList);
	*(int*)0x0405D1B = 6500 * sizeof(st_ItemList);
	*(int*)0x0405DA7 = 6500 * sizeof(st_ItemList);
	*(int*)0x04060E9 = 6500 * sizeof(st_ItemList);

	// Modifica todas as checagens de índices do itemlist
	// para poder adicionar novos itens no servidor
	*(int*)0x040171A = 6500;
    *(int*)0x0402AC1 = 6500;
    *(int*)0x04031D1 = 6500;
    *(int*)0x0403AE1 = 6500;
    *(int*)0x0404233 = 6500;
    *(int*)0x04045A3 = 6500;
    *(int*)0x0404E7B = 6500;
    *(int*)0x040507D = 6500;
    *(int*)0x04050A3 = 6500;
    *(int*)0x04061D0 = 6500;
    *(int*)0x040696B = 6500;
    *(int*)0x04077D9 = 6500;
    *(int*)0x0408A7F = 6500;
    *(int*)0x0408B1E = 6500;
    *(int*)0x040A95A = 6500;
}