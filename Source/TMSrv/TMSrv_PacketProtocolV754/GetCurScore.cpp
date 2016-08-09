#include "DLLMain.h"

void HKD_BASE_GetCurrentScore_FixStatus(st_Mob &mob, stAffects *affect)
{
	BASE_GetCurrentScore(mob, affect);

	INT32 clientid = GetUserFromMob((int)&mob);

	GetCurScore(&mob, clientid);		
}

void GetCurScore_CapeInfo(st_Mob* player)
{
	if(player->CapeInfo != 4)
	{			
		INT16 cape = player->Equip[15].Index;
		switch(cape)
		{ 
			case  543: case  545: case  734: case  736: case 3191: 
			case 3194: case 3197: case 3300: case 3303: case 3306:
				cape = 7;
				break;
			case  544: case  546: case  735: case  737: case 3192: 
			case 3195: case 3198: case 3301: case 3304: case 3307:
				cape = 8;
				break;
		}

		player->CapeInfo = cape;
	}		
}

void GetCurScore_Affects(st_Mob *player, INT32 clientid)
{
	for(INT8 i = 0; i < 16; i++)
	{
		switch(mBuffer[clientid].Affects[i].Index)
		{
			case 29: // Soul
			{
				if(player->Equip[0].EFV2 == ARCH)
				{
					memset(&mBuffer[clientid].Affects[i], 0x0, sizeof(stAffects));
					break;
				}

				int strbonus = 0, intbonus = 0, dexbonus = 0, conbonus = 0;

				if(player->Equip[0].EFV2 == MORTAL)
				{
					if(mBuffer[clientid].Affects[i].Master == 11)
					{
						player->Status.STR = 2000;
						player->Status.INT = 2000;
						player->Status.maxHP = 10000;
						player->Status.maxMP = 10000;
						break;
					}

					strbonus = MortalStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][0];
					intbonus = MortalStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][1];
					dexbonus = MortalStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][2];
					conbonus = MortalStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][3];
				}
				else
				{
					strbonus = CeleStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][0];
					intbonus = CeleStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][1];
					dexbonus = CeleStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][2];
					conbonus = CeleStatsBonuse[wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].SoulInfo][3];
				}

				player->Status.STR += ((player->bStatus.STR / 100) * strbonus);
				player->Status.DEX += ((player->bStatus.DEX / 100) * dexbonus);
				player->Status.INT += ((player->bStatus.INT / 100) * intbonus);
				player->Status.CON += ((player->bStatus.CON / 100) * conbonus);

				player->Status.Attack += (((player->bStatus.STR / 100) * strbonus) / 3);
				player->Status.maxHP  += (((player->bStatus.CON / 100) * conbonus) * 2);
				player->Status.maxMP  += (((player->bStatus.INT / 100) * intbonus) * 2);							

				break;
			}
			case 38: //8 skill ht troca
				{

				player->Status.maxMP >>= 1;
				player->Status.maxHP += player->Status.maxMP + (500 * ((player->Status.Mastery[2] << 1) / 100)) + 100;					

				if(player->Status.curHP > player->Status.maxHP)
					player->Status.curHP = player->Status.maxHP;

				if(player->Status.curMP > player->Status.maxMP)
					player->Status.curMP = player->Status.maxMP;

				}
				break;
		}
	}
}

