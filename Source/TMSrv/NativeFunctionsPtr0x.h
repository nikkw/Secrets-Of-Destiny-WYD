#ifndef __NATIVE_FUNCTIONS_H__
#define __NATIVE_FUNCTIONS_H__

#include "st_Base.h"

#define f_ptr (__cdecl *)
#define ITEM_SLOT_EQUIP 0
#define ITEM_SLOT_INVENTORY 1

#pragma region Server.obj
static void (*ClearCrown)(int)												= (void f_ptr(int)) 0x004013DE; // Lib: Server.obj Class : (null)
static int (*AddCrackError)(int,int,int)									= (int f_ptr(int,int,int)) 0x0040148D; // Lib: Server.obj Class : (null)
static int (*PutItem)(int clientID, st_Item* item)							= (int f_ptr(int clientID, st_Item* item)) 0x00401320; // Lib: Server.obj Class : (null)
static void (*GuildZoneReport)(void)										= (void f_ptr(void)) 0x00401109; // Lib: Server.obj Class : (null)
static struct HFONT__* (*GetAFont)(void)									= (struct HFONT__*f_ptr(void)) 0x004010BE; // Lib: Server.obj Class : (null)
static void (*ReadConfig)(void)												= (void f_ptr(void)) 0x004015F5; // Lib: Server.obj Class : (null)
static void (*DrawConfig)(int)												= (void f_ptr(int)) 0x0040119A; // Lib: Server.obj Class : (null)
static void (*AddFailAccount)(char*)										= (void f_ptr(char*)) 0x0040128F; // Lib: Server.obj Class : (null)
static int (*CheckFailAccount)(char*)										= (int f_ptr(char*)) 0x004014FB; // Lib: Server.obj Class : (null)
static int (*IsFree)(struct STRUCT_SELCHAR*)								= (int f_ptr(struct STRUCT_SELCHAR*)) 0x004012F3; // Lib: Server.obj Class : (null)
static int (*SendBilling)(int,char*,int,int)								= (int f_ptr(int,char*,int,int)) 0x004015D2; // Lib: Server.obj Class : (null)
static void (*SetItemBonus)(st_Item*,int,int,int)				= (void f_ptr(st_Item*,int,int,int)) 0x00401564; // Lib: Server.obj Class : (null)
static void (*ReadGuild)(void)												= (void f_ptr(void)) 0x00401154; // Lib: Server.obj Class : (null)
static void (*WriteGuild)(void)												= (void f_ptr(void)) 0x00401131; // Lib: Server.obj Class : (null)
static int (*Challange)(int,int,int)										= (int f_ptr(int,int,int)) 0x004015DC; // Lib: Server.obj Class : (null)
static int (*GenerateSummon)(int,int,struct STRUCT_ITEM*)					= (int f_ptr(int,int,struct STRUCT_ITEM*)) 0x004014CE; // Lib: Server.obj Class : (null)
static int (*CreateMob)(char*,int,int,char*)								= (int f_ptr(char*,int,int,char*)) 0x004013F7; // Lib: Server.obj Class : (null)
static void (*GenerateMob)(int,int,int)										= (void f_ptr(int,int,int)) 0x004011CC; // Lib: Server.obj Class : (null)
static void (*RebuildGenerator)(void)										= (void f_ptr(void)) 0x004013E3; // Lib: Server.obj Class : (null)
static int (*InitApplication)(void*)										= (int f_ptr(void*)) 0x0040139D; // Lib: Server.obj Class : (null)
static int (*InitInstance)(void*,int)										= (int f_ptr(void*,int)) 0x004010D7; // Lib: Server.obj Class : (null)
static struct _iobuf* (*WriteHeader)(char*)									= (struct _iobuf* f_ptr(char*)) 0x004012D0; // Lib: Server.obj Class : (null)
static void (*WriteArmor)(struct _iobuf*)									= (void f_ptr(struct _iobuf*)) 0x004012E9; // Lib: Server.obj Class : (null)
static void (*WriteWeapon)(struct _iobuf*)									= (void f_ptr(struct _iobuf*)) 0x004014D8; // Lib: Server.obj Class : (null)
static void (*BuildList)(void)												= (void f_ptr(void)) 0x004015E1; // Lib: Server.obj Class : (null)
static long (*MainWndProc)(struct HWND__*,unsigned int,unsigned int,long)	= (long f_ptr(struct HWND__*,unsigned int,unsigned int,long)) 0x00401190; // Lib: Server.obj Class : (null)
static int (*GetUserInArea)(int,int,int,int,char*)							= (int f_ptr(int,int,int,int,char*)) 0x00401348; // Lib: Server.obj Class : (null)
static void (*MountProcess)(int,struct STRUCT_ITEM*)						= (void f_ptr(int,struct STRUCT_ITEM*)) 0x0040135C; // Lib: Server.obj Class : (null)
static void (*LinkMountHp)(int)												= (void f_ptr(int)) 0x00401352; // Lib: Server.obj Class : (null)
static void (*ProcessAdultMount)(int,int)									= (void f_ptr(int,int)) 0x004015CD; // Lib: Server.obj Class : (null)
static void (*ProcessClientMessage)(int clientId, BYTE* packetBuffer)		= (void f_ptr(int, BYTE*)) 0x422100; // Lib: Server.obj Class : (null)
static void (*ProcessBILLMessage)(char*)									= (void f_ptr(char*)) 0x004015AF; // Lib: Server.obj Class : (null)
static void (*ProcessDBMessage)(char*)										= (void f_ptr(char*)) 0x00401181; // Lib: Server.obj Class : (null)
static void (*CheckIdle)(int)												= (void f_ptr(int)) 0x004011F4; // Lib: Server.obj Class : (null)
static void (*FinishCastleWar)(void)										= (void f_ptr(void)) 0x004011EA; // Lib: Server.obj Class : (null)
static void (*RegenMob)(int)												= (void f_ptr(int)) 0x00401587; // Lib: Server.obj Class : (null)
static int (*ProcessAffect)(int)											= (int f_ptr(int)) 0x004011F9; // Lib: Server.obj Class : (null)
static void (*SendDamage)(int,int,int,int)									= (void f_ptr(int,int,int,int)) 0x004012A8; // Lib: Server.obj Class : (null)
static void (*ProcessSecTimer)(void)										= (void f_ptr(void)) 0x453180; // Lib: Server.obj Class : (null)
static void (*ProcessMinTimer)(void)										= (void f_ptr(void)) 0x455B60; // Lib: Server.obj Class : (null)
static void (*SummonGuild2)(int,int,int,int,int)							= (void f_ptr(int,int,int,int,int)) 0x004014EC; // Lib: Server.obj Class : (null)
static void (*SummonGuild)(int,int,int,int,int)								= (void f_ptr(int,int,int,int,int)) 0x004015C8; // Lib: Server.obj Class : (null)
static void (*ClearArea)(int x_min, int y_min, int x_max, int y_max)		= (void f_ptr(int,int,int,int)) 0x0040106E; // Lib: Server.obj Class : (null)
static void (*ClearAreaLevel)(int,int,int,int,int lvl_min, int lvl_max)		= (void f_ptr(int,int,int,int,int,int)) 0x00401244; // Lib: Server.obj Class : (null)
static void (*ClearAreaGuild)(int,int,int,int,int)							= (void f_ptr(int,int,int,int,int)) 0x0040144C; // Lib: Server.obj Class : (null)
static void (*ClearAreaTeleport)(int,int,int,int,int,int)					= (void f_ptr(int,int,int,int,int,int)) 0x00401596; // Lib: Server.obj Class : (null)
static void (*ClearGuildPKZone)(void)										= (void f_ptr(void)) 0x00401235; // Lib: Server.obj Class : (null)
static void (*SetColoseumDoor)(int)											= (void f_ptr(int)) 0x00401415; // Lib: Server.obj Class : (null)
static void (*SetColoseumDoor2)(int)										= (void f_ptr(int)) 0x004010EB; // Lib: Server.obj Class : (null)
static void (*GenerateColoseum)(int)										= (void f_ptr(int)) 0x0040142E; // Lib: Server.obj Class : (null)
static void (*DeleteColoseum)(void)											= (void f_ptr(void)) 0x0040121C; // Lib: Server.obj Class : (null)
static void (*SetArenaDoor)(int)											= (void f_ptr(int)) 0x00401050; // Lib: Server.obj Class : (null)
static void (*SetCastleDoor)(int)											= (void f_ptr(int)) 0x0040122B; // Lib: Server.obj Class : (null)
static void (*DecideWinner)(void)											= (void f_ptr(void)) 0x004013D9; // Lib: Server.obj Class : (null)
static void (*GuildProcess)(void)											= (void f_ptr(void)) 0x0040146A; // Lib: Server.obj Class : (null)
static void (*StartLog)(void)												= (void f_ptr(void)) 0x00401519; // Lib: Server.obj Class : (null)
static void (*CrackLog)(int,char*)											= (void f_ptr(int,char*)) 0x0040112C; // Lib: Server.obj Class : (null)
static void (*Log)(char*,char*,unsigned int)								= (void f_ptr(char*,char*,unsigned int)) 0x00401406; // Lib: Server.obj Class : (null)
static int (*GetUserFromSocket)(int)										= (int f_ptr(int)) 0x0040115E; // Lib: Server.obj Class : (null)
static int (*GetEmptyUser)(void)											= (int f_ptr(void)) 0x004014B5; // Lib: Server.obj Class : (null)
static int (*GetEmptyItem)(void)											= (int f_ptr(void)) 0x00401410; // Lib: Server.obj Class : (null)
static int (*GetEmptyNPCMob)(void)											= (int f_ptr(void)) 0x004013C5; // Lib: Server.obj Class : (null)
static int (*GetUserByName)(char*)											= (int f_ptr(char*)) 0x004010FA; // Lib: Server.obj Class : (null)
static int (*IsImple)(int)													= (int f_ptr(int)) 0x004014A6; // Lib: Server.obj Class : (null)
static void (*CloseUser_OL2)(int)											= (void f_ptr(int)) 0x004012A3; // Lib: Server.obj Class : (null)
static BYTE* (*GetMobFromIndex)(unsigned int)								= (BYTE* f_ptr(unsigned int)) 0x00401483; // Lib: Server.obj Class : (null)
static int (*GetAngle)(int,int)												= (int f_ptr(int,int)) 0x0040157D; // Lib: Server.obj Class : (null)
static int (*GetLength)(int,int)											= (int f_ptr(int,int)) 0x00401497; // Lib: Server.obj Class : (null)
static int (*ReadMob)(struct STRUCT_MOB*,char*)								= (int f_ptr(struct STRUCT_MOB*,char*)) 0x0040131B; // Lib: Server.obj Class : (null)
static void (*DeleteMob)(int,int)											= (void f_ptr(int,int)) 0x00401113; // Lib: Server.obj Class : (null)
static void (*SaveUser)(int,int)											= (void f_ptr(int,int)) 0x459E40; // Lib: Server.obj Class : (null)
static void (*CharLogOut)(int)												= (void f_ptr(int)) 0x004013B6; // Lib: Server.obj Class : (null)
static void (*Reboot)(void)													= (void f_ptr(void)) 0x00401226; // Lib: Server.obj Class : (null)
static void (*ClearChallanger)(void)										= (void f_ptr(void)) 0x004011C2; // Lib: Server.obj Class : (null)
static void (*ReadChallanger)(void)											= (void f_ptr(void)) 0x00401424; // Lib: Server.obj Class : (null)
static void (*WriteChallanger)(void)										= (void f_ptr(void)) 0x0040114A; // Lib: Server.obj Class : (null)
static void (*SetBattle)(int,int)											= (void f_ptr(int,int)) 0x00401014; // Lib: Server.obj Class : (null)
static void (*MobKilled)(int,int,int,int)									= (void f_ptr(int,int,int,int)) 0x45AB00; // Lib: Server.obj Class : (null)
static int (*CreateItem)(int, int, st_Item*,int,int)				= (int f_ptr(int,int, st_Item*,int,int)) 0x00401096; // Lib: Server.obj Class : (null)
static void (*RemoveTrade)(int)												= (void f_ptr(int)) 0x00401447; // Lib: Server.obj Class : (null)
static void (*RemoveParty)(int)												= (void f_ptr(int)) 0x00401366; // Lib: Server.obj Class : (null)
static int (*UpdateItem)(int,int,int*)										= (int f_ptr(int,int,int*)) 0x0040161D; // Lib: Server.obj Class : (null)
static void (*DoRecall)(int)												= (void f_ptr(int)) 0x00401294; // Lib: Server.obj Class : (null)
static void (*DoWar)(int,int)												= (void f_ptr(int,int)) 0x00401032; // Lib: Server.obj Class : (null)
static void (*DoAlly)(int,int)												= (void f_ptr(int,int)) 0x00401118; // Lib: Server.obj Class : (null)
static void (*DoDeprivate)(int,int)											= (void f_ptr(int,int)) 0x004012DF; // Lib: Server.obj Class : (null)
static void (*ProcessRanking)(void)											= (void f_ptr(void)) 0x0040111D; // Lib: Server.obj Class : (null)
static void (*DoRanking)(int,int,int)										= (void f_ptr(int,int,int)) 0x00401604; // Lib: Server.obj Class : (null)
static void (*DoRemoveHide)(int)											= (void f_ptr(int)) 0x00401442; // Lib: Server.obj Class : (null)
static void (*DoTeleport)(int clientID, int posX, int posY)					= (void f_ptr(int clientID, int posX, int posY)) 0x004010C8; // Lib: Server.obj Class : (null)
static void (*DoSummon)(int,int,int)										= (void f_ptr(int,int,int)) 0x004015FF; // Lib: Server.obj Class : (null)
static int (*SetAffect)(int,int,int,int)									= (int f_ptr(int,int,int,int)) 0x004015BE; // Lib: Server.obj Class : (null)
static int (*SetTick)(int,int,int,int)										= (int f_ptr(int,int,int,int)) 0x00401429; // Lib: Server.obj Class : (null)
static void (*ProcessDecayItem)(void)										= (void f_ptr(void)) 0x004012F8; // Lib: Server.obj Class : (null)
static int (*CombineTreasureMap)(int)										= (int f_ptr(int)) 0x004010CD; // Lib: Server.obj Class : (null)
static void (*Combine)(int,int,int)											= (void f_ptr(int,int,int)) 0x004015D7; // Lib: Server.obj Class : (null)
static int (*ApplyHp)(int)													= (int f_ptr(int)) 0x00401253; // Lib: Server.obj Class : (null)
static int (*ApplyMp)(int)													= (int f_ptr(int)) 0x0040153C; // Lib: Server.obj Class : (null)
static void (*SetReqHp)(int)												= (void f_ptr(int)) 0x00401492; // Lib: Server.obj Class : (null)
static void (*SetReqMp)(int)												= (void f_ptr(int)) 0x004011A9; // Lib: Server.obj Class : (null)

