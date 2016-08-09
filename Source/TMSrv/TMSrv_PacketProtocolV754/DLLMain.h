// ---
// by ptr0x
// ---

#ifndef _DLL_MAIN_H_
#define _DLL_MAIN_H_

#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#include "PE_Patch.h"
#include "PE_DefConst.h"
#include "../ItemEffect.h"

// Funcs para uso indireto
void RefinarItemMais(st_Item *item, int value);
int GetChanceRefOdin(st_Item *Item);
void SendLog(char *Who, char *msg, ...);
void s334(INT32 clientId, char *message);
void ReadDonateList();
void ReadResetList();
void ReadMessageList();
void ReadArchFile();
void ReadEvent();
void ReadAllData();
UINT8 DayOfWeek();
bool SaveAccount(int clientId);
bool isVip(int index);
bool file_exists(const char *filename);
bool bFile_exists(const char *filename);
FindAmountItem FindOcurrences(st_Item *Item, int index);
void Sendpack(BYTE *bufr, int clientId, int paksize);
void AmountMinus(st_Item *item);
void SendALL(int clientid);
int GetItemSanc(st_Item *item);
int GetFirstSlot(int clientId, int itemId, int itemType);
void SetItemSanc(st_Item *item, int value);
void WINAPI MainThread();
void NpcsAlive(int clientid, int vivos, int total);
INT32 CheckItems(st_Window *pServer);
void Composition(st_Window *pServer, st_Mob *player);
INT64 SystemTimeDifference(const SYSTEMTIME time1, const SYSTEMTIME time2);
bool FileExist(const char* Name );
bool CheckBan(const char *login);
void SendBan(const char *login);
void SendBan(const char *login, SYSTEMTIME banTime);
bool SaveGuilds();
void ReadGuildFile();
void ReadEventFile();
void TeleportWar();
int  GetCity(int cId);
bool PutItemnInv(INT16 cId, st_Item *Item);
void OpenTrade(short ClientID, short MobID);
void SendAllTrade(short ClientID, short MobID);
void CloseTrade(short ClientID);
void CheckItensOnTrade(short ClientID, short MobID);
bool CanTrade(UINT16 Index);
bool AddItensOnTrade(SendTrade *p);
BYTE GetAmountItemOnTrade(short ClientID);
BYTE GetAmountItem(WORD clientid);
void PutAsWinner(INT8 WarNum, INT8 Winner);
int GetTeamAlive(INT8 WarNum, INT8 Team);
void WINAPI PremiumDelivery();
bool CheckArchItem(int id);
bool CheckHardItem(int id);
st_Item* GetItemPointer(st_Mob* mob, st_Item* cargo, int type, int pos);
unsigned long int GetCoinOnItens(st_Item *Inventory);
void sD1D(int clientid, int destino, char *msg, int cor);
void SendPartyChat(int clientId, char *message);
void SendToALL(BYTE *szBuffer, int PacketSize);
bool PutAddOnItem(st_Item *Item, UINT8 ef1, UINT8 ef2, UINT8 efv1, UINT8 efv2);
void DecrementWaterTime();
void VerifyPesa(int cId);
void VerifyQuests(INT16 cId);
void VerifyWarArea(INT16 cId);
void SendWarInfo(char *Message);
void LettersTime();
UINT16 DefineGuildWinner();
bool CheckMount(st_Item *Item, INT16 Mount);
void SendClientMsg(int cID, char *msg, ...);
void KillMobsOnArea(int x1, int y1, int x2, int y2);
void TeleportPeople(INT16 *cIds, INT16 destX, INT16 destY);
void OitavaHT(int ClientID, int OtherID);
void CheckItemTime(st_Item *Item);
void TimeLimitCheck(st_Item *Item, INT16 cId, bool Fairy, char* Name);
bool isSubLider(char *Name, UINT16 GuildID);
void UpdateGuildInfo(INT16 cId);
void UpdateMGuildInfo(UINT16 GuildIndex);
void SendGuildChat(UINT16 GuildIndex, char *Msg);
INT32 GetMatchCombine(st_Item* pItem);
INT8 ReturnItemAmount(st_Item *Item);

