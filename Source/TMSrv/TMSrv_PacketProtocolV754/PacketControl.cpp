#include "PacketControl.h"

bool SendPacketControl(BYTE* newPacketBuffer, PacketHeader* oldPacketBuffer, int clientId)
{
	// Para zerar um packet basta setar retn como true, 
	// O hook se encarregará do resto

	bool retn = false;
	switch(oldPacketBuffer->PacketId)
	{
		/*case 0x110: case 0x112:
			UpdateCharListStructure((st_CharList*)&newPacketBuffer[12], (BYTE*)newPacketBuffer);
			break;
			*/
		case 0x114:
			SendWorld((BYTE*)newPacketBuffer);
			break;

		case 0x336:
			FixSendScore_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			SendAffect(oldPacketBuffer->ClientId);
			break;

		case 0x337:
			FixSendEtc_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x338:
			FixSendExp_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x363:
			FixGetCreateMobTrade_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x364:
			FixGetCreateMob_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x36B:
			FixRefreshItens_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x37E:
			FixExitParty_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x36C:
		case 0x39D:
			FixSendAffect_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;

		case 0x39E:
			FixSendAffect39E_SERVER((BYTE*)newPacketBuffer, (BYTE*)oldPacketBuffer);
			break;			
				
		case 0x803:
			DoLogin((BYTE*)newPacketBuffer, &retn);
			break;	

		case 0x809:
			if (newPacketBuffer[12] >= 0 && newPacketBuffer[12] <= 3)
				strncpy(Users[oldPacketBuffer->ClientId].CharList.Name[newPacketBuffer[12]], "\0", 12);
			break;
	}
	    
	return retn;
}

bool RecvPacketControl(PacketHeader* packetBuffer, int clientId)
{
	// Para zerar um packet basta setar retn como true, 
	// O hook se encarregará do resto

	bool retn = false;

	switch(packetBuffer->PacketId)
	{
		case 0x20F:
		    CreateChar((BYTE*)packetBuffer, &retn);
		    break;

		case 0x213:
			memset((BYTE*)&packetBuffer[20], 0x0, 36 - 20);					
			break;

		case 0x277:
			FixAddPoint_CLIENT((BYTE*)packetBuffer, &retn);
			break;

		case 0x28B:
			UseNpcs((BYTE*)packetBuffer, &retn);
			break;			

		case 0x2E1:
			SkillAlchemy((BYTE*)packetBuffer, &retn);
			break;

		case 0x334:
			Commands((BYTE*)packetBuffer, &retn);
			break;

		case 0x373:
			UseItens((BYTE*)packetBuffer, &retn);
			break;

		case 0x374:
		{
			if((int*)&packetBuffer[14])
				retn = true;
		}
		break;

		case 0x376:
			VerifyItemMovement((BYTE*)packetBuffer, &retn);
			break;

		case 0x378:
			ChangeSkillBar((BYTE*)packetBuffer, &retn);
			break;

		case 0x379:
			FixBuyItem_SERVER((BYTE*)packetBuffer, &retn);
			break;

		case 0x37A:
			Control37A((BYTE*)packetBuffer, &retn);
			break;

		case 0x37E:
			FixExitParty_CLIENT((BYTE*)packetBuffer);
			break;

		case 0x39D:
		case 0x36C:
			FixSendAffect_CLIENT((BYTE*)packetBuffer, &retn);
			break;

		case 0x398:
			Control398((BYTE*)packetBuffer, &retn);
			break;

		case 0x39E:
			FixSendAffect39E_CLIENT((BYTE*)packetBuffer, &retn);
			break;		

		case 0x3D5:
			RecruitPerson((BYTE*)packetBuffer, &retn);
			break;	

		case 0x272:
			{
				if(wdBuffer[packetBuffer->ClientId].Ingame.RetectItem)
				{
					retn = true;

					SendClientMsg(packetBuffer->ClientId, "Aguarde mais %d segundo(s) e tente novamente.", wdBuffer[packetBuffer->ClientId].Ingame.RetectItem);

					return retn;
				}

				wdBuffer[packetBuffer->ClientId].Ingame.RetectItem = 10;

			}
			break;

		case 0x28E:
		case 0x28F:
			ReceiveBets((BYTE*)packetBuffer, &retn);
			break;

		case 0x3BA:
		    Agatha((BYTE*)packetBuffer, &retn);
		    break;

		case 0x3C0:
			Tiny((BYTE*)packetBuffer, &retn);
			break;

		case 0x2C3:
			Lindy((UINT8*)packetBuffer, &retn);
			break;

		case 0x2C4:
			Shany((BYTE*)packetBuffer, &retn);
			break;

		case 0x2D3:
			Ehre((BYTE*)packetBuffer, &retn);
			break;
				
		case 0x3B5:
			Ailyn((BYTE*)packetBuffer, &retn);
			break;

		case 0x2D2:
			Odin((BYTE*)packetBuffer, &retn);
			break;

		case 0x366:
			MovePlayer((BYTE*)packetBuffer, &retn);
			break;

		case 0x3A6://0x3A6 _MSG_CombineItem
		    Compounder((BYTE*)packetBuffer, &retn);
            break;
	}

	return retn;
}

void __stdcall HKD_CorrectRecvPacket(UINT8* szBuffer, INT32 FixClientID)
{
	PacketHeader *Header = (PacketHeader*)szBuffer;

	Header->ClientId = FixClientID; // Proteção contra hacks baseados em mudar o clientid

	if(Header->PacketId == 0x39D || Header->PacketId == 0x39E || Header->PacketId == 0x367)
		if(Header->TimeStamp == 0x0E0A1ACA) // Proteção contra speed
			Header->PacketId = 0;

	switch(Header->PacketId)
	{

		case 0xFDE:
			Numerica((BYTE*)szBuffer);
			break;
	}
}