// New
static void (*DeleteNightMareN)(void)										= (void f_ptr(void)) 0x00401627; // Lib: Server.obj Class : (null)
static void (*DeleteNightMareM)(void)										= (void f_ptr(void)) 0x0040162C; // Lib: Server.obj Class : (null)
static void (*DeleteNightMareA)(void)										= (void f_ptr(void)) 0x00401631; // Lib: Server.obj Class : (null)
static void (*DeleteLetterN_01)(void)										= (void f_ptr(void)) 0x00401636; // Lib: Server.obj Class : (null)
static void (*DeleteLetterN_02)(void)										= (void f_ptr(void)) 0x0040163B; // Lib: Server.obj Class : (null)
static void (*DeleteLetterN_03)(void)										= (void f_ptr(void)) 0x00401640; // Lib: Server.obj Class : (null)
static void (*DeleteLetterN_04)(void)										= (void f_ptr(void)) 0x00401645; // Lib: Server.obj Class : (null)
static void (*DeleteLetterM_01)(void)										= (void f_ptr(void)) 0x0040164A; // Lib: Server.obj Class : (null)
static void (*DeleteLetterM_02)(void)										= (void f_ptr(void)) 0x0040164F; // Lib: Server.obj Class : (null)
static void (*DeleteLetterM_03)(void)										= (void f_ptr(void)) 0x00401654; // Lib: Server.obj Class : (null)
static void (*DeleteLetterM_04)(void)										= (void f_ptr(void)) 0x00401659; // Lib: Server.obj Class : (null)
static void (*DeleteLetterA_01)(void)										= (void f_ptr(void)) 0x0040165E; // Lib: Server.obj Class : (null)
static void (*DeleteLetterA_02)(void)										= (void f_ptr(void)) 0x00401663; // Lib: Server.obj Class : (null)
static void (*DeleteLetterA_03)(void)										= (void f_ptr(void)) 0x00401668; // Lib: Server.obj Class : (null)
static void (*DeleteLetterA_04)(void)										= (void f_ptr(void)) 0x0040166D; // Lib: Server.obj Class : (null)
static void (*DeleteTowerOfWar)(void)										= (void f_ptr(void)) 0x00401672; // Lib: Server.obj Class : (null)
static void (*DeleteUxmall_01)(void)										= (void f_ptr(void)) 0x00401677; // Lib: Server.obj Class : (null)
static void (*DeleteUxmall_02)(void)										= (void f_ptr(void)) 0x0040167C; // Lib: Server.obj Class : (null)
static void (*DeleteUxmall_03)(void)										= (void f_ptr(void)) 0x00401681; // Lib: Server.obj Class : (null)