// Volatiles
void Replations(UINT8* m_PacketBuffer, bool* pRetn);
void Barras(UINT8* m_PacketBuffer, bool* pRetn);
void DesagruparPoeiras(UINT8* m_PacketBuffer, bool* pRetn);
void AgruparPoeiras(UINT8* m_PacketBuffer, bool* pRetn);
void ProcessHuntingScrolls(BYTE *m_PacketBuffer, bool* pRetn);
void MoneyCube(BYTE *m_PacketBuffer, bool* pRetn);
void ProcessSephiraBook(UINT8* m_PacketBuffer, bool* pRetn);
void UseLac(BYTE *m_PacketBuffer, bool *pRetn);
void Gemas(BYTE *m_PacketBuffer, bool *pRetn);
void Tinturas(BYTE *m_PacketBuffer, bool* pRetn);
void RemoveTinturas(BYTE *m_PacketBuffer, bool* pRetn);
void RecallRvR(BYTE *m_PacketBuffer, bool *pRetn);
void NightMare(BYTE *m_PacketBuffer, bool *pRetn);
void Ideal(BYTE *m_PacketBuffer, bool *pRetn);
void Water(BYTE *m_PacketBuffer, bool *pRetn);
void CurarMontaria(BYTE *m_PacketBuffer, bool *pRetn);
void DonateBars(BYTE *m_PacketBuffer, bool *pRetn);
void NewInv(BYTE *m_PacketBuffer, bool *pRetn);
void Cristais(BYTE *m_PacketBuffer, bool *pRetn);
void Lac100(BYTE *m_PacketBuffer, bool *pRetn);
void CatalizarLevel(BYTE *m_PacketBuffer, bool *pRetn);
void Pots(BYTE *m_PacketBuffer, bool *pRetn);
bool Powder(int Index, int Effect, st_Item *dstPtr);
void BauExp(BYTE *m_PacketBuffer, bool *pRetn);
void Lans(BYTE *m_PacketBuffer, bool *pRetn);
void Misteriosa(BYTE *m_PacketBuffer, bool *pRetn);
void ChocAmor(BYTE *m_PacketBuffer, bool *pRetn);
void Fogos(UINT8* m_PacketBuffer, bool *pRetn);
void Joias(BYTE *m_PacketBuffer, bool *pRetn);
void Extracoes(BYTE *m_PacketBuffer, bool *pRetn);
void CaosPoint(UINT8* m_PacketBuffer, bool *pRetn);
void Frango(BYTE *m_PacketBuffer, bool *pRetn);
void SeloGuerreiro(BYTE* m_PacketBuffer, bool *pRetn);
void QuestItens(BYTE* m_PacketBuffer, bool *pRetn);
void PedraFuria(BYTE* m_PacketBuffer, bool *pRetn);
void Item_VIP(BYTE* m_PacketBuffer, bool *pRetn);
void BossWater(BYTE* m_PacketBuffer, bool *pRetn);
void BarrasMithril(BYTE* m_PacketBuffer, bool *pRetn);
void Cartas(UINT8 *m_buffer, bool *pRetn);
void RestaurarMontarias(BYTE* m_PacketBuffer, bool *pRetn);
void RemoveCancel(BYTE* m_PacketBuffer, bool *pRetn);
void MolarGargula(UINT8* m_PacketBuffer, bool *pRetn);

