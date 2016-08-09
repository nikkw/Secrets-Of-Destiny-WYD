#include "SendAffect.h"

void FixSendAffect_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	*(DWORD*)&m_PacketBuffer[44] = *(DWORD*)&packetBuffer[40];

	*(DWORD*)&m_PacketBuffer[40] = 0x0;
}

void FixSendAffect_CLIENT(BYTE *m_PacketBuffer, bool* pRetn)
{
	PacketHeader *p = (PacketHeader*)m_PacketBuffer;		
		
	if(p->ClientId < 750)
		FixUseSkill((BYTE*)m_PacketBuffer, pRetn);

	*(DWORD*)&m_PacketBuffer[40] = *(DWORD*)&m_PacketBuffer[44];
	*(DWORD*)&m_PacketBuffer[44] = 0x0;
}

void FixUseSkill(BYTE *m_PacketBuffer, bool* pRetn)
{
	p39D_754 *p = (p39D_754*)m_PacketBuffer;

	INT16 cId = p->Header.ClientId;

	p754_SendAffect *oldp = (p754_SendAffect*)m_PacketBuffer;

	INT16 oldcId = oldp->Header.ClientId;

	st_Mob *player = GetMobFromIndex(oldcId);	

	if(p->m_SkillId == 103) // Skill Kefra sem ser mob
	{
		*pRetn = true;

		CloseUser(cId);
		
		return;
	}		

	else if(!p->m_SkillId) // Se não for skill 
		return;	

	if(p->Header.PacketId == 0x36C && p->m_SkillId == 79)
	{
		OitavaHT(cId, p->m_Target.Index);

		*pRetn = true;

		return;
	}
		
	switch(p->m_SkillId)
	{
		case 27: case 29:
			*(DWORD*)&m_PacketBuffer[12] = 0x0;
			break;

		case 31: // Renascimento
		{
			*pRetn = true;

			if(cId == p->m_Target.Index)
				return;
			else if(p->m_Target.Index < 0 || p->m_Target.Index > 750)
				return;
				
			bool HasOnGroup = false;

			if(player->Leader <= 0) // Lider do grupo ou sem grupo
			{
				for(int i = 0; i < 12; i++)
				{
					if(player->PartyList[i] == p->m_Target.Index)
					{
						HasOnGroup = true;
						break;
					}
				}
			}
			else if(player->Leader != -1)
			{
				st_Mob *leader = GetMobFromIndex(player->Leader);

				for(int i = 0; i < 12; i++)
				{
					if(leader->PartyList[i] == p->m_Target.Index)
					{
						HasOnGroup = true;
						break;
					}
				}
			}

			if(!HasOnGroup)
				return;

			st_Mob *deadPerson = GetMobFromIndex(p->m_Target.Index);

			if(deadPerson->Status.curHP > 0)
				return;
			if(!player->Status.curHP || !player->Status.curMP)
				return;

			deadPerson->Status.curHP = deadPerson->Status.maxHP / 2;
			deadPerson->Status.curMP = deadPerson->Status.maxMP / 2;

			deadPerson->bStatus.curHP = deadPerson->bStatus.maxHP / 2;
			deadPerson->bStatus.curMP = deadPerson->bStatus.maxMP / 2;

			Users[p->m_Target.Index].Potion.CountMp = deadPerson->Status.curMP;
			Users[p->m_Target.Index].Potion.CountHp = deadPerson->Status.curHP;

			player->Status.curMP = 0;
			player->bStatus.curMP = 0;

			Users[cId].Potion.CountMp = player->Status.curMP;
				
			GetCurrentScore(p->m_Target.Index);

			BASE_GetHpMp(deadPerson);

			SendScore(p->m_Target.Index);
			SendCreateMob(p->m_Target.Index, p->m_Target.Index, 1);

			DoTeleport(p->m_Target.Index, deadPerson->PosX, deadPerson->PosY);

			break;
		}

		case 56: case 57: case 58: 
		case 59: case 60: case 61: 
		case 62: case 63: 
		{
			*pRetn = true;

			UINT8 summonId = p->m_SkillId - 56; 

			static const UINT8 MobDivisor[8] = {31, 36, 42, 51, 63, 85, 127, 255};

			if(!player->Leader || player->Leader == -1)
			{
				for(int i = 0; i < 12; i++)
				{
					if(player->PartyList[i] <= 0)
						continue;

					st_Mob *tmpMob = GetMobFromIndex(player->PartyList[i]);

					for(int e = 0; e < 8; e++)
					{
						if(tmpMob->Equip[0].Index == MobFaces[e]) 
						{
							if(tmpMob->Summoner != p->Header.ClientId)
								return;

							RemoveParty(player->PartyList[i]);
							SendRemoveParty(player->Leader, player->PartyList[i]);
						}
					}
				}
			}
			else // Não é o lider do grupo
			{
				st_Mob *Lider = GetMobFromIndex(player->Leader);

				for(int i = 0;i<12;i++)
				{
					if(Lider->PartyList[i] == cId)
						continue;

					if(Lider->PartyList[i] <= 0)
						continue;

					st_Mob *tmpMob = (st_Mob*)GetMobFromIndex(Lider->PartyList[i]);
						
					for(int e = 0; e < 8; e++)
					{
						if(tmpMob->Equip[0].Index == MobFaces[e]) 
						{
							if(tmpMob->Summoner != p->Header.ClientId)
							    return;

							RemoveParty(Lider->PartyList[i]);
							SendRemoveParty(Lider->Leader, Lider->PartyList[i]);
						}
					}
				}
			}

			// Essa conta pega o número de mobs que a skill deve criar
			INT16 numMob = player->Status.Mastery[2] / MobDivisor[summonId];

			if(!numMob)
				numMob += 1;

			for(int i = 0; i < numMob; i++)
				GenerateSummon(cId, summonId, 0);

			break;
		}

		case 64: case 66: case 68: 
		case 70: case 71:
		{
			if(player->Equip[13].Index > 4151 && player->Equip[13].Index < 4159)
			{
				// Está de traje
				SendClientMessage(cId, "Impossível utilizar esta skill enquanto trajado.");

				*pRetn = true;

				return;
			}

			break;
		}

		////case 98: // Vinha - Skill sephira
		////	CreateMob("Vinha", oldp->PositionFinal.X, oldp->PositionFinal.Y, "npc");
		////	break;

		case 99: // Ressureição - Skill sephira
		{
			*pRetn = true;

			INT16 Level = player->bStatus.Level + 1;

			if(player->Equip[0].EFV2 > ARCH)
				Level += 200;

			INT8 resChances = Level / 5;

			if(wdBuffer[cId].Ingame.hasFailed)
				return;

			srand(time(NULL) / 5 * (rand() % 500) * 5);

			if(rand() % 100 <= resChances)
			{
				player->Status.curHP = player->Status.maxHP / 2;
				player->Status.curMP = player->Status.maxMP / 2;
				player->bStatus.curHP = player->bStatus.maxHP / 2;
				player->bStatus.curMP = player->bStatus.maxMP / 2;

				GetCurrentScore(cId);

				BASE_GetHpMp(player);

				SendScore(cId);
				SendCreateMob(cId, cId, 1);
			}
			else
				if(!wdBuffer[cId].Ingame.hasFailed)
					wdBuffer[cId].Ingame.hasFailed = 200;
				
			break;
		}

		case 102: // Soul - Melhor buff ever
		{
			*pRetn = true;

			if(player->Equip[0].EFV2 == ARCH)
				return;

			bool hasSoulOn = false;

			for(int i = 0; i < 16; i++)
				if(mBuffer[cId].Affects[i].Index == 29)
				{
					hasSoulOn = true;
					mBuffer[cId].Affects[i].Master = wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].SoulInfo;
					mBuffer[cId].Affects[i].Time = 139;
					mBuffer[cId].Affects[i].Value = 4;
					break;
				}

			if(!hasSoulOn)
			{
				for(int i = 0; i < 16; i++)
					if(!mBuffer[cId].Affects[i].Index)
					{
						mBuffer[cId].Affects[i].Index = 29;
						mBuffer[cId].Affects[i].Master = wdBuffer[cId].Chars[wdBuffer[cId].Ingame.LoggedMob].SoulInfo;
						mBuffer[cId].Affects[i].Time = 139;
						mBuffer[cId].Affects[i].Value = 4;
						break;
					}
			}				

			GetCurrentScore(cId);
			SendStats(cId);
			SendScore(cId);				
			break;
		}
	}
}