static void GenerateMemberOfParty(int clientId, int summon_Id)
{
	int summon_Addr = 0x0446170;
	_asm
	{
		PUSH 0
		PUSH summon_Id
		PUSH clientId
		CALL summon_Addr
		ADD ESP, 0x0C
	}
}
#pragma endregion

#pragma region Basedef.obj
static int (*BASE_NeedLog)(struct STRUCT_ITEM*,int) = (int f_ptr(struct STRUCT_ITEM *,int)) 0x00401037; // Lib: Basedef.obj Class : (null)
static int (*SendBilling2)(struct _AUTH_GAME*,int) = (int f_ptr(struct _AUTH_GAME *,int)) 0x00401172; // Lib: Server.obj Class : (null)
static int (*BASE_GetBonusSkillPoint)(struct STRUCT_MOB*) = (int f_ptr(struct STRUCT_MOB*)) 0x00401456; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetBonusScorePoint)(struct STRUCT_MOB*) = (int f_ptr(struct STRUCT_MOB*)) 0x0040133E; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetHpMp)(struct STRUCT_MOB*) = (int f_ptr(struct STRUCT_MOB *)) 0x00401307; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSpeed)(struct STRUCT_SCORE*) = (int f_ptr(struct STRUCT_SCORE *)) 0x0040132F; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetDamage)(int,int,int) = (int f_ptr(int,int,int)) 0x00401041; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL1)(char*,int) = (void f_ptr(char *,int)) 0x00401195; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL2)(char*,int,char *) = (void f_ptr(char *,int,char *)) 0x004011B3; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL3)(char*,int,char *,char *) = (void f_ptr(char *,int,char *,char *)) 0x00401537; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL4)(char*,int,int) = (void f_ptr(char *,int,int)) 0x004013C0; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL5)(char*,int,int,int) = (void f_ptr(char *,int,int,int)) 0x00401541; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL6)(char*,int,char *,int) = (void f_ptr(char *,int,char *,int)) 0x0040116D; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetLanguage_OL7)(char*,int,int,char *) = (void f_ptr(char *,int,int,char *)) 0x00401280; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetGuildName)(int,unsigned short,char *) = (void f_ptr(int,unsigned short,char *)) 0x004013B1; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetClientGuildName)(int,unsigned short,char *,int) = (void f_ptr(int,unsigned short,char *,int)) 0x00401249; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSkillDamage_OL1)(int,int,int) = (int f_ptr(int,int,int)) 0x0040103C; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetItemCode)(struct STRUCT_ITEM *,char *) = (void f_ptr(struct STRUCT_ITEM *,char *)) 0x004010AF; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetItemAbilityNosanc)(struct STRUCT_ITEM *,unsigned char) = (int f_ptr(struct STRUCT_ITEM *,unsigned char)) 0x0040110E; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetItemAbility)(struct STRUCT_ITEM *,unsigned char) = (int f_ptr(struct STRUCT_ITEM *,unsigned char)) 0x004015A0; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetStaticItemAbility)(struct STRUCT_ITEM *,unsigned char) = (int f_ptr(struct STRUCT_ITEM *,unsigned char)) 0x0040146F; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetBonusItemAbility)(struct STRUCT_ITEM *,unsigned char) = (int f_ptr(struct STRUCT_ITEM *,unsigned char)) 0x004011E0; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetBonusItemAbilityNosanc)(struct STRUCT_ITEM *,unsigned char) = (int f_ptr(struct STRUCT_ITEM *,unsigned char)) 0x004013D4; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetItemSanc)(st_Item*) = (int f_ptr(st_Item*)) 0x00401393; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetItemSancSuccess)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x004013A2; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSuccessRate)(struct STRUCT_ITEM *,int) = (int f_ptr(struct STRUCT_ITEM *,int)) 0x00401203; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetGrowthRate)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x004014E7; // Lib: Basedef.obj Class : (null)
static int (*BASE_SetItemSanc)(st_Item*,int,int) = (int f_ptr(st_Item*,int,int)) 0x00401145; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetItemAmount)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x00401311; // Lib: Basedef.obj Class : (null)
static void (*BASE_SetItemAmount)(struct STRUCT_ITEM *,int) = (void f_ptr(struct STRUCT_ITEM *,int)) 0x00401555; // Lib: Basedef.obj Class : (null)
static struct STRUCT_ITEM* (*GetItemPointer)(struct STRUCT_MOB*, struct STRUCT_ITEM*, int, int) = (struct STRUCT_ITEM* f_ptr(struct STRUCT_MOB *,struct STRUCT_ITEM *,int,int)) 0x00401208; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetMobAbility)(struct STRUCT_MOB *,unsigned char) = (int f_ptr(struct STRUCT_MOB *,unsigned char)) 0x00401046; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetMaxAbility)(struct STRUCT_MOB *,unsigned char) = (int f_ptr(struct STRUCT_MOB *,unsigned char)) 0x004015E6; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetMobCheckSum)(struct STRUCT_MOB*) = (int f_ptr(struct STRUCT_MOB*)) 0x004015B9; // Lib: Basedef.obj Class : (null)
static bool (*BASE_CheckValidString)(char*) = (bool f_ptr(char*)) 0x004010F5; // Lib: Basedef.obj Class : (null)
static bool (*BASE_CheckHangul)(unsigned short) = (bool f_ptr(unsigned short)) 0x00401087; // Lib: Basedef.obj Class : (null)
static int (*BASE_InitializeBaseDef)(void) = (int f_ptr(void)) 0x0040101E; // Lib: Basedef.obj Class : (null)
static void (*BASE_ApplyAttribute)(char *,int) = (void f_ptr(char *,int)) 0x004011D1; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitModuleDir)(void) = (void f_ptr(void)) 0x004015AA; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSum)(char*,int) = (int f_ptr(char *,int)) 0x0040154B; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSum2)(char*,int) = (int f_ptr(char *,int)) 0x00401168; // Lib: Basedef.obj Class : (null)
static void (*BASE_WriteSkillBin)(void) = (void f_ptr(void)) 0x0040105F; // Lib: Basedef.obj Class : (null)
static void (*BASE_WriteItemList)(int) = (void f_ptr(int)) 0x004013FC; // Lib: Basedef.obj Class : (null)
static int (*BASE_ReadSkillBin)(void) = (int f_ptr(void)) 0x004011DB; // Lib: Basedef.obj Class : (null)
static int (*BASE_ReadItemList)(void) = (int f_ptr(void)) 0x00401019; // Lib: Basedef.obj Class : (null)
static void (*BASE_SpaceToUnderBar)(char*) = (void f_ptr(char *)) 0x004014DD; // Lib: Basedef.obj Class : (null)
static void (*BASE_UnderBarToSpace)(char*) = (void f_ptr(char *)) 0x00401073; // Lib: Basedef.obj Class : (null)
static void (*BASE_ClearMob)(struct STRUCT_MOB *) = (void f_ptr(struct STRUCT_MOB *)) 0x0040141F; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetCurrentScore)(struct STRUCT_MOB *,struct STRUCT_AFFECT *) = (void f_ptr(struct STRUCT_MOB *,struct STRUCT_AFFECT *)) 0x004014C9; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetFirstKey)(char *,char *) = (void f_ptr(char *,char *)) 0x0040152D; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetGuild_OL1)(int,int) = (int f_ptr(int,int)) 0x004011EF; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetIndex)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x00401230; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetGuild_OL2)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x00401465; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSubGuild)(int) = (int f_ptr(int)) 0x004012B2; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetArena)(int,int) = (int f_ptr(int,int)) 0x00401370; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetVillage)(int,int) = (int f_ptr(int,int)) 0x0040118B; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetKorFirst)(int,int *) = (void f_ptr(int,int *)) 0x00401217; // Lib: Basedef.obj Class : (null)
static void (*BASE_ClearItem)(struct STRUCT_ITEM *) = (void f_ptr(struct STRUCT_ITEM *)) 0x004014C4; // Lib: Basedef.obj Class : (null)
static int (*BASE_CanEquip)(struct STRUCT_ITEM *,struct STRUCT_SCORE *,int,int,struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *,struct STRUCT_SCORE *,int,int,struct STRUCT_ITEM *)) 0x0040100F; // Lib: Basedef.obj Class : (null)
static int (*BASE_CanCarry)(struct STRUCT_ITEM *,struct STRUCT_ITEM *,int,int,int *) = (int f_ptr(struct STRUCT_ITEM *,struct STRUCT_ITEM *,int,int,int *)) 0x00401334; // Lib: Basedef.obj Class : (null)
static int (*BASE_CanCargo)(struct STRUCT_ITEM *,struct STRUCT_ITEM *,int,int) = (int f_ptr(struct STRUCT_ITEM *,struct STRUCT_ITEM *,int,int)) 0x004010A5; // Lib: Basedef.obj Class : (null)
static void (*BASE_SortTradeItem)(struct STRUCT_ITEM *,int) = (void f_ptr(struct STRUCT_ITEM *,int)) 0x004014D3; // Lib: Basedef.obj Class : (null)
static int (*BASE_CanTrade)(struct STRUCT_ITEM *,struct STRUCT_ITEM *,unsigned char *,struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *,struct STRUCT_ITEM *,unsigned char *,struct STRUCT_ITEM *)) 0x00401091; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeMessage)(char*) = (void f_ptr(char *)) 0x004011D6; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeMobname)(char*,int) = (void f_ptr(char *,int)) 0x004010B9; // Lib: Basedef.obj Class : (null)
static void (*BASE_WriteMessageBin)(void) = (void f_ptr(void)) 0x00401078; // Lib: Basedef.obj Class : (null)
static int (*BASE_ReadMessageBin)(void) = (int f_ptr(void)) 0x00401163; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeItemList)(void) = (void f_ptr(void)) 0x00401532; // Lib: Basedef.obj Class : (null)
static int (*BASE_ReadItemListFile)(char *,int) = (int f_ptr(char *,int)) 0x004012E4; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeEffectName)(void) = (void f_ptr(void)) 0x0040155F; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeHitRate)(void) = (void f_ptr(void)) 0x00401546; // Lib: Basedef.obj Class : (null)
static int (*BASE_UpdateItem)(int,int,int,int,int,char *,int,int *) = (int f_ptr(int,int,int,int,int,char *,int,int *)) 0x004011AE; // Lib: Basedef.obj Class : (null)
static int (*BASE_UpdateItem2)(int,int,int,int,int,char *,int,int) = (int f_ptr(int,int,int,int,int,char *,int,int)) 0x00401186; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetDestByAction)(unsigned short *,unsigned short *,struct MSG_Action *) = (void f_ptr(unsigned short *,unsigned short *,struct MSG_Action *)) 0x00401064; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetManaSpent)(int,int,int) = (int f_ptr(int,int,int)) 0x00401622; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetHitRate)(struct STRUCT_SCORE *,struct STRUCT_SCORE *) = (int f_ptr(struct STRUCT_SCORE *,struct STRUCT_SCORE *)) 0x0040117C; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetDamageRate)(struct STRUCT_SCORE *,int) = (int f_ptr(struct STRUCT_SCORE *,int)) 0x004012DA; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetAccuracyRate)(struct STRUCT_SCORE *) = (int f_ptr(struct STRUCT_SCORE *)) 0x00401361; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetDoubleCritical)(struct STRUCT_MOB *,unsigned short *,unsigned short *,unsigned char *) = (int f_ptr(struct STRUCT_MOB *,unsigned short *,unsigned short *,unsigned char *)) 0x004015FA; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetRoute)(int, int, int *,int *,char *,int,char *) = (int f_ptr(int,int,int *,int *,char *,int,char *)) 0x004015A5; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetDistance)(int,int,int,int) = (int f_ptr(int,int,int,int)) 0x004013AC; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetHitPosition)(int,int,int *,int *,char *) = (void f_ptr(int,int,int *,int *,char *)) 0x00401618; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetHitPosition2)(int,int,int *,int *,char *) = (void f_ptr(int,int,int *,int *,char *)) 0x0040140B; // Lib: Basedef.obj Class : (null)
static void (*BASE_WriteInitItem)(void) = (void f_ptr(void)) 0x0040138E; // Lib: Basedef.obj Class : (null)
static int (*BASE_ReadInitItem)(void) = (int f_ptr(void)) 0x0040127B; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeInitItem)(void) = (void f_ptr(void)) 0x004012AD; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeSkill)(void) = (void f_ptr(void)) 0x00401127; // Lib: Basedef.obj Class : (null)
static int (*IsClearString3)(char *,int) = (int f_ptr(char *,int)) 0x00401028; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeClientGuildName)(int) = (void f_ptr(int)) 0x0040104B; // Lib: Basedef.obj Class : (null)
static void (*BASE_InitializeGuildName)(void) = (void f_ptr(void)) 0x00401389; // Lib: Basedef.obj Class : (null)
static int (*BASE_InitializeServerList)(void) = (int f_ptr(void)) 0x004010F0; // Lib: Basedef.obj Class : (null)
static int (*BASE_InitializeAttribute)(void) = (int f_ptr(void)) 0x004010E1; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetHttpRequest)(char *,char *,int) = (int f_ptr(char *,char *,int)) 0x00401460; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetSkillDamage_OL2)(int,struct STRUCT_MOB *,int,int) = (int f_ptr(int,struct STRUCT_MOB *,int,int)) 0x004014E2; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetEnglish)(char *) = (int f_ptr(char *)) 0x00401550; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetWeekNumber)(void) = (int f_ptr(void)) 0x0040102D; // Lib: Basedef.obj Class : (null)
static int (*BASE_CheckPacket)(struct MSG_STANDARD*) = (int f_ptr(struct MSG_STANDARD *)) 0x004012D5; // Lib: Basedef.obj Class : (null)
static void (*LoadSkillData)()										= (void f_ptr()) 0x040E0D0;
#pragma endregion

