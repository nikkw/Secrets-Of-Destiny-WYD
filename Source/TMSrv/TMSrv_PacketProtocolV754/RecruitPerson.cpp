#include "DLLMain.h"

void RecruitPerson(UINT8* m_PacketBuffer, bool* pRetn)
{
	*pRetn = true;

	p3D5 *p  = (p3D5*)m_PacketBuffer;

	if(p->Header.ClientId < 0 || p->Header.ClientId > 750 ||
	   p->RecruitCid      < 0 || p->RecruitCid      > 750)
	   return;

	INT16 LidercId = p->Header.ClientId,
		  RecruitcId = p->RecruitCid;

	if(Users[p->RecruitCid].Status != 22)
		return;

	st_Mob *Lider  = GetMobFromIndex(LidercId),
		   *Member = GetMobFromIndex(RecruitcId);

	GetCurScore_CapeInfo(Lider);
	GetCurScore_CapeInfo(Member);

	if(Lider->Equip[12].Index != 509 && (Lider->Equip[12].Index < 526 || Lider->Equip[12].Index > 528))
	{
		SendClientMessage(LidercId, "Para recrutar é necessário ser Lider ou SubLider.");

		//SendLog(Users[LidercId].Username, "%s tentou recrutar %s sem ser lider e sub.", Lider->Name, Member->Name);

		return;
	}
	else if(Member->Equip[12].Index)
	{
		SendClientMessage(LidercId, "Este jogador já tem guild.");

		//SendLog(Users[LidercId].Username, "%s tentou recrutar %s que já possuia guild.", Lider->Name, Member->Name);

		return;
	}
	else if(Member->CapeInfo != Lider->CapeInfo)
	{
		SendClientMessage(LidercId, "Jogador deve pertencer ao mesmo reino para ser recrutado.");

		//SendLog(Users[LidercId].Username, "%s tentou recrutar %s que era de outro reino.", Lider->Name, Member->Name);

		return;
	}

	if(Lider->Gold < 4000000)
	{
		SendClientMessage(LidercId, "São necessários 4.000.000 (4 Milhões) de gold para recrutar.");

		//SendLog(Users[LidercId].Username, "%s tentou recrutar %s sem os 4kk de pagamento.", Lider->Name, Member->Name);

		return;
	}

	if(Guilds[Lider->GuildIndex].Members > 64000)
	{
		SendClientMessage(LidercId, "Sua guild já atingiu o tamanho máximo.");

		//SendLog(Users[LidercId].Username, "%s tentou recrutar %s mas a guild já estava no tamanho máximo.", Lider->Name, Member->Name);

		return;
	}

	Guilds[Lider->GuildIndex].Members++;

	Lider->Gold -= 4000000;

	memcpy(&Member->GuildIndex, &Lider->GuildIndex, sizeof(unsigned short));
	memcpy(&Member->Equip[12],  &Lider->Equip[12],  sizeof st_Item);

	Member->Equip[12].Index = 508;

	SendItem(RecruitcId, EQUIP, 12, &Member->Equip[12]);

	SendScore(LidercId);
	SendScore(RecruitcId);
	SendEtc(LidercId);
	SendEtc(RecruitcId);

	BYTE packet[108]; 

	BASE_GetCreateMob(RecruitcId, (BYTE*)&packet);
	GridMulticast(RecruitcId, Member->TargetX, Member->TargetY, (void*)&packet);

	SendCreateMob(RecruitcId, RecruitcId, 1);

	char szMsg[108];
	sprintf_s(szMsg, "! Bem vindo a guild %s!!", Guilds[Lider->GuildIndex].GuildName);
	SendClientMessage(p->RecruitCid, szMsg);

	sprintf(szMsg, "Jogador %s acaba de entrar para a guild.", Member->Name);

	//SendLog(Users[RecruitcId].Username, szMsg);
	UpdateMGuildInfo(Lider->GuildIndex);

	for(int i = 0; i < 750; i++)
	{
		st_Mob *tmp = GetMobFromIndex(i);

		if(tmp->GuildIndex == Lider->GuildIndex)
			sD1D(0x7530, i, szMsg, 0xFF00BFFF);
	}
}