void GetCurScore_FixBonus(INT32 clientid)
{
	st_Mob *player = GetMobFromIndex(clientid);

	INT32 ExpBonus = 0;
	INT32 DropBonus = 0;
	INT32 ForceDamage = 0;
	INT32 ReflectDamage = 0;
	UINT16 ExtractHp = 0,
		  ExtractMp = 0;

	for(INT8 i = 1; i < 16; i++)
	{
		/* Futuro sistema extração de HP/MP
		for (int e = 0; e < 3; e++)
		{
			if (player->Equip[i].Effect[e].Index == EF_GETHP || player->Equip[i].Effect[e].Index == EF_GETMP)
			{
				INT16 sanc  = GetItemSanc(&player->Equip[i]),
                      value = player->Equip[i].Effect[e].Value;

				if (sanc >= 230)
					sanc = 10 + ((sanc - 230) / 4);

				if (sanc <= 10)
					value = (((sanc + 10) * value) / 10);
				else
				{
					static int Power[] = {
						220, 250, 280, 320, 370
					};

					int val = Power[sanc - 11];
					value = ((value * val) / 100);
				}

				player->Equip[i].Effect[e].Index == EF_GETHP ? ExtractHp += value : ExtractMp += value;

				break;
			}
		}
		*/

		INT16 EquipID = player->Equip[i].Index;
		if(EquipID <= 0 || EquipID > 6500)
			continue;

		if(ItemList[EquipID].Grade == 5)
			DropBonus += 8;

		if(ItemList[EquipID].Grade == 6)
			ForceDamage += 20;

		if(ItemList[EquipID].Grade == 7)
			ExpBonus += 2;
			
		if(ItemList[EquipID].Grade == 8)
			ReflectDamage += 20;

		else
		{	
			INT32 sanc = GetItemSanc(&player->Equip[i]);	

			if(sanc >= 230)
			{
				INT8 mCALC = sanc % 4;

				switch(mCALC)
				{
				case 0:
					ExpBonus += 2;
					break;

				case 1:
					ReflectDamage += 20;
					break;

				case 2:
					DropBonus += 8;
					break;

				case 3:
					ForceDamage += 20;
					break;

				}
			}
		}
	}			

	if(player->Equip[13].Index > 0) //fadas
	{
		switch(player->Equip[13].Index)
		{
		case 3900: case 3903: case 3906: case 3911: case 3912: case 3913: //fada verde
			ExpBonus += 16;
			break;

		case 3901: case 3904: case 3907: //azul
			DropBonus += 32;
			break;

		case 3902: case 3905: case 3908: //vermelha
			ExpBonus += 32;
			DropBonus += 16;
			break;

		case 3914: //prateada
			ExpBonus += 16;
			DropBonus += 32;
			break;

		case 3915:
			ExpBonus += 18;
			DropBonus += 50;
			break;
		}
	}	

	for(int i = 0; i < 16; i++)
	{
		switch(mBuffer[clientid].Affects[i].Index)
		{
			case 39:
				ExpBonus += 110;
				break;
		}
	}

	if(isVip(clientid))
	{
		ExpBonus += 30;
		DropBonus += 30;
	}

	if(clientid < 750)
	{
		wdBuffer[clientid].Chars[wdBuffer[clientid].Ingame.LoggedMob].ExpBonus = ExpBonus;
		wdBuffer[clientid].Ingame.HpExtract = ExtractHp;
		wdBuffer[clientid].Ingame.HpExtract = ExtractMp;
	}	

	player->DropBonus = DropBonus;
	player->ForceDamage = ForceDamage;
	player->ReflectDamage = ReflectDamage;			
}