#pragma region CNPCGene.obj
static int (*ReadNPCGenerator)(void)			= (int f_ptr(void)) 0x00401055; // Lib: CNPCGene.obj Class : CNPCGenerator
static int (*ParseString)(int, char*)			= (int f_ptr(int, char*)) 0x401271; // Lib: CNPCGene.obj Class : CNPCGenerator
static void (*Initialize)(void)					= (void f_ptr(void)) 0x004011E5; // Lib: CNPCGene.obj Class : CNPCSummon
static void (*SetAct)(char*, char*)				= (void f_ptr(char*, char*)) 0x00401302; // Lib: CNPCGene.obj Class : (null)
#pragma endregion

#pragma region CPSock.obj
static int (* CloseSocket)(void)									= (int f_ptr(void)) 0x00401325; // Lib: CPSock.obj Class : CPSock
static int (* WSAInitialize)(void)									= (int f_ptr(void)) 0x00401267; // Lib: CPSock.obj Class : CPSock
static unsigned int (* StartListen)(struct HWND__ *,int,int,int)	= (unsigned int f_ptr(struct HWND__ *,int,int,int)) 0x004015B4; // Lib: CPSock.obj Class : CPSock
static unsigned int (* ConnectServer)(char *,int,int,int)			= (unsigned int f_ptr(char *,int,int,int)) 0x00401474; // Lib: CPSock.obj Class : CPSock
static unsigned int (* ConnectBillServer)(char *,int,int,int)		= (unsigned int f_ptr(char *,int,int,int)) 0x0040128A; // Lib: CPSock.obj Class : CPSock
static int (* Receive)(void)										= (int f_ptr(void)) 0x00401023; // Lib: CPSock.obj Class : CPSock
static char (* ReadMessage)(int *,int *)							= (char f_ptr(int *,int *)) 0x419280; // Lib: CPSock.obj Class : * CPSock
static char (* ReadBillMessage)(int *,int *)						= (char f_ptr(int *,int *)) 0x0040123F; // Lib: CPSock.obj Class : * CPSock
static int (* SendBillMessage)(char *)								= (int f_ptr(char *)) 0x004010E6; // Lib: CPSock.obj Class : CPSock
static int (* _AddMessage)(BYTE *,int)								= (int f_ptr(BYTE *,int)) 0x4198C0; // Lib: CPSock.obj Class : CPSock
static void (* RefreshRecvBuffer)(void)								= (void f_ptr(void)) 0x0040100A; // Lib: CPSock.obj Class : CPSock
static void (* RefreshSendBuffer)(void)								= (void f_ptr(void)) 0x004013F2; // Lib: CPSock.obj Class : CPSock
//static int (* SendMessageA)(void)									= (int f_ptr(void)) 0x00401613; // Lib: CPSock.obj Class : CPSock
static int (* _SendOneMessage)(char *,int)							= (int f_ptr(char *,int)) 0x004012B7; // Lib: CPSock.obj Class : CPSock

