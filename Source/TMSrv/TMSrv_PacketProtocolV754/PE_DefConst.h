// ---
// by ptr0x
// ---

#ifndef __PE_DEF_CONST_H__
#define __PE_DEF_CONST_H__

#include <Windows.h>
#include "../../Common/DefaultEncDecInfoV754.h"
#include "DLLMain.h"

void SetDefaultConstants();
void SetVersion();
void SetEncDec();
void SetSkillDataString();
void SetSkillIndex();
void SetMobIndex();
void SetSockAddrPorts();
void SetPacketSize();
void ChangeItemlistStructPointer();
void CorrectAffectSize();
void TranslateBaseNPCFiles();
void RedirectCUserBuffer();
void ChangeLimitAffects();
void ChangeMountStatus();
void ChangeTransBonusStructurePointer();
void NPCGenerLimit();
void FixBonusExp();
void SetNewHpMpSize();
void ChangeHpMpStructurePointer();

#endif // __PE_DEF_CONST_H__