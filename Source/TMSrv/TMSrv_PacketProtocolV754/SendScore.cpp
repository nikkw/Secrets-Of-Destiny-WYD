#include "SendScore.h"

void FixSendScore_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer)
{
	p754_SendScore *new_SendScore = (p754_SendScore*)m_PacketBuffer;
	p613_SendScore *def_SendScore = (p613_SendScore*)packetBuffer;

	st_Mob *player = GetMobFromIndex(new_SendScore->Header.ClientId);
	
	for(int i = 0; i < 16; i++) 
	{
		new_SendScore->Affect[i].Index = mBuffer[new_SendScore->Header.ClientId].Affects[i].Index;
		new_SendScore->Affect[i].Time = mBuffer[new_SendScore->Header.ClientId].Affects[i].Time;
	}
		
	memcpy(&new_SendScore->GuildMemberType, &def_SendScore->GuildMemberType, 18);
	memcpy(&new_SendScore->Status, &player->Status, sizeof(st_Status));
	memset(&new_SendScore->Unk[0], 0x0, 5);		

	new_SendScore->CurrHP = player->Status.curHP;
	new_SendScore->CurrMP = player->Status.curMP;

	new_SendScore->RegenHP = player->RegenHP;
	new_SendScore->RegenMP = player->RegenMP;

	new_SendScore->Critical = player->Critical;	
	new_SendScore->MagicIncrement = player->MagicIncrement;		
}