static int SendOneMessage(BYTE* packet, int pSize, unsigned int objInstance)
{
	int retn = 0;

	__asm
	{
		PUSH pSize
		PUSH [packet]
		MOV ECX, objInstance
		MOV EAX, 0x4012B7
		CALL EAX

		MOV retn, EAX
	}

	return retn;
}

static void AddMessage(BYTE *bufr, int clientId)
{
	static DWORD func_addr = 0x4198C0;
	static DWORD pSize = *(WORD*)bufr;
	__asm
	{
		MOV ECX, clientId
		IMUL ECX, ECX, 0xC4C
		ADD ECX, 0x7B318E8

		PUSH pSize
		PUSH bufr
		CALL func_addr
	}
}

static void SendFunctionPacket(BYTE *bufr, int clientId)
{
	static DWORD func_addr = 0x04198C0;

	__asm
	{
		MOV ECX, clientId
		IMUL ECX, ECX, 0xC4C
		ADD ECX, 0x07B318E8

		PUSH 140
		PUSH bufr
		CALL func_addr
	}
}

static void SendFunctionPacket_02(BYTE *bufr, int clientId,int paksize)
{
	static DWORD func_addr = 0x4198C0;

	__asm
	{
  		MOV ECX, clientId
  		IMUL ECX, ECX, 0xC4C
  		ADD ECX, 0x7B318E8

  		PUSH paksize
  		PUSH bufr
  		CALL func_addr
	}
}
#pragma endregion

