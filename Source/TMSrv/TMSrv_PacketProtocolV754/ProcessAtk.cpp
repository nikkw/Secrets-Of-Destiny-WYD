#include "DLLMain.h"

static const INT8 Merchants[] = {1,2,8,19,30,42,43};

int __stdcall HKD_ChangeDamage(DWORD attacked, DWORD attacker, DWORD Damage)
{	
	st_Mob *player = (st_Mob*)GetMobFromIndex(attacker),
		   *mob    = (st_Mob*)GetMobFromIndex(attacked);

	for(int i = 0; i < 7; i++)
		if(mob->Info.Merchant == Merchants[i])
			return 0;

	// Itens de divisão de hp
	int hpDef = 0;

	if(mob->Equip[13].Index == 786)
		hpDef = 2;
	else if(mob->Equip[13].Index == 1936)
		hpDef = 10;
	else if(mob->Equip[13].Index == 1937)
		hpDef = 20;

	if(hpDef) 
	{
		int sanc = BASE_GetItemSanc(&mob->Equip[13]);

		if(sanc < 2)
			sanc = 2;

		sanc *= hpDef;
		Damage /= sanc;
	}

	/*if (wdBuffer[attacker].Ingame.HpExtract > 0)
	{
		int bonuseHp = (Damage * wdBuffer[attacker].Ingame.HpExtract) / 10000;

		if (player->Status.curHP + bonuseHp > player->Status.maxHP)
			bonuseHp = player->Status.maxHP - player->Status.curHP;

		player->Status.curHP += bonuseHp;
		Users[attacker].Potion.CountHp += bonuseHp;

		p18A p;
		memset(&p, 0, sizeof p18A);

		p.Header.ClientId = attacker;
		p.Header.PacketId = 0x18A;
		p.Header.Size = sizeof p18A;

		p.CurHP = player->Status.curHP;
		p.Incress = bonuseHp;

		SetReqHp(attacker);

		int TargetX = Users[attacker].nTargetX;
		int TargetY = Users[attacker].nTargetY;

		GridMulticast_OL2(TargetX, TargetY, (BYTE*)&p, 0);
	}
	if (wdBuffer[attacker].Ingame.MpExtract > 0)
	{
		int	bonuseMp = (Damage * wdBuffer[attacker].Ingame.MpExtract) / 10000;

		if (player->Status.curMP + bonuseMp > player->Status.maxMP)
			bonuseMp = player->Status.maxMP - player->Status.curMP;

		player->Status.curMP += bonuseMp;
		Users[attacker].Potion.CountMp += bonuseMp;

		SetReqMp(attacker);

		SendScore(attacker);
	}
	*/

	if(attacked <= 750)
	{
		for(int i = 0; i < 16; i++)
		{
			if(mBuffer[attacked].Affects[i].Index == 18)
			{
				UINT16 manaSpent = (Damage / 100) * 70;

				if(manaSpent > mob->Status.curMP)
					manaSpent = mob->Status.curMP;

				mob->Status.curMP -= manaSpent;
				Users[attacked].Potion.CountMp -= manaSpent;

				SetReqMp(attacked);
				SendScore(attacked);

				Damage -= manaSpent;
    
				break;
			}
		}
	}
	else if(attacker <= 750)
	{
		for(int i = 0; i < 16; i++)
		{
			if(mBuffer[attacker].Affects[i].Index == 30)
			{
				// Frango
				Damage += 2000;
				break;
			}
		}
	}

	if (Damage >= 30000)
		Damage = 30000;

	return Damage;
}