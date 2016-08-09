#ifndef __NATIVE_FUNCTIONS_H__
#define __NATIVE_FUNCTIONS_H__

#include "../../Source/Common/st_Base.h"

#define f_ptr (__cdecl *)

static void (*SetReqHp)(int)									= (void f_ptr(int)) 0x00401492; // Lib: Server.obj Class : (null)
static void (*SetReqMp)(int)									= (void f_ptr(int)) 0x004011A9; // Lib: Server.obj Class : (null)
static void (*GetAction)(int,int,int,struct MSG_Action *)       = (void f_ptr(int,int,int,struct MSG_Action *)) 0x004012BC;
static void (*DoRecall)(int)									= (void f_ptr(int)) 0x00401294; // Lib: Server.obj Class : (null)
static void (*SetTotKill)(int,int)                              = (void f_ptr(int,int)) 0x00401500; // Lib: GetFunc.obj Class : (null)
static void (*BASE_GetItemCode)(st_Item *Item,char *Message)    = (void f_ptr(st_Item *Item,char *Message)) 0x004010AF; // Lib: Basedef.obj Class : (null)
static void (*SendAddParty)(int Alvo, int Membro, int Type)     = (void f_ptr(int Alvo, int Membro, int Type)) 0x0040147E; // Lib: SendFunc.obj Class : (null)
//static st_Item* (*GetItemPointer)(st_Mob*, st_Item*, int, int)  = (st_Item* f_ptr(st_Mob *,st_Item *,int,int)) 0x00401208; // Lib: Basedef.obj Class : (null)
static int (*GetGuilty)(int)                                    = (int f_ptr(int)) 0x004012CB; // Lib: GetFunc.obj Class : (null)
static void (*SetGuilty)(int,int)                               = (void f_ptr(int,int)) 0x00401488; // Lib: GetFunc.obj Class : (null)
static void (*MountProcess)(int,st_Item*)						= (void f_ptr(int,st_Item*)) 0x0040135C; // Lib: Server.obj Class : (null)
static void (*ProcessAdultMount)(int,int)						= (void f_ptr(int,int)) 0x004015CD; // Lib: Server.obj Class : (null)
static int (*BASE_GetVillage)(int,int)                          = (int f_ptr(int,int)) 0x0040118B; // Lib: Basedef.obj Class : (null)
static int (*BASE_GetDistance)(int,int,int,int)                 = (int f_ptr(int,int,int,int)) 0x004013AC; // Lib: Basedef.obj Class : (null)
static void (*BASE_GetCurrentScore)(st_Mob &,stAffects *)       = (void f_ptr(st_Mob &,stAffects *)) 0x00406A60;
static int (*BASE_GetBonusSkillPoint)(st_Mob *)                 = (int f_ptr(st_Mob *)) 0x00401456; // Lib: Basedef.obj Class : (null)
//static int (*BASE_GetBonusScorePoint)(st_Mob *)               = (int f_ptr(st_Mob *)) 0x0040133E; // Lib: Basedef.obj Class : (null)
static void (*SetPKPoint)(int,int)                              = (void f_ptr(int,int)) 0x0040137A; // Lib: GetFunc.obj Class : (null)
//static void (*Log)(char*,char*,unsigned int)                    = (void (__cdecl *)(char*,char*,unsigned int)) 0x00458F50;
static int (*BASE_GetItemAbility)(st_Item*,unsigned char)       = (int f_ptr(st_Item*,unsigned char)) 0x004015A0; // Lib: Basedef.obj Class : (null)
static void (*MobKilled)(int KillerId,int KilledId,int cX,int cY) = (void f_ptr(int,int,int,int)) 0x45AB00; // Lib: Server.obj Class : (null)
static void (*WriteInitItem)(void)                              = (void f_ptr(void)) 0x0040138E; // Lib: Basedef.obj Class : (null)
//static int (*ReadInitItem)(void)                              = (int f_ptr(void)) 0x0040127B; // Lib: Basedef.obj Class : (null)
static void (*InitializeInitItem)(void)                         = (void f_ptr(void)) 0x004012AD; // Lib: Basedef.obj Class : (null)
static void (*GridMulticast)(int, int, int, void*)              = (void (__cdecl*)(int, int, int, void*)) 0x0043FDB0;
static int (*BASE_GetDamage)(int,int,int)                       = (int f_ptr(int,int,int)) 0x00401041; // Lib: Basedef.obj Class : (null)
static void (*SendCarry)(int)                                   = (void f_ptr(int)) 0x00401573; // Lib: SendFunc.obj Class : (null)
static void (*ClearAreaTeleport)(int,int,int,int,int,int)		= (void f_ptr(int,int,int,int,int,int)) 0x00401596; // Lib: Server.obj Class : (null)
static int (*SetAffect)(int,int,int,int)						= (int f_ptr(int,int,int,int)) 0x004015BE; // Lib: Server.obj Class : (null)
static int (*BASE_GetItemSanc)(st_Item*)                        = (int f_ptr(st_Item*)) 0x00401393; // Lib: Basedef.obj Class : (null)
static void (*SaveUser)(int,int)								= (void f_ptr(int,int)) 0x459E40; // Lib: Server.obj Class : (null)
static int (*GetMobAbility)(st_Mob *, unsigned char)            = (int (__cdecl *)(st_Mob *, unsigned char)) 0x00405420;
static int (*PutItem)(int clientID, st_Item* item)				= (int f_ptr(int clientID, st_Item* item)) 0x00401320; // Lib: Server.obj Class : (null)
static st_Mob* (*GetMobFromIndex)(unsigned int)                 = (st_Mob* (__cdecl *)(unsigned int)) 0x00401483; // Lib: Server.obj Class : (null)
static void (*SendClientMessage)(int clientid, char *)          = (void (__cdecl *)(int,char *)) 0x004010FF; // Lib: SendFunc.obj Class : (null)
static void (*SendClientSignalParm)(int,int,unsigned short,int) = (void (__cdecl *)(int,int,unsigned short,int)) 0x0040141A; // Lib: SendFunc.obj Class : (null)
static void (*SendCreateMob)(int,int,int)                       = (void (__cdecl *)(int,int,int)) 0x40160E;
static int (*GetCurKill)(int clientid)                          = (int f_ptr(int)) 0x004014F1; // Lib: GetFunc.obj Class : (null)
static int (*GetTotKill)(int clientid)                          = (int f_ptr(int)) 0x0040130C; // Lib: GetFunc.obj Class : (null)
static void (*SendGuildNotice)(int guildid, char *)             = (void (__cdecl *)(int,char *)) 0x43F190;
static void (*DoTeleport)(int clientid, int dX, int dY)         = (void (__cdecl *)(int,int,int)) 0x004010C8;
static void (*SendEffect)(int, int, int)                        = (void (__cdecl *)(int, int, int)) 0x004010DC;
static void (*SendStats)(int clientid)                          = (void (__cdecl *)(int)) 0x004012C1;
static void (*SendEquip)(int clientid)                          = (void (__cdecl *)(int)) 0x00401069;
static void (*SendScore)(int clientid)                          = (void (__cdecl *)(int)) 0x00401578;
static void (*SendCharList)(int clientid)                       = (void (__cdecl *)(int)) 0x004013B6;
static void (*SaveChar)(int, int)                               = (void (__cdecl *)(int, int)) 0x0040158C;
static void (*SendSay)(int npcID, char *msgToSay)               = (void f_ptr(int npcID, char *msgToSay)) 0x00401140; // Lib: SendFunc.obj Class : (null)
static void (*SendNotice)(char *)                               = (void (__cdecl *)(char *)) 0x00401357;
static void (*SendNoticeArea)(int, int, int, int, char *)       = (void (__cdecl *)(int, int, int, int, char *)) 0x0043F0A0;
static void (*DoTeleportArea)(int, int, int, int, int, int)     = (void (__cdecl *)(int, int, int, int, int, int)) 0x00401596;
static int (*GetUserInArea)(int,int,int,int,char*)				= (int f_ptr(int,int,int,int,char*)) 0x00401348; // Lib: Server.obj Class : (null)
static void (*GenerateSpawn)(int)                               = (void (__cdecl *)(int)) 0x004011CC;
static void (*ClearArea)(int x_min, int y_min, int x_max, int y_max)		= (void f_ptr(int,int,int,int)) 0x0040106E; // Lib: Server.obj Class : (null)
static void (*ClearAreaLevel)(int,int,int,int,int lvl_min, int lvl_max)		= (void f_ptr(int,int,int,int,int,int)) 0x00401244; // Lib: Server.obj Class : (null)
static void (*SaveAll)(void)                                    = (void (__cdecl *)(void)) 0x004014B0;// Usado no comando de gm, envia todos os personagens para tela de escolha.
static void (*Reboot)(void)                                     = (void (__cdecl *)(void)) 0x0045A1F0;
static int  (*GetUserByName)(char *)                            = (int (__cdecl *)(char *)) 0x004010FA;
static void (*CloseUser)(int)                                   = (void (__cdecl *)(int)) 0x00459440;// Da DC no personagem
static void (*sendinv1)(int)                                    = (void (__cdecl *)(int)) 0x00401578;// Usado no SendALL
static void (*sendinv2)(int)                                    = (void (__cdecl *)(int)) 0x00401573;// Usado no SendALL
static void (*sendstats)(int)                                   = (void (__cdecl *)(int)) 0x004012C1;// Usado no SendALL
static void (*sendequip)(int)                                   = (void (__cdecl *)(int)) 0x00401069;// Usado no SendALL
static void (*GridMulticast_2)(int, int, void*, int)            = (void (__cdecl*)(int, int, void*, int)) 0x004409C0;
static void (*SendItem)(int clientID, int itemSlotPlace, int itemSlot, st_Item *item) = (void f_ptr(int clientID, int itemSlotPlace, int itemSlot, st_Item *item)) 0x004015C3; // Lib: SendFunc.obj Class : (null)
static void (*SendEtc)(int)                                     = (void f_ptr(int)) 0x004012C1; // Lib: SendFunc.obj Class : (null)
static int (*GetUserFromSocket)(int)							= (int f_ptr(int)) 0x0040115E; // Lib: Server.obj Class : (null)
static int (* _AddMessage)(BYTE *,int)							= (int f_ptr(BYTE *,int)) 0x4198C0; // Lib: CPSock.obj Class : CPSock
static char (* ReadMessage)(int *,int *)						= (char f_ptr(int *,int *)) 0x419280; // Lib: CPSock.obj Class : * CPSock
static void (*GenerateMob)(int,int,int)							= (void f_ptr(int,int,int)) 0x004011CC; // Lib: Server.obj Class : (null)
static void (*RebuildGenerator)(void)							= (void f_ptr(void)) 0x004013E3; // Lib: Server.obj Class : (null)
static void (*LoadSkillData)()									= (void f_ptr()) 0x040E0D0;
static void (*BASE_InitializeItemList)(void)                    = (void f_ptr(void)) 0x00401532; // Lib: Basedef.obj Class : (null)
static void (*ReadConfig)(void)									= (void f_ptr(void)) 0x004015F5; // Lib: Server.obj Class : (null)
static void (*CloseUser_OL2)(int)                               = (void (__cdecl *)(int)) 0x004012A3; // Lib: Server.obj Class : (null)
static int  (*Rand)()                                           = (int f_ptr())0x4633E0;
static void (*ProcessMinTimer)(void)                            = (void (__cdecl *)(void)) 0x00455B60;
static int (*CreateMob)(char*,int,int,char*)					= (int f_ptr(char*,int,int,char*)) 0x004013F7; // Lib: Server.obj Class : (null)
static int (*GenerateSummon)(int,int,struct STRUCT_ITEM*)		= (int f_ptr(int,int,struct STRUCT_ITEM*)) 0x004014CE; // Lib: Server.obj Class : (null)
static int (* _SendOneMessage)(BYTE *buffer, int size)	        = (int f_ptr(BYTE *,int)) 0x004012B7; // Lib: CPSock.obj Class : CPSock
static int (*BASE_GetEmptyMobGrid)(int, int *, int *)           = (int (__cdecl *)(int, int*, int*)) 0x00401401; // Lib: GetFunc.obj Class : (null)
static char* (__stdcall* inet_n2a)(IN_ADDR in_addr)             = (char* (__stdcall*)(IN_ADDR))0x00463364;
static int (*BASE_GetCreateMob)(int, BYTE *)                    = (int (__cdecl *)(int, BYTE*)) 0x00401136;
static void (*SendSetHpMp)(int)                                 = (void f_ptr(int)) 0x0040156E; // Lib: SendFunc.obj Class : (null)
static void (*SendRemoveParty)(int,int)                         = (void f_ptr(int,int)) 0x004014BA;
//static void (*RemoveParty_)(int)								= (void f_ptr(int)) 0x00401366; // Lib: Server.obj Class : (null)
static void (*WarGate)(int)                                     = (void (__cdecl *)(int)) 0x457260;
static int (*GetCreateMob)(int clientID, BYTE*)                 = (int f_ptr(int clientID, BYTE*)) 0x00401136; // Lib: GetFunc.obj Class : (null)
static void (*GridMulticast_OL2)(int posX, int posY, BYTE* packetBuffer, int zero) = (void f_ptr(int posX, int posY, BYTE* packetBuffer, int zero)) 0x004013A7; // Lib: SendFunc.obj Class : (null)
static unsigned char (*GetAttribute)(int,int)                   = (unsigned char f_ptr(int,int)) 0x004014AB; // Lib: GetFunc.obj Class : (null)
//static void (*SetReqHp)(int)									= (void f_ptr(int)) 0x00401492; // Lib: Server.obj Class : (null)
//static void (*SetReqMp)(int)									= (void f_ptr(int)) 0x004011A9; // Lib: Server.obj Class : (null)
static int (*BASE_GetBonusItemAbility)(st_Item *,unsigned char) = (int f_ptr(st_Item *,unsigned char)) 0x004011E0; // Lib: Basedef.obj Class : (null)
static int (*GetPKPoint)(int)                                   = (int f_ptr(int)) 0x004012FD; // Lib: GetFunc.obj Class : (null)

static void Buff(int ClientID, int time1, int time2, int skill)
{
	int buff_addr = 0x04015BE;
	_asm
	{
		PUSH time1
		PUSH time2
		PUSH skill
		PUSH ClientID
		CALL buff_addr
		ADD ESP,0x010
	}
}

static void GetCurrentScore(int clientid)
{
	int getscore_addr = 0x040149C;
	int addr_bclient = clientid * 0x0410;

	int addr = addr_bclient + 0x015C69B8;
	_asm
	{
		MOV ECX,clientid
		PUSH ECX
		MOV ECX,addr
		CALL getscore_addr
	}
}

static void SendDBPacket(BYTE *Buffer, int tamanho)
{
	static int clientid = Buffer[6];
	static int calleu = 0x4012B7;
	static int trem = 0x7B318E0;
	static int tremm = 0x0A16990;
	__asm
	{
		MOV ECX,clientid
		IMUL ECX,ECX,0xC4C
		MOV [ECX+trem],0xD

		PUSH tamanho
		PUSH Buffer
		MOV ECX,tremm
		CALL calleu
	}
}
#endif // __NATIVE_FUNCTIONS_H__