#pragma region CMob.obj
static void (*ProcessorSecTimer)(void)				= (void f_ptr(void)) 0x00401523; // Lib: CMob.obj Class : CMob
static int (*StandingByProcessor)(void)				= (int f_ptr(void)) 0x0040107D; // Lib: CMob.obj Class : CMob
static int (*BattleProcessor)(void)					= (int f_ptr(void)) 0x004013ED; // Lib: CMob.obj Class : CMob
static void (*AddEnemyList)(short)					= (void f_ptr(short)) 0x00401212; // Lib: CMob.obj Class : CMob
static void (*RemoveEnemyList)(short)				= (void f_ptr(short)) 0x004011C7; // Lib: CMob.obj Class : CMob
static void (*SelectTargetFromEnemyList)(void)		= (void f_ptr(void)) 0x004010AA; // Lib: CMob.obj Class : CMob
static int (*SetSegment)(void)						= (int f_ptr(void)) 0x00401591; // Lib: CMob.obj Class : CMob
static void (*_GetCurrentScore)(int)					= (void f_ptr(int)) 0x0040149C; // Lib: CMob.obj Class : CMob
static void (*GetTargetPosDistance)(int)			= (void f_ptr(int)) 0x004011B8; // Lib: CMob.obj Class : CMob
static void (*GetRandomPos)(void)					= (void f_ptr(void)) 0x0040114F; // Lib: CMob.obj Class : CMob
static void (*GetTargetPos)(int)					= (void f_ptr(int)) 0x0040105A; // Lib: CMob.obj Class : CMob
static int (*_CheckGetLevel)(void)					= (int f_ptr(void)) 0x40143D; // Lib: CMob.obj Class : CMob
static void (*GetNextPos)(int)						= (void f_ptr(int)) 0x00401262; // Lib: CMob.obj Class : CMob
static int (*GetEnemyFromView)(void)				= (int f_ptr(void)) 0x0040151E; // Lib: CMob.obj Class : CMob

