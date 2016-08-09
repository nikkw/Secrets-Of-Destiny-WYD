// ---
// by ptr0x
// ---

#ifndef __FIX_SEND_ETC_H__
#define __FIX_SEND_ETC_H__

#include "../../Common/st_Base.h"

#pragma region Packet Struct v613
typedef struct 
{
	PacketHeader Header;

	DWORD Exp;
	DWORD Learn;

	WORD pStatus;
	WORD pMaster;
	WORD pSkills;
	WORD Magic; // Unknow

	DWORD Gold;
} p613_SendEtc;
#pragma endregion

#pragma region Packet Struct v754
typedef struct 
{
	PacketHeader Header;

	DWORD Hold;
	DWORD Exp;
	DWORD Learn;

	WORD pStatus;
	WORD pMaster;
	WORD pSkills;
	WORD Magic; // Unknow

	DWORD Gold;
} p754_SendEtc;
#pragma endregion

void FixSendEtc_SERVER(BYTE *m_PacketBuffer, BYTE *packetBuffer);

#endif // __FIX_SEND_ETC_H__