void SkillAlchemy(UINT8 *m_PacketBuffer, bool *pRetn)
{
	*pRetn = true;

	st_Window *pServer = (st_Window*)m_PacketBuffer;

	INT16 cId = pServer->Header.ClientId;

	if(cId <= NULL || cId >= MAX_PLAYER)
		return;

	st_Mob *player = GetMobFromIndex(cId);

	if(pServer->Slot[0] == 0xFF || pServer->Slot[1] == 0xFF || pServer->Slot[2] == 0xFF)
		SendClientMessage(cId, "Coloque os três itens necessários.");
	else
	{
		for(char i = 0; i < 3; i ++)		
		{
			if(memcmp(&pServer->ItemId[i], &player->Inventory[pServer->Slot[i]], sizeof st_Item))
				return;

			else if(pServer->ItemId[i].Index != player->Inventory[pServer->Slot[i]].Index)
				return;
		}		
		
		Composition(pServer, player);

		SendClientSignalParm(cId, 0x7530, 0x3A7, 2);
	}
}

void OitavaHT(int ClientID, int OtherID)
{
    st_Mob *player = (st_Mob*) GetMobFromIndex(ClientID);
    st_Mob *mob = (st_Mob*) GetMobFromIndex(OtherID);

    p36C p;
    memset(&p, 0, sizeof p36C);
 
    p.Header.ClientId = 30000;
    p.Header.Size = sizeof p36C;
    p.Header.PacketId = 0x36C;
 
	p.m_AffectedPosition.X = mob->TargetX;
    p.m_AffectedPosition.Y = mob->TargetY;
    p.m_AttackerPosition.X = player->TargetX;
    p.m_AttackerPosition.Y = player->TargetY;
 
    p.m_ClientId = ClientID;
 
    p.m_CurrentExp = player->Exp;
 
    p.m_FlagLocal = 1;
    p.m_Motion = -1;
    p.m_SkillId = 79;
 
    for(int i = 0;i < 8;i++)
    {
        INT32 parry = GetParryRate(mob, mob->Parry);
        INT32 randInterator = rand() % 1000;
 
        if(randInterator <= (parry / 2))
        {
            p.m_Target[i].Index = OtherID;
            p.m_Target[i].Damage = -1;
 
            continue;
        }
                       
        int RemoveDamage = BASE_GetDamage(player->Status.Attack, (OtherID <= MAX_PLAYER) ? (mob->Status.Defense << 1) : mob->Status.Defense, 0) / 2;
        int Damage = RemoveDamage;
 
		if(OtherID < 750)
        {
            RemoveDamage = Damage * 4 / 9;
 
            Damage = RemoveDamage;
        }

		Damage = HKD_ChangeDamage(OtherID, ClientID, RemoveDamage);
 
        if(mob->Status.curHP - Damage <= 0)
        {
            p.m_Target[i].Damage = Damage;
            p.m_Target[i].Index = OtherID;
 
            mob->Status.curHP = 0;

			Users[OtherID].Potion.CountHp = 0;

            break;
        }
        else
		{
            mob->Status.curHP -= Damage;

			Users[OtherID].Potion.CountHp -= Damage;
		}
 
        p.m_Target[i].Damage = Damage;
        p.m_Target[i].Index = OtherID;
    }
 
    p.m_CurrentMp = player->Status.curMP;
 
    GridMulticast(ClientID, player->TargetX, player->TargetY, &p);
 
    p.m_FlagLocal = 0;
 
    Sendpack((BYTE*)&p, ClientID, sizeof p36C);
       
    if(!mob->Status.curHP)
        MobKilled(OtherID, ClientID, 0, 0);
  
    SendScore(OtherID);
}

