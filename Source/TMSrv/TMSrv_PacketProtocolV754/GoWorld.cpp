#include "DLLMain.h"

void SendWorld(BYTE *m_PacketBuffer)
{
	memset(&m_PacketBuffer[788], 0x0, 1244 - 788);

	p114 *p = (p114*)m_PacketBuffer;

	short clientId = *(short*)&m_PacketBuffer[774];

	wdBase *player = &wdBuffer[clientId];

	if(clientId < 1 || clientId > MAX_PLAYER)
		return;

	player->Ingame.LoggedMob = p->SlotIndex;

	memcpy(p->SkillBar2, player->Chars[player->Ingame.LoggedMob].SkillBar2, 16);

	p->Hold = 0x0;

	if(!player->Ingame.canLog)
	{
		CloseUser(clientId);

		return;
	}
	else if(p->GuildIndex)
		UpdateGuildInfo(clientId);

	//SendLog(Users[clientId].Username, "%s acessou o mundo.", p->Name);
}