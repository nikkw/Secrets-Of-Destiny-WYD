#include "DLLMain.h"

void MovePlayer(BYTE* m_PacketBuffer, bool *pRetn)
{
	p366 *p = (p366*)m_PacketBuffer;

	if(p->Header.ClientId < 1 || p->Header.ClientId > MAX_PLAYER)
		return;
	if(p->xDst > 4096 || p->xDst < 0 || p->xSrc > 4096 || p->xSrc < 0)
		return;
	if(p->yDst > 4096 || p->yDst < 0 || p->ySrc > 4096 || p->ySrc < 0)
		return;

	st_Mob *player = GetMobFromIndex(p->Header.ClientId);

	int CityId = player->Info.CityID,
		cId = p->Header.ClientId;

	if(p->xSrc >= MaxMinCoordsGuilds[CityId][0] && p->xSrc <= MaxMinCoordsGuilds[CityId][2] &&
	   p->ySrc >= MaxMinCoordsGuilds[CityId][1] && p->ySrc <= MaxMinCoordsGuilds[CityId][3] &&
	   !wdBuffer[cId].Ingame.isAdmin)
	{
		if(!War.Owner[CityId])
		{
			DoTeleport(cId, CoordsReturnArea[CityId][0] + (Rand() % 5), CoordsReturnArea[CityId][1] + (Rand() % 5));

			SendClientMessage(cId, "Necessário dominar esta cidade antes.");

			return;
		}
		else if(player->GuildIndex != War.Owner[CityId])
		{
			DoTeleport(cId, CoordsReturnArea[CityId][0] + (Rand() % 5), CoordsReturnArea[CityId][1] + (Rand() % 5));

			SendClientMessage(cId, "Somente membros da guild dominante podem entrar.");

			return;
		}
	}
}