static int CheckGetLevel(int clientId)
{
	int retnValue;
	__asm
	{
		MOV ECX, clientId
		IMUL ECX, 0x410
		ADD ECX, 0x15C69B8

		MOV EAX, 0x40143D
		CALL EAX

		MOV retnValue, EAX
	}

	return retnValue;
}

static void GetCurrentScore(int clientId)
{
	static DWORD func_addr = 0x40149C;
	__asm
	{
		MOV ECX, clientId
		IMUL ECX, ECX, 0x410
		ADD ECX, 0x15C69B8

		MOV EAX, clientId
		PUSH EAX
		CALL func_addr
	}
}
#pragma endregion

#pragma region CUser.obj
static int (* AcceptUser)(int)	= (int f_ptr(int)) 0x004010A0; // Lib: CUser.obj Class : CUser
static int (* CloseUser_OL1)(void)	= (int f_ptr(void)) 0x00401285; // Lib: CUser.obj Class : CUser
#pragma endregion

#pragma region GetFunc.obj
static int (*GetMatchCombine)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x00401451; // Lib: GetFunc.obj Class : (null)
static int (*GetParryRate)(struct STRUCT_MOB *,int) = (int f_ptr(struct STRUCT_MOB *,int)) 0x0040113B; // Lib: GetFunc.obj Class : (null)
static int (*GetEmptyAffect)(int,int) = (int f_ptr(int,int)) 0x00401339; // Lib: GetFunc.obj Class : (null)
static int (*GetHide)(int) = (int f_ptr(int)) 0x00401505; // Lib: GetFunc.obj Class : (null)
static int (*GetInView)(int,int) = (int f_ptr(int,int)) 0x004011FE; // Lib: GetFunc.obj Class : (null)
static int (*GetInHalf)(int,int) = (int f_ptr(int,int)) 0x00401159; // Lib: GetFunc.obj Class : (null)
static int (*GetTeleportPosition)(int *,int *) = (int f_ptr(int *,int *)) 0x0040150A; // Lib: GetFunc.obj Class : (null)
static int (*GetExpApply)(int,int,int) = (int f_ptr(int,int,int)) 0x00401104; // Lib: GetFunc.obj Class : (null)
static int (*GetCreateMob)(int clientID, BYTE*) = (int f_ptr(int clientID, BYTE*)) 0x00401136; // Lib: GetFunc.obj Class : (null)
static int (*GetCreateMobTrade)(int,struct MSG_CreateMobTrade*) = (int f_ptr(int,struct MSG_CreateMobTrade *)) 0x00401528; // Lib: GetFunc.obj Class : (null)
static void (*GetAffect)(unsigned short *,struct STRUCT_AFFECT *) = (void f_ptr(unsigned short *,struct STRUCT_AFFECT *)) 0x00401122; // Lib: GetFunc.obj Class : (null)
static void (*GetCreateItem)(int,struct MSG_CreateItem *) = (void f_ptr(int,struct MSG_CreateItem *)) 0x004015EB; // Lib: GetFunc.obj Class : (null)
static void (*GetAction)(int,int,int,struct MSG_Action *) = (void f_ptr(int,int,int,struct MSG_Action *)) 0x004012BC; // Lib: GetFunc.obj Class : (null)
static unsigned char (*GetAttribute)(int,int) = (unsigned char f_ptr(int,int)) 0x004014AB; // Lib: GetFunc.obj Class : (null)
static void (*GetAttack)(int,int,struct MSG_AttackOne *) = (void f_ptr(int,int,struct MSG_AttackOne *)) 0x00401375; // Lib: GetFunc.obj Class : (null)
static void (*GetGuild_OL1)(int) = (void f_ptr(int)) 0x00401433; // Lib: GetFunc.obj Class : (null)
static int (*GetGuild_OL2)(struct STRUCT_ITEM *) = (int f_ptr(struct STRUCT_ITEM *)) 0x004014BF; // Lib: GetFunc.obj Class : (null)
static int (*GetEmptyItemGrid)(int *,int *) = (int f_ptr(int *,int *)) 0x004014F6; // Lib: GetFunc.obj Class : (null)
static int (*GetEmptyMobGrid)(int,int *,int *) = (int f_ptr(int,int *,int *)) 0x00401401; // Lib: GetFunc.obj Class : (null)
static int (*GetCurKill)(int) = (int f_ptr(int)) 0x004014F1; // Lib: GetFunc.obj Class : (null)
static int (*GetTotKill)(int) = (int f_ptr(int)) 0x0040130C; // Lib: GetFunc.obj Class : (null)
static void (*SetCurKill)(int,int) = (void f_ptr(int,int)) 0x004014A1; // Lib: GetFunc.obj Class : (null)
static void (*SetTotKill)(int,int) = (void f_ptr(int,int)) 0x00401500; // Lib: GetFunc.obj Class : (null)
static int (*GetPKPoint)(int) = (int f_ptr(int)) 0x004012FD; // Lib: GetFunc.obj Class : (null)
static int (*GetGuilty)(int) = (int f_ptr(int)) 0x004012CB; // Lib: GetFunc.obj Class : (null)
static void (*SetGuilty)(int,int) = (void f_ptr(int,int)) 0x00401488; // Lib: GetFunc.obj Class : (null)
static void (*SetPKPoint)(int,int) = (void f_ptr(int,int)) 0x0040137A; // Lib: GetFunc.obj Class : (null)
#pragma endregion