void FixSendAffect39E_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	if(*(WORD*)m_PacketBuffer < 50)
		return;

	*(DWORD*)&m_PacketBuffer[48] = *(DWORD*)&packetBuffer[44];
	*(DWORD*)&m_PacketBuffer[44] = *(DWORD*)&packetBuffer[40];
	*(DWORD*)&m_PacketBuffer[40] = 0x0;
}

void FixSendAffect39E_CLIENT(BYTE *m_PacketBuffer, bool* pRetn)
{
	if(*(WORD*)m_PacketBuffer < 50)
		return;

	*(DWORD*)&m_PacketBuffer[40] = *(DWORD*)&m_PacketBuffer[44];
	*(DWORD*)&m_PacketBuffer[44] = *(DWORD*)&m_PacketBuffer[48];
	*(DWORD*)&m_PacketBuffer[48] = 0x0;
}

void __stdcall SendAffect(UINT32 ClientID)
{
	if(ClientID < 0 || ClientID > MAX_PLAYER)
		return;

	p3B9 pack_3B9;

	pack_3B9.Header.PacketId = 0x3B9;
	pack_3B9.Header.Size = 140;
	pack_3B9.Header.ClientId = ClientID;

	memset(&pack_3B9.Affect[0], 0x0, 140 - 12);

	for (short i = 0; i <= 15; i++)
	{
		if (mBuffer[ClientID].Affects[i].Time > 10)
		{
			pack_3B9.Affect[i].Index = (BYTE)mBuffer[ClientID].Affects[i].Index;
			pack_3B9.Affect[i].Master = (BYTE)mBuffer[ClientID].Affects[i].Master;
			pack_3B9.Affect[i].Time = (DWORD)mBuffer[ClientID].Affects[i].Time;
			pack_3B9.Affect[i].Value = (WORD)mBuffer[ClientID].Affects[i].Value;
		}
	}

	Sendpack((BYTE*)&pack_3B9, ClientID, sizeof pack_3B9);
}