// Npcs
void CarbWind(INT16 cId, INT16 npcId);
void NpcDeTroca(INT16 cId, INT16 npcId);
void Unis(INT16 cId, INT16 npcId, INT8 QuestId);
void Khadin(INT16 clientId, INT16 npcId);
void GodGovernament(INT16 clientId, INT16 npcId);
void Kibita(INT16 clientId, INT16 npcId);
void Sephirot(BYTE *m_PacketBuffer, bool *pRetn);
void Perzens(BYTE *m_PacketBuffer, bool *pRetn);
void Juli(BYTE *m_PacketBuffer, bool *pRetn);
void KingDom(BYTE* m_PacketBuffer, bool *pRetn);
void Oraculo(BYTE* m_PacketBuffer, bool *pRetn);
void EntradasQuest(INT16 clientId, INT16 npcId, INT8 questIndex);
void QuestCapaVerde(BYTE* m_PacketBuffer, bool *pRetn);
void GuardaReal(BYTE* m_PacketBuffer, bool *pRetn);
void KingDomBroker(INT16 clientId, INT16 npcId);
void MestreHab(INT16 clientId, INT16 npcId);
void Arch(BYTE* m_PacketBuffer, bool *pRetn);
void Cosmos(INT16 cId, INT16 npcId);
void Compounder(BYTE *packetBuffer, bool *pRetn);
void Lindy(UINT8 *packet, bool *pRetn);

// Funcs que são hookadas 
void GetCurScore_CapeInfo(st_Mob* player);
void Server_ProcessMinTimer();
void HKD_BASE_GetCurrentScore_FixStatus(st_Mob &mob, stAffects *affect);
void GetCurScore(st_Mob *player, INT32 clientid);
void __stdcall HKD_BASE_GetCurrentScore_BlockStatus(INT32 clientid);
void HKD_ProcessClientMessage_UseMountFeed(WORD *mountId, WORD feedId);
void HKD_CloseUser(int clientId);
void __stdcall HKD_ProcessDBMessage_LoadBuffs(INT32 clientid);
void __stdcall HKD_ControlEXP(INT32 clientid, INT32 exp, INT32 type);
INT32 HKD_ExpInPesaAllArea(UINT32 ClientID, INT32 X, INT32 Y);
int HKD_GenerateSummon_CanSummon(int mobId, int faceId);
int HKD_BASE_GetBonusSkillPoint(st_Mob* mob);
bool ReadEvokFile(char *szMob, int evokId);
bool HKD_BASE_CanEquip(st_Mob *player);
INT32 __stdcall HKD_CheckGetLevel_FixClass(st_Mob &player);
void __stdcall HKD_ControlCheckGetLevel(int mPointer, short *mPoints);
INT32 __stdcall HKD_GetItemSanc_FixSanc(st_Item* item);
INT32 HKD_ProcessClientMessage_ApplyBonus(BYTE *buffer, INT32 clientid);
bool HKD_CorrectPositionGoWorld(INT32 ClientID, INT16* PosX, INT16* PosY);
INT32 HKD_ControlTeleportPosition(INT16 clientId, INT16 *ptrX, INT16 *ptrY);
void LimitPlayers();
INT32 GetParryRate(st_Mob *player, INT32 Parry);
INT32 __stdcall HKD_GetParryRate_FixEvasion(INT32 clientid, INT32 otherClientId, INT32 parry);
bool __stdcall HKD_FixTrainningCamp(INT32 clientid);
void __stdcall HKD_Base_GetCurrentScore_FixTrans(st_Mob &player, INT32 transId);
void __stdcall HKD_Base_GetCurrentScore_FixFaceArch(st_Mob &player);
void __stdcall FixMaxLevel(INT32 clientid, INT16 type);
void __stdcall HKD_ProcessAttack(INT32 otherConn, INT32 clientid, INT32 damage);
int BASE_GetHpMp(st_Mob* mob);
int BASE_GetBonusScorePoint(st_Mob* mob);
INT32 BuySkillCele(INT32 ClientID);
void HKD_ProcessClientMessage_Command(p334 *p);
void RegenMob(int User);
void HKD_ProcessClientMessage_KickPlayer(BYTE *packetBuffer);
void RemoveParty(INT32 Cid);
void __stdcall NKD_SystemTrade(BYTE *m_PacketBuffer, int ClientID);
int __stdcall HKD_ChangeDamage(DWORD attacked, DWORD attacker, DWORD Damage);

