#include "DLLMain.h"

void RegenMob(int User)
{
	if (User <= 0 || User >= MAX_PLAYER)
		return;

	char temp[1024];

	st_Mob *player = GetMobFromIndex(User);

	int GuildID = player->GuildIndex;
	
	Users[User].CharLoginTime++;

	if(!Users[User].CharLoginTime % 450)
	{
		int Frag = GetPKPoint(User);

		if (Frag < 75)
		{
			Frag++;

			SetPKPoint(User, Frag);

			sprintf(temp, "Chaos Point aumentaram! [%d] [%d]", Frag - 75, 1);
			SendClientMessage(User, temp);
		}

		st_Item *MountBufferItem = &player->Equip[14];

		if(MountBufferItem->Index >= 2300)
		{
			if(MountBufferItem->Index < 2330)
			{
				int Delay = BASE_GetBonusItemAbility(MountBufferItem, EF_INCUDELAY);

				if(Delay > 0)
				{
					Delay--;

					MountBufferItem->EFV3 = Delay;

					SendItem(User, EQUIP, 14, &player->Equip[14]);

					SendClientMessage(User, (char*) 0x7D88D8);
				}
			}
		}

		if(MountBufferItem->Index >= 2330 && MountBufferItem->Index < 2390 && MountBufferItem->EF1 > 0)
		{
			int v44 = MountBufferItem->EF3;

			int v48 = (MountBufferItem->Index - 2330) % 30;

			if (v48 <= 15)
				v44 -= 2;
			else
				v44 -= 4;

			if (v44 <= 1)
			{
				MountBufferItem->EF1 = 0;
				MountBufferItem->EF3 = 4;

				SendClientMessage(User, (char*) 0x7D89D8);

				st_Item *Src50;

				memcpy(Src50, MountBufferItem, sizeof(st_Item));

				BYTE v4A = 0;

				if (MountBufferItem->Index >= 2360 && MountBufferItem->Index < 2390)
					ProcessAdultMount(User, 0);
				if (MountBufferItem->Index < 2360)
					MountProcess(User, Src50);
				else
					GetCurrentScore(User);
			}
			else
				MountBufferItem->EF3 = v44;

			SendItem(User, EQUIP, 14, &player->Equip[14]);
		}
	}

	int Guilty = GetGuilty(User);

	if(Guilty > 0)
	{
		Guilty--;

		SetGuilty(User, Guilty);

		if(!Guilty)
		{
			p613_GetCreateMob m;

			GetCreateMob(User, (BYTE*) &m);

			GridMulticast_OL2(player->TargetX, player->TargetY, (BYTE*) &m, 0);

			for(int s = 1000; s < 30000; s++)
			{
				st_Mob *mob = GetMobFromIndex(s);

				if(mob->Mode != 5)
					continue;
				if(mob->CapeInfo != 4)
					continue;

				if(mob->CurrentTarget == User)
				{
					mob->CurrentTarget = 0;
					mob->Mode = 4;
				}

				for(int l = 0; l < 4; l++)
				{
					if(mob->EnemyList[l] != User)
						continue;

					mob->EnemyList[l] = 0;
					mob->Mode = 4;
				}
			}
		}
	}

	int vCC = 100;
	int vD0 = 10;

	int vD4 = GetAttribute(player->TargetX,player->TargetY);

	LOBYTE(vD4);


	if(vD4 & 1)
	{
		vCC = 200;
		vD0 = 20;
	}
	if(vD4 & 8 || vD4 & 32)
	{
		vCC = 400;
		vD0 = 50;
	}
	else
	{
		if((BYTE)&player->AffectInfo & 16)
		{
			int vD8 = player->Status.Mastery[1];

			vD8 /= 10;

			if (vD8 < 0)
				vD8 = 0;
			if (vD8 > 20)
				vD8 = 20;

			vCC = vD8 + 110;
			vD0 = 20;
		}
	}

	if(player->Mode)
	{
		if(player->Status.curHP > 0)
		{
			if(User >= 1000 || Users[User].Status == 22)
			{
				UINT32 maxHP = player->Status.maxHP;
				UINT32 maxMP = player->Status.maxMP;
				UINT32 curHP = player->Status.curHP;
				UINT32 curMP = player->Status.curMP;

				int calcRegenHPMP = player->RegenHP;

				calcRegenHPMP = calcRegenHPMP * vCC / 100;

				int calcRegenHP = maxHP * calcRegenHPMP / 120 + vD0;

				curHP = curHP + calcRegenHP;

				if(User <= 750)
				{
					if(player->Equip[0].EFV2 == ARCH)
						curHP += (maxHP / 100) * 5;
					else if(player->Equip[0].EFV2 >= CELESTIAL)
						curHP += (maxHP / 100) * 10;
				}

				if(curHP > maxHP)
					curHP = maxHP;

				calcRegenHPMP = player->RegenMP;

				calcRegenHPMP = calcRegenHPMP * vCC / 100;

				int calcRegenMP = maxMP * calcRegenHPMP / 120 + vD0;

				curMP = curMP + calcRegenMP;

				if(User <= MAX_PLAYER)
				{
					if(player->Equip[0].EFV2 == ARCH)
						curMP += (maxMP / 100) * 5;
					else if(player->Equip[0].EFV2 >= CELESTIAL)
						curMP += (maxMP / 100) * 10;
				}

				if(curMP > maxMP)
					curMP = maxMP;

				if(curMP > 32000)
					curMP = 32000;
				if(curHP > 32000)
					curHP = 32000;

				player->Status.curHP = curHP;
				player->Status.curMP = curMP;

				BYTE pSend[20];

				*(WORD*)&pSend[0] = 20;
				*(WORD*)&pSend[4] = 0x181;
				*(WORD*)&pSend[6] = User;

				*(WORD*)&pSend[12] = curHP;
				*(WORD*)&pSend[14] = curMP;

				SetReqHp(User);
				SetReqMp(User);

				*(WORD*)&pSend[16] = Users[User].Potion.CountHp;
				*(WORD*)&pSend[18] = Users[User].Potion.CountMp;

				int TargetX = Users[User].nTargetX;
				int TargetY = Users[User].nTargetY;

				GridMulticast_OL2(TargetX, TargetY, (BYTE*) &pSend, 0);
			}
		}
	}
}