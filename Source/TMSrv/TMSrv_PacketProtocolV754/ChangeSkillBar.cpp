#include "DLLMain.h"

void ChangeSkillBar(BYTE *m_PacketBuffer, bool *pRetn)
{
	p378 *p = (p378*)m_PacketBuffer;

	wdBase *player = &wdBuffer[p->Header.ClientId];

	// Salva os Slots das skils no player.
	memcpy(player->Chars[player->Ingame.LoggedMob].SkillBar2, p->SkillBar2, 16);

	SaveAccount(p->Header.ClientId);

	return;
}