// Funções chamadas no PacketControl
void CreateChar(BYTE *m_PacketBuffer, bool *pRetn);
void RecruitPerson(UINT8* m_PacketBuffer, bool* pRetn);
void Commands(BYTE* m_PacketBuffer, bool *pRetn);
void DoLogin(BYTE *m_PacketBuffer, bool *pRetn);
void SendWorld(BYTE *m_PacketBuffer);
void FixAddPoint_CLIENT(BYTE *m_PacketBuffer, bool *pRetn);
void UpdateCharListStructure(st_CharList* newCharList, BYTE *m_PacketBuffer);
void UseNpcs(BYTE *m_PacketBuffer, bool *pRetn);
void ReceiveBets(BYTE *m_PacketBuffer, bool *pRetn);
void UseItens(BYTE *m_PacketBuffer, bool *pRetn);
void FixBuyItem_SERVER(BYTE *m_PacketBuffer, bool *pRetn);
void Control37A(BYTE *m_PacketBuffer, bool *pRetn);
void Control398(BYTE *m_PacketBuffer, bool *pRetn);
void VerifyItemMovement(BYTE *m_PacketBuffer, bool *pRetn);
void ChangeSkillBar(BYTE* m_PacketBuffer, bool *pRetn);
void Agatha(BYTE *m_PacketBuffer, bool *pRetn);
void Tiny(BYTE *m_PacketBuffer, bool *pRetn);
void Ehre(BYTE *m_PacketBuffer, bool *pRetn);
void Ailyn(BYTE *m_PacketBuffer, bool *pRetn);
void Odin(BYTE *m_PacketBuffer, bool *pRetn);
void Numerica(BYTE *m_PacketBuffer);
void MovePlayer(BYTE* m_PacketBuffer, bool *pRetn);
void Shany(UINT8 *m_PacketBuffer, bool *pRetn);

// Variáveis extern
extern GuildInfos Guilds[0xFFFF];
extern Aguas     Agua[3];
extern Pesas     Pesa[3];
extern Quests    QuestList[5];
extern Donate    DonateList[300];
extern CUser     Users[1000];
extern Resets    ResetList[50];
extern Messages  MessageList[50];
extern WarInfos  War;
extern wdBase    wdBuffer[750];
extern stBuffer  mBuffer[30000];
extern st_TransBonus TransBonus[5];
extern stMOBGener Genner[10000];
extern stMOB754 MobArch;
extern st_ItemListCSV ItemList[6500];
extern st_MountData MountBuffer[50];
extern st_Trade Trade[1000];
extern ServerInfos Server;
extern CartasQuest Carta;
extern FILE *pLogFile;

// Defines

#define SERV_1 1
#define SERV_2 2

#define xX 0
#define XX 2
#define yY 0
#define YY 2

#define Segunda 0
#define Terça 1
#define Quarta 2
#define Quinta 3
#define Sexta 4
#define Sabado 5
#define Domingo 6

#define SIMPLES 1
#define PLUS 2

#define MORTAL 1
#define ARCH 2
#define CELESTIAL 3
#define SCELESTIAL 4
#define HARDCORE 5
#define SHARDCORE 6

#define EQUIP 0
#define INVENTORY 1
#define CARGO 2

#define MSG_COLOR_DONATE 0xFFFFA54F
#define MSG_COLOR_NOTICE 0xFFFF8C00
#define MSG_COLOR_GRITO  0xFF00CD00
#define MSG_COLOR_GRITOV 0xFFA62A2A
#define MSG_COLOR_GRITOA 0xFFD9D919
#define MSG_COLOR_GIFT   0xFFFFE4E1

#define NORMAL_PLAYER 0
#define TESTING_MOD 1
#define REAL_MOD 2
#define ADMIN 3

#define ELMO_TYPE 2
#define PEITO_TYPE 4
#define CALCA_TYPE 8
#define LUVA_TYPE 16
#define BOTA_TYPE 32
#define ARMA_TYPE1 192
#define ARMA_TYPE2 64
#define ESCUDO_TYPE 128

#define MAX_ITEMLIST 6500
#define MAX_PLAYER 1000
#define MAX_USER_WAR 26
#define MAX_AFFECTS 16

#define GetUserFromMob(mob) (((int)mob - 0x15C69B8) / 0x410)
#define StartThread(thread) (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, 0))

#define MAX_HPMP 32000

#endif // _DLL_MAIN_H_