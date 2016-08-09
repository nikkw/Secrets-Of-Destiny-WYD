#include "GetCreateMob.h"

int GetAnctCode(st_Item *item)
{
	int value = 0;

	if(item->EF1 >= 116 && item->EF1 <= 125)
	{
		value = item->EF1;
		return value;
	}
	else if(item->EF2 >= 116 && item->EF2 <= 125)
	{
		value = item->EF2;
		return value;
	}
	else if(item->EF3 >= 116 && item->EF3 <= 125)
	{
		value = item->EF3;
		return value;
	}
  
	else if(item->EF1 == 43)
       	value = item->EFV1;
   	else if(item->EF2 == 43)
       	value = item->EFV2;
	else if(item->EF3 == 43)
       	value = item->EFV3;
	if(value == 0)
      	return 0;
	if(value < 230)
		return 43;
    
	switch(value % 4)
   	{       	
		case 0:  return 0x30;
  	 	case 1:  return 0x40;
       	case 2:  return 0x10;
       	case 3:  return 0x20;
		default: return value;
   	}
}

WORD GetItemIDEF(st_Item *item, bool mnt)
{
	int value = 0; bool colored = false;
	
	if(mnt) { // montaria
		value = (int)item->EF2 / 10;
		return (value * 4096) + item->Index;
	}
	else
	{
		if(item->EF1 >= 116 && item->EF1 <= 125) { // item colorido
			value = item->EFV1;
			colored = true;
		}
		else if(item->EF2 >= 116 && item->EF2 <= 125) { // item colorido
			value = item->EFV2;
			colored = true;
		}
		else if(item->EF3 >= 116 && item->EF3 <= 125) { // item colorido
			value = item->EFV3;
			colored = true;
		}
		else if(item->EF1 == 43) { // item sem cor
			value = item->EFV1;
		}
		else if(item->EF2 == 43) { // item sem cor
			value = item->EFV2;
		}
		else if(item->EF3 == 43) { // item sem cor
			value = item->EFV3;
		}
		else  // item sem refinação
			return item->Index;
	}

	if(value > 9 && !colored)
	{
		if(value >= 230 && value <= 233)
			value = 10;
		else if(value >= 234 && value <= 237)
			value = 11;
		else if(value >= 238 && value <= 241)
			value = 12;
		else if(value >= 242 && value <= 245)
			value = 13;
		else if(value >= 246 && value <= 249)
			value = 14;
		else if(value >= 250 && value <= 253)
			value = 15;
		else // value >= 254
			value = 16;
	}

	if(value > 9 && colored) {
		value = 9;
	}

	return (value * 4096) + item->Index;
}

void FixGetCreateMob_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	p613_GetCreateMob *def_GetCreateMob = (p613_GetCreateMob*)packetBuffer;
	p754_GetCreateMob *new_GetCreateMob = (p754_GetCreateMob*)m_PacketBuffer;
	st_Mob *thisMob = GetMobFromIndex(new_GetCreateMob->ClientId);

	memcpy(&new_GetCreateMob->GuildIndex, &def_GetCreateMob->GuildIndex, 32);

	for(int i = 0; i < 16; i++)
	{
		new_GetCreateMob->Affect[i].Index = mBuffer[new_GetCreateMob->ClientId].Affects[i].Index; 
		new_GetCreateMob->Affect[i].Time = mBuffer[new_GetCreateMob->ClientId].Affects[i].Time; 

		st_Item item = thisMob->Equip[i];			

		WORD itemIDEF = GetItemIDEF(&item, i == 14);
		BYTE anctCode = GetAnctCode(&item);
		memcpy(&new_GetCreateMob->ItemEff[i],  &itemIDEF, 2);	
		memcpy(&new_GetCreateMob->AnctCode[i], &anctCode, 1);
	}

	memcpy(&new_GetCreateMob->GuildIndex, &thisMob->GuildIndex, sizeof(unsigned short));

	if(thisMob->Equip[14].EFV1 > 127 || thisMob->Equip[14].EFV1 == -1) //bug da montaria morta
		new_GetCreateMob->ItemEff[14].ItemID = 0;

	memset(&new_GetCreateMob->Tab[0], 0xFF, 26);

	strncpy(&new_GetCreateMob->Tab[0], "", 26);

	if(def_GetCreateMob->ClientId <= MAX_PLAYER)
		strncpy(&new_GetCreateMob->Tab[0], wdBuffer[def_GetCreateMob->ClientId].Ingame.Tab, 26);

	memset(&new_GetCreateMob->Unknow[0], 0xCC, 4);
}

void FixRefreshItens_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	p36b_613 *def_36b = (p36b_613*)packetBuffer;
	p36b *new_36b = (p36b*)m_PacketBuffer;
	st_Mob* player = GetMobFromIndex(new_36b->Header.ClientId);
	
	memcpy(&new_36b->ItemEff, &def_36b, 32);
	memset(&new_36b->pAnctCode, 0x0, 16);

	for(int i = 0; i < 16; i++)
	{
		st_Item *item = &player->Equip[i];
		WORD itemIDEF = GetItemIDEF(item, i == 14);
		BYTE anctCode = GetAnctCode(item);

		memcpy(&new_36b->ItemEff[i], &itemIDEF, 2);	
		memcpy(&new_36b->pAnctCode[i], &anctCode, 1);
	}
}