void GetCurScore(st_Mob *player, INT32 clientid)
{
	GetCurScore_CapeInfo(player);		
	GetCurScore_Affects(player, clientid);				

	INT16 calcCriticalIncrement = ((GetMobAbility(player, EF_CRITICAL) / 10) * 2.5) + (GetMobAbility(player, EF_CRITICAL2) / 10 * 2.5);		
	INT16 calcMagicIncrement = (GetMobAbility(player, EF_MAGIC) + GetMobAbility(player, EF_MAGICADD));			

	// Skills passívas
	if(player->ClassInfo == 0) // TK
	{
		if((player->Learn & (1 << 9)))
		{// Bonus ao usar 2 armas equipadas  (mestre das armas)
			if(player->Equip[6].Index && player->Equip[7].Index)
				player->Status.Attack += ((player->Status.Mastery[2] * 3) / 2) + 100;						
		}

		if((player->Learn & (1 << 14)))
			player->Status.Attack += (player->Status.Mastery[2] / 2) + 100;			
			
		if((player->Learn & (1 << 15)))
		{//Defesa e critico (Armadura critica)   
			player->Status.Defense += (player->Status.Mastery[2] * 5) / 2;
			calcCriticalIncrement += 25;				
		}
	}

	else if(player->ClassInfo == 2) //BM
	{			
		if((player->Learn & (1 << 67)))
		{
			if(player->Equip[7].Index > 0)
			{
				INT32 itemUnique = ItemList[player->Equip[7].Index].Unique;

				if(itemUnique == 51) //escudo					
					player->Status.Defense += player->Status.Mastery[3] + 25;					
			}
		}			
	}
		
	else if(player->ClassInfo == 3) // HT
	{			
		if((player->Learn & (1 << 75)))
		{
			INT32 itemUnique = ItemList[player->Equip[6].Index].Unique;

			if(itemUnique == 44 || itemUnique == 42) //arcos ou garras
				player->Status.Attack += 80 + ((player->Status.Mastery[1] * 3) / 100) * 80;	
		}			

		if((player->Learn & (1 << 82)))
		{//Pericia de caçador (aumenta o atk se tiver com armas de 1 mao)
			if(player->Equip[6].Index != 0 && player->Equip[7].Index == 0)
				player->Status.Attack += 80 + ((player->Status.Mastery[2] * 3) / 100) * 80;			
		}

		if((player->Learn & (1 << 91)))
		{//Visao de caçadora (aumenta o critico proporcional a velocidade)
			calcCriticalIncrement += (player->Status.DEX / 50);
		}

		if((player->Learn & (1 << 94)))
		{ //proteção das sombras (+def com garras)
			INT32 itemUnique = ItemList[player->Equip[6].Index].Unique;

			if(itemUnique == 44)
				player->Status.Defense += ((player->Status.Mastery[3] * 3) / 100) * 80;			
		}

		if((player->Learn & (1 << 79)))
		{
			//tempestade de raios (8 skill)
			player->Status.Attack += 200;
		}
	}					
		
	if(player->Equip[6].Index > 0)
	{
		INT16 weaponUnique = ItemList[player->Equip[6].Index].Unique;

		if(weaponUnique == 47)
			calcMagicIncrement += 8;
		else
			player->Status.Attack += 40;
	}

	if(player->Equip[7].Index > 0)
	{
		INT16 shieldUnique = ItemList[player->Equip[7].Index].Unique;

		if(shieldUnique == 47)
			calcMagicIncrement += 8;
		else
			player->Status.Attack += 40;	
	}				

	calcMagicIncrement = (((calcMagicIncrement + 1) >> 1) / 100) * 70;

	if(calcMagicIncrement > 255)
		calcMagicIncrement = 255;				

	if(calcCriticalIncrement > 255)
		calcCriticalIncrement = 255;		

	player->Critical = calcCriticalIncrement;	
	player->MagicIncrement = calcMagicIncrement;	

	player->Status.Attack += (player->Status.DEX / 4);
}

void __stdcall HKD_BASE_GetCurrentScore_BlockStatus(INT32 clientid)
{
	st_Mob *player = GetMobFromIndex(clientid);

	if(player->Status.Attack > 32000)
		player->Status.Attack = 32000;

	if(player->bStatus.Attack > 32000)
		player->bStatus.Attack = 32000;

	if(player->Status.Defense > 32000)
		player->Status.Defense = 32000;

	if(player->bStatus.Defense > 32000)
		player->bStatus.Defense = 32000;

	if(player->Status.curHP > MAX_HPMP)
		player->Status.curHP = MAX_HPMP;

	if(player->bStatus.curHP > MAX_HPMP)
		player->bStatus.curHP = MAX_HPMP;

	if(player->Status.maxHP > MAX_HPMP)
		player->Status.maxHP = MAX_HPMP;

	if(player->bStatus.maxHP > MAX_HPMP)
		player->bStatus.maxHP = MAX_HPMP;

	if(player->Status.curMP > MAX_HPMP)
		player->Status.curMP = MAX_HPMP;

	if(player->bStatus.curMP > MAX_HPMP)
		player->bStatus.curMP = MAX_HPMP;

	if(player->Status.maxMP > MAX_HPMP)
		player->Status.maxMP = MAX_HPMP;

	if(player->bStatus.maxMP > MAX_HPMP)
		player->bStatus.maxMP = MAX_HPMP;					

	GetCurScore_FixBonus(clientid);
}