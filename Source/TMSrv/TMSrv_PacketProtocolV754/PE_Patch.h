// ---
// by ptr0x
// ---

#ifndef __PE_PATCH_H__
#define __PE_PATCH_H__

#include <Windows.h>

#include "AddMessage.h"
#include "ReadMessage.h"
#include "MobKilled.h"

#include "../../Common/PE_Hook.h"
#include "../../Common/st_Base.h"

void DoIndirections();
void ChangeItemlistStructurePointer();

// CPSock
void CPSockIndirections();
void NKD_AddMessage();
void NKD_ReadMessage();
void NKD_AddMessage_EncKey_1();
void NKD_ReadMessage_DecKey_1();
void NKD_ReadMessage_DecKey_2();
void NKD_DisableUnkPacket();
void NKD_DisableCheckPacket();
void NKD_CloseUser();

// Server
void NKD_ProcessClientMessage_UseMountFeed();
void NKD_StandingByProcessor_VerifyAbility_1();
void NKD_GetCurrentScore_VerifyAbility_1();
void NKD_GenerateSummon_CanSummon();
void NKD_MobKilled_DropGold();
void NKD_MobKilled_EventDead();
void NKD_MobKilled_ControlDropItem();
void NKD_GetDoubleCritical_SetNewCriticalRate();
void NKD_GetGetCurrentScore_FixCriticalRate();
void NKD_GetMobAbility_Spectral();
//void NKD_GetCurrentScore();
void NKD_CorrectRefs();
void NKD_CorrectDamageCele();
void SkillLvCele();
void NKD_ProcessClientMessage_ReadCommand();
void Fix_IntegerDivisionByZero();
void __stdcall ZeroAffect(UINT16 ClientID);
void CheckAffects();
void FixAffects();
void RemoveAffects();
void GetBuffer();
void AfterAffects();
void NKD_ProcessClientMessage_ApplyBonus();
void NKD_CorrectRecvPacket();
void NKD_BASE_GetBonusSkillPoint();
void NKD_FixMaxLevel_CheckGetLevel();
void NKD_FixMaxLevel_MobKilled();
void NKD_FixMaxLevel_ProcessClientMessage();
void NKD_FixMaxLevel_ProcessDBMessage();
void NKD_ControlCheckGetLevel();
void NKD_CheckGetLevel_FixClass();
void NKD_CorrectPositionGoWorld();
void NKD_CorrectSleip();
void NKD_Base_GetCurrentScore_FixEdenStatus();
void NKD_ControlTeleportPosition();
void NKD_RegenMob_FixCancel();
void NKD_FixTrainningCamp();
void NKD_GetCurrentScore_SancTransform();
void NKD_Base_GetCurrentScore_FixTrans();
void NKD_Base_GetCurrentScore_FixFaceArch();
void HKD_SaveUser(INT32 clientid, bool reason);
void NKD_ProcessClientMessage_ControlEXP();
void NKD_ProcessDBMessage_LoadBuffs();
void NKD_GetParryRate_FixEvasion();
void NKD_GetParryRate_FixEvasion_2();
void NKD_ExpInPesaAllArea();
void NKD_BASE_GetCurrentScore_BlockStatus();
void NKD_MobKilled_ControlExp();
void NKD_MobKilled_FixClassExp();
void NKD_BASE_CanEquip_REQ_SIDC();
void NKD_BASE_CanEquip_VerifClassInfo();

void NKD_ProcessClientMessage_ProcessAttack();
void NKD_ProcessClientMessage_ProcessAttack_Visual();

void NKD_RegenMob_FixHP();

void NKD_ProcessClientMessage_Command();
void NKD_ProcessClientMessage_KickPlayer();

void NKD_NewTrade();

void NKD_ChangeDamage_1();
void NKD_ChangeDamage_2();
void NKD_ChangeDamage_3();

void NKD_ProcessSecTimer_CorrectHpMpLimit_1();
void NKD_ProcessSecTimer_CorrectHpMpLimit_2();
void NKD_ProcessClientMessage_CorrectHpMpLimit_3();
void NKD_ProcessClientMessage_CorrectHpMpLimit_4();
void NKD_ProcessClientMessage_CorrectHpMpLimit_5();
void NKD_ProcessClientMessage_CorrectHpMpLimit_6();
#endif // __PE_PATCH_H__