#pragma region SendFunc.obj
static void (*SendClientMessage)(int, char*) = (void f_ptr(int,char *)) 0x004010FF; // Lib: SendFunc.obj Class : (null)
static void (*SendNotice)(char*) = (void f_ptr(char *)) 0x00401357; // Lib: SendFunc.obj Class : (null)
static void (*SendNoticeChief)(char*) = (void f_ptr(char *)) 0x00401258; // Lib: SendFunc.obj Class : (null)
static void (*SendSummonChief)(void) = (void f_ptr(void)) 0x0040125D; // Lib: SendFunc.obj Class : (null)
static void (*SendNoticeArea)(char*, int, int, int, int) = (void f_ptr(char *,int,int,int,int)) 0x00401177; // Lib: SendFunc.obj Class : (null)
static void (*SendGuildNotice)(int, char*) = (void f_ptr(int,char *)) 0x00401479; // Lib: SendFunc.obj Class : (null)
static void (*SendClientMessageOk)(int, char*, int, int) = (void f_ptr(int,char *,int,int)) 0x0040134D; // Lib: SendFunc.obj Class : (null)
static void (*SendClientSignal)(int, int, unsigned short) = (void f_ptr(int,int,unsigned short)) 0x0040145B; // Lib: SendFunc.obj Class : (null)
static void (*SendClientSignalParm)(int,int,unsigned short,int) = (void f_ptr(int,int,unsigned short,int)) 0x0040141A; // Lib: SendFunc.obj Class : (null)
static void (*SendClientSignalParm2)(int,int,unsigned short,int,int) = (void f_ptr(int,int,unsigned short,int,int)) 0x00401276; // Lib: SendFunc.obj Class : (null)
static void (*SendClientSignalParm3)(int,int,unsigned short,int,int,int) = (void f_ptr(int,int,unsigned short,int,int,int)) 0x004015F0; // Lib: SendFunc.obj Class : (null)
static void (*SyncMulticast)(int,struct MSG_STANDARD *,int) = (void f_ptr(int,struct MSG_STANDARD *,int)) 0x004011BD; // Lib: SendFunc.obj Class : (null)
static void (*SendCreateMob)(int clientId,int,int) = (void f_ptr(int,int,int)) 0x0040160E; // Lib: SendFunc.obj Class : (null)
static void (*SendCreateItem)(int,int,int) = (void f_ptr(int,int,int)) 0x00401316; // Lib: SendFunc.obj Class : (null)
static void (*SendChat)(int,char *) = (void f_ptr(int,char *)) 0x004013CF; // Lib: SendFunc.obj Class : (null)
static void (*SendEnvEffect)(int,int,int,int,int,int) = (void f_ptr(int,int,int,int,int,int)) 0x00401582; // Lib: SendFunc.obj Class : (null)
static void (*SendRemoveMob)(int,int,int,int) = (void f_ptr(int,int,int,int)) 0x0040155A; // Lib: SendFunc.obj Class : (null)
static void (*SendAutoTrade)(int,int) = (void f_ptr(int,int)) 0x004012EE; // Lib: SendFunc.obj Class : (null)
static void (*SendGridMob)(int) = (void f_ptr(int)) 0x0040123A; // Lib: SendFunc.obj Class : (null)
static void (*GridMulticast_OL1)(int,int,int,struct MSG_STANDARD *) = (void f_ptr(int,int,int,struct MSG_STANDARD *)) 0x0040120D; // Lib: SendFunc.obj Class : (null)
static void (*SendEmotion)(int,int,int)					= (void f_ptr(int,int,int)) 0x004010DC; // Lib: SendFunc.obj Class : (null)
static void (*GridMulticast_OL2)(int posX, int posY, BYTE* packetBuffer, int zero) = (void f_ptr(int posX, int posY, BYTE* packetBuffer, int zero)) 0x004013A7; // Lib: SendFunc.obj Class : (null)
static void (*PartyGridMulticast)(int,int,struct MSG_STANDARD *,int,int) = (void f_ptr(int,int,struct MSG_STANDARD *,int,int)) 0x0040119F; // Lib: SendFunc.obj Class : (null)
static void (*SendItem)(int clientID, int itemSlotPlace, int itemSlot, st_Item *item) = (void f_ptr(int clientID, int itemSlotPlace, int itemSlot, st_Item *item)) 0x004015C3; // Lib: SendFunc.obj Class : (null)
static void (*SendEquip)(int,int) = (void f_ptr(int,int)) 0x00401069; // Lib: SendFunc.obj Class : (null)
static void (*SendScore)(int) = (void f_ptr(int)) 0x00401578; // Lib: SendFunc.obj Class : (null)
static void (*SendEtc)(int) = (void f_ptr(int)) 0x004012C1; // Lib: SendFunc.obj Class : (null)
static void (*SendCargoCoin)(int) = (void f_ptr(int)) 0x004010C3; // Lib: SendFunc.obj Class : (null)
static void (*SendGuildList)(int) = (void f_ptr(int)) 0x00401569; // Lib: SendFunc.obj Class : (null)
static void (*SendShopList)(int,int,int) = (void f_ptr(int,int,int)) 0x00401343; // Lib: SendFunc.obj Class : (null)
static void (*SendWarInfo)(int,int) = (void f_ptr(int,int)) 0x0040159B; // Lib: SendFunc.obj Class : (null)
static void (*SendAddParty)(int,int,int) = (void f_ptr(int,int,int)) 0x0040147E; // Lib: SendFunc.obj Class : (null)
static void (*SendReqParty)(int,int,int) = (void f_ptr(int,int,int)) 0x004013E8; // Lib: SendFunc.obj Class : (null)
static void (*SendRemoveParty)(int,int) = (void f_ptr(int,int)) 0x004014BA; // Lib: SendFunc.obj Class : (null)
static void (*SendCarry)(int) = (void f_ptr(int)) 0x00401573; // Lib: SendFunc.obj Class : (null)
static void (*SendWeather)(void) = (void f_ptr(void)) 0x00401438; // Lib: SendFunc.obj Class : (null)
static void (*SendSetHpMp)(int) = (void f_ptr(int)) 0x0040156E; // Lib: SendFunc.obj Class : (null)
static void (*SendHpMode)(int) = (void f_ptr(int)) 0x0040129E; // Lib: SendFunc.obj Class : (null)
static void (*SendSay)(int npcID, char *msgToSay) = (void f_ptr(int npcID, char *msgToSay)) 0x00401140; // Lib: SendFunc.obj Class : (null)
#pragma endregion

static int (*Rand)() = (int f_ptr())0x4633E0;

/*https://www.dropbox.com/sh/pmctkmo0xvm2fll/AAAeQNz0SIPbIx3xBBT-kNgFa#/*/

#endif // __NATIVE_FUNCTIONS_H__