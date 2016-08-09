#ifndef __BASE_STRUCTURES_H__
#define __BASE_STRUCTURES_H__

#include <Windows.h>
#include <time.h>

typedef struct
{
	INT16 Size; // 0 - 1

	INT8 Key; // 2
	INT8 CheckSum;//3

	INT16 PacketId; //4 - 5
	INT16 ClientId;

	UINT32 TimeStamp;
} PacketHeader;

typedef struct
{
	INT16 X;
	INT16 Y;
} st_Position;

struct st_Item
{
	INT16 Index;

	struct
	{
		UINT8 Index;
		UINT8 Value;
	} Effect[3];
};

#define EF1 Effect[0].Index
#define EFV1 Effect[0].Value
#define EF2 Effect[1].Index
#define EFV2 Effect[1].Value
#define EF3 Effect[2].Index
#define EFV3 Effect[2].Value

typedef struct
{
	INT16 Level;   //36-37 64-65
	INT16 Defense; //38-39 66-67
	INT16 Attack;  //40-41 68-69

    struct
    {
        UINT8 Merchant : 4;
        UINT8 Direction : 4;
    } Merchant;    //42 70

    struct 
	{
		BYTE Speed : 4;
		BYTE ChaosRate : 4;
	} Move;        //43 71 
	      
	UINT16 maxHP, //44-45 72-73
		   maxMP; //46-47 74-75

	UINT16 curHP, //48-49 76-77
		   curMP; //50-51 78-79

	INT16 STR, //52-53 80-81
		  INT, //54-55 82-83
	      DEX, //56-57 84-85 
	      CON; //58-59 86-87

	UINT8 Mastery[4]; //60-63 88-91
} st_Status;

struct stAffects
{
	UINT16 Index;
    UINT16 Master;
    UINT16 Value;
    UINT16 Time;
};

typedef struct
{
	char Name[16];
    char CapeInfo;

	struct
    {
        UINT8 Merchant : 6;
        UINT8 CityID : 2;
    } Info;

    UINT16 GuildIndex;
    UINT8 ClassInfo;

    union
    {
        struct
        {
            UINT8 SlowMov : 1;
            UINT8 DrainHP : 1;
            UINT8 VisionDrop : 1;
            UINT8 Evasion : 1;
            UINT8 Snoop : 1;
            UINT8 SpeedMov : 1;
            UINT8 SkillDelay : 1;
            UINT8 Resist : 1;
        };

        UINT8 Value;
    } AffectInfo;

    UINT16 QuestInfo;
    INT32 Gold;
    UINT32 Exp;

    st_Position LastPosition;

    st_Status bStatus;
	st_Status Status;

    st_Item Equip[16];
	st_Item Inventory[64];

    UINT32 Learn;

    UINT16 StatusPoint,
		 MasterPoint,
		 SkillPoint;

	UINT8 Critical;
    UINT8 SaveMana;

    INT8 SkillBar[4];

    INT8 GuildMemberType;

    UINT8 MagicIncrement;
    UINT8 RegenHP,
		  RegenMP;

	INT8 Resist1,
		 Resist2,
		 Resist3,
		 Resist4;

	stAffects Affects[4];	

	UINT32 Mode;                                               // 788 a 791
	UINT32 Leader;                                             // 792 a 795
	UINT32 Formation;                                  // 796 a 799
	UINT32 RouteType;                                  // 800 a 803

	UINT32 LastX;                                              // 804 a 807
	UINT32 LastY;                                              // 808 a 811
	UINT32 LastTime;                                   // 812 a 815
	UINT32 LastSpeed;                                  // 816 a 819

	UINT32 TargetX;                                    // 820 a 823
	UINT32 TargetY;                                    // 824 a 827

	UINT32 NextX;                                              // 828 a 831
	UINT32 NextY;                                              // 832 a 835
	UINT32 NextAction;                                 // 836 a 839

	UINT8 Route[24];                                 // 840 a 863

	UINT32 WaitSec;                                    // 864 a 867

	UINT32 PosX;                                               // 868 a 871
	UINT32 PosY;                                        // 872 a 875
 
	UINT32 Segment;                                    // 876 a 879
	UINT32 DeltaExp;									//880 a 883 
	UINT32 SegmentX;                                   // 884 a 887
	UINT32 SegmentY;                                   // 888 a 891
	UINT32 SegmentListX[5];                    // 892 a 911
	UINT32 SegmentListY[5];                    // 912 a 931
	UINT32 SegmentWait[5];                             // 932 a 951
	UINT32 SegmentDirection;                   // 952 a 955
	UINT32 SegmentProgress;                    // 956 a 959
 
	UINT32 GenerateIndex;                              // 960 a 963
	UINT16 CurrentTarget;                    // 964 a 965
	UINT16 EnemyList[4];                             // 966 a 973
	INT16 PartyList[12];                    // 974 a 997
 
	UINT16 Unk1;                                             // 998 a 999
 
	UINT32 WeaponDamage;                               // 1000 a 1003
	UINT32 Summoner;                                   // 1004 a 1007
	UINT32 PotionCount;                                // 1008 a 1011
	INT32 Parry;                                       // 1012 a 1015
	UINT32 GuildDisable;                               // 1016 a 1019
	UINT32 DropBonus;                                  // 1020 a 1023 //Diamante
	UINT32 ExpBonus;                                   // 1024 a 1027 //Coral
	UINT32 ForceDamage;                                // 1028 a 1031 //Esmeralda
	UINT32 ReflectDamage;                              // 1032 a 1035 //Garnet
 
	UINT32 Unk2;	
} st_Mob;

typedef struct
{
    int SkillPoint;
    int TargetType;
    int ManaSpent;
    int Delay;
    int Range;
    int InstanceType;
    int InstanceValue;
    int TickType;
    int TickValue;
    int AffectType;
    int AffectValue;
    int AffectTime;
    char Act_1[8];
    //char Act_2[8]; - só p/ 7xx
    int InstanceAttribute;
    int TickAttribute;
    int Aggressive;
    int Maxtarget;
    int PartyCheck;
    int AffectResist;
    int Passive_Check;
} st_AffectData;

typedef struct
{
	DWORD AtaqFisico;
	DWORD AtaqMagico;
	DWORD Evasao;
	DWORD Resistencia;
	DWORD VelocidadeMov;
} st_MountData;

struct sTransBonus
{
	INT32 MinDamage;
	INT32 MaxDamage;
	INT32 MinDefense;
	INT32 MaxDefense;
	INT32 MinHP;
	INT32 MaxHP;
	INT32 Unk1[2];
	INT32 SpeedAttack;
	INT32 SpeedMove;
	INT32 Unk2[6];
	INT32 Sanc;	
} st_TransBonus;

typedef struct
{
	//# Index,Name,Mesh-Texture,REQ_SIDC,Unique,EF_PRICE,EF_POS,Extreme,Grade,N0,V0,N1,V1,N2,V2,N3,V3,N4,V4,N5,V5,N6,V6,N7,V7,N8,V8,N9,V9,N10,V10,N11,V11//
	//"%d,%64s,%d.%d,%d.%d.%d.%d.%d,%d,%d,%d,%d,%d,
	//"%d,%64s,%d.%d,%d.%d.%d.%d.%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"
    char Name[64];
	
    short mesh1;
	short mesh2;

	short unknow;

    short Level;
    short STR;
    short INT;
    short DEX;
    short CON;

    struct {
        short index;
        short value;
    } Effect[12];

    int Price;
    short Unique;
    WORD Pos;

    short Extreme;
    short Grade;
} st_ItemList;

typedef struct
{
	char Name[27];

	short Mesh1;
	short Mesh2;

	short Unknow;

	struct
	{
		short Level;
		short Str;
		short Int;
		short Dex;
		short Con;
	} REQ_SIDC;

	struct {
        short Index;
        short Value;
    } Effect[12];

	int Price;
    short Unique;
    WORD Pos;

    short Extreme;
    short Grade;
} st_ItemListCSV;

struct p334{
    PacketHeader Header;
    char Cmd[16];
    char Arg[96];
};

struct Donate
{
	st_Item Item;
	UINT8 Price;
	UINT16 Store;
};

struct Quests
{
	UINT8 CidID[40];
};

struct Pesas
{
	UINT8 Groups;
	INT16 CIDS[3][13];
	UINT8 NpcsAlive;
	bool Status;
	INT16 TimeLeft;
};

struct Room
{
	bool isActive;

	UINT8 MobsLeft;
	INT16 Cids[13];
	INT16 Leaders;

	UINT8 TimeLeft;
};

struct Aguas
{
	Room Rooms[9];
};

struct Resets
{
	UINT8 Time;
	st_Position MinCoords,
		        MaxCoords;
    UINT16 MinLevel,
		   MaxLevel;
};

struct p376
{
    PacketHeader Header;
    BYTE DstType;
    BYTE DstSlot;
    BYTE SrcType;
    BYTE SrcSlot;
    int Unknown;
};

struct DropEvent
{
	bool isOn;

	UINT8 Rate;
	WORD Id;

	UINT32 Quantity;
	UINT32 Dropped;
};

struct Messages
{
	UINT8 Time;
	char Msg[108];
};

struct st_CharList
{
	st_Position Position[4]; // 0
	char Name[4][16]; // 16
	st_Status Status[4]; // 80
	st_Item Equip[4][16]; // 192

	INT16 GuildId[4]; // 704
	INT32 Gold[4]; // 712
	INT32 Experience[4]; //728
}; // 744

struct st_Socket
{
	INT32 FD; // 0-32
	INT8* SendBuffer; // 4-36
	INT8* RecvBuffer; // 8-40
	
	INT32 SizeOfSend; // 12-44
	INT32 SizeOfRecv; // 16-48
		
	INT32 IndexOfRecv; // 20-52
	INT32 IndexOfSend; // 24-56
		
	INT32 Hello; // 28-60
}; // 32 - 64
struct CUser
{
	char Username[16]; // 0
	INT32 CharPosition; //16
	IN_ADDR In_Addr; // 20
	//inet_n2a(user->In_Addr);
	INT32 Status; // 24
	INT32 IsAutoTrading; // 28
 
	st_Socket Service; // 32
 
	INT8 Unknown_64[404]; //64
 
	struct
	{
		st_Item Item[128]; // 468
		INT32 Gold; // 1492
	} Storage;
 
	INT16 AttackCount; // 1496
	INT16 Unknown_1498; // 1498
 
	struct
	{
		PacketHeader Header; // 1500
 
		st_Item Item[8]; // 1512
		INT8 Slots[8]; // 1576
  
		INT32 Gold; // 1584
  
		bool Accept; // 1588;
  
		INT8 Unknown_1589; // 1589
  
		INT16 OtherClientId; // 1590
	} Trade;
 
	struct
	{
		PacketHeader Header; // 1592
 
		char Name[24]; // 1604
  
		st_Item Item[12]; // 1628
		INT8 Slots[12]; // 1724
  
		INT32 Price[12]; // 1736
  
		INT16 Unknown_1784; // 1784
  
		INT16 Index; // 1786
	} AutoTrade;
 
	struct
	{
		INT32 LastType; // 1788
 
		INT32 TimeStamp; // 1792
	} Attack;
 
	INT32 Unknown_1796; // 1796
 
	struct
	{
		INT32 PacketId; // 1800
		INT32 TimeStamp; // 1804
	} Movement;
 
	INT32 IllusionTime; //1808
 
	UINT32 CrackErrorCount; // 1812
 
	INT32 Billing; // 1816
 
	st_CharList CharList; //1820
 
	char LastWhisper[16]; // 2564
 
	INT32 IsBillConnect; // 2580
	char UserStatus[4]; // 2584
  
	struct
	{
		PacketHeader Header;
   
		INT32 nCommand;
		INT32 nDummy[4];
	} Session;
 
	INT8 SkillBar[8]; //2620
 
	INT32 nTargetX; // 2628
	INT32 nTargetY; // 2632
 
	struct
	{
		INT32 Whisper; // 2636
		INT32 Guild; // 2640
		INT32 Party; // 2644
		INT32 Chat; // 2648
  
		INT8 AutoTradeName[24]; // 2652
 
		INT32 PK; // 2676
	} AllStatus;
 
	struct
	{
		UINT32 CountHp; // 2680
		UINT32 CountMp; // 2684
  
		INT32 bQuaff; // 2688;
	} Potion;
 
	INT32 AdapterKeys[4]; // 2692
 
	struct
	{
		INT32 Mode; // 2708
		INT32 Index; // 2712
  
		INT32 ClassId; // 2716 - confirmar.
	} Challenger;
 
	INT32 LastReceiveTime; // 2720
	INT32 Admin; // 2724
 
	INT32 Child; // 2728
	INT32 CheckBillingTime; // 2732
	INT32 CharLoginTime; // 2736
 
	INT32 Range; // 2740
 
	INT8 Unknown_2744[404]; // 2744
}; // 3148

struct p36b // Request Refresh Itens 754
{
    PacketHeader Header;
    WORD ItemEff[16];
    BYTE pAnctCode[16];
};
 
struct p36b_613 // Request Refresh Itens 613
{
    PacketHeader Header;
    WORD ItemEff[16];  
};

typedef struct
{
    bool isTrading;
    bool WaitingData;
    bool Confirm;
 
    DWORD Gold;
    clock_t Timer;
       
    WORD ClientID;
 
    st_Item Itens[15];
    char TradeItemSlot[15];
} st_Trade;

typedef struct
{
    PacketHeader Header;
 
    st_Item TradeItem[15];
    char TradeItemSlot[15];
 
    BYTE Unknow;
 
    DWORD Gold;
    bool Confirma;
    WORD OtherClientid;
} SendTrade;

struct stTime
{
	UINT8 Dia,
		  Mes,
		  Hor,
		  Min,
		  Seg;
	UINT16 Ano;
};

struct WarInfos
{
	// Guerras cidades (Armia, Erion, Azran, Gelo, Noatum)
	UINT8  Tax[5];     // Taxa dos impostos por cidade
	UINT8  Kingdom[5]; // Reino da guild vencedora, para comparações do dragão.

	INT8  TeamCount[4][2]; // Número de jogadores em cada time na war

	INT16 OwnerTeam[4][26], // ClientId dos jogadores defensores na war
		  DefyTeam[4][26];  // ClientId dos jogadores desafiadores na war

	UINT16 Owner[5];    // GuildID dominante
	UINT16 BetIndex[4][2]; // Index da guild com maior aposta
	UINT16 WarIndexs[4][2]; // Defensora/desafiante

	UINT32 BetValue[4]; // Valor total das apostas  em fame
	
	UINT64 CityTaxs[5]; // Soma total dos impostos

	char   DraggonOwner[16]; // Caso alguém possua tudo, ganha o dragao
	char   Coroado[16];   // Dono da coroa, aquele quem conquistou Noatum

	bool   Iniciada[5],   // Se a guerra começou
		   Finalizada[5], // Se terminou
		   Delivered[5];  // Prêmio foi entregue ?

	// Guerra Noatum
	UINT8  ThorTime; // Tempo no Altar
	char   ChallengerName[16]; // Nome de quem está tentando dominar o altar
	bool   HasWinner;

	// RvR
	UINT8  Winner,
		   BonusExp;
	UINT16 RedKills,
		   BlueKills;

	bool   InitializeWar,
		   FinalizedWar,
		   MsgSended;
};

typedef struct 
{
	// Este é um exemplo de quests
	// Como o valor é UINT64, são 64 bits, ou seja, 64 quests

	// Level feito o celestial
	UINT64 Level355 : 1;
	UINT64 Level370 : 1;
	UINT64 Level380 : 1;
	UINT64 Level398 : 1;
	UINT64 Level399 : 1;

	// Cristais Arch
	UINT64 CristalElime : 1;
	UINT64 CristalSylphed : 1;
	UINT64 CristalThelion : 1;
	UINT64 CristalNoas : 1;

	// Selo do Guerreiro
	UINT64 SeloArch355 : 1;

	// Arcana
	UINT64 Arcana : 1;

	// Adicionais SubCele
	UINT64 Add120 : 1;
	UINT64 Add151 : 1;
	UINT64 Add180 : 1;
	UINT64 Add199 : 1;

	// Resets Subcelestial
	UINT64 Reset_1 : 1;
	UINT64 Reset_2 : 1;
	UINT64 Reset_3 : 1;
	UINT64 Reset_4 : 1;

	// Treinadores
	UINT64 Treinador_1 : 1;
	UINT64 Treinador_2 : 1;
	UINT64 Treinador_3 : 1;

	UINT64 Unicornio : 1;
	UINT64 MolarGargula : 1;

	UINT64 Block40Cele : 1,
           Block90Cele : 1,
           Block355Arch : 1, 
		   Block370Arch : 1;
  
	UINT64 SubCeleMade : 1;

	UINT64 Unknow : 6;

	bool ItensReceived[23];
} pQuestInfo;

struct p20D{
	PacketHeader Header; // 0 - 11

	char Login[16]; // 12 - 27
	char Password[12]; // 28 - 39

	INT32 Version; // 40 - 43
	INT32 Unknows; // 44- 47

	char Keys[16]; // 48 - 63
	char IPAddress[16]; // 64 - 79
};

struct p277
{
   PacketHeader Header;
   short Mode;
   short Info;
   int unk;
};

struct stBuffer{
        stAffects Affects[16];
        UINT8 Unknown[912];
};

struct stTarget
{
	UINT16 Index;
	UINT16 Damage;
};

typedef struct
{
    PacketHeader Header;
	UINT16 m_ClientId;
	UINT16 m_AttackCount;

	st_Position m_AttackerPosition;
	st_Position m_AffectedPosition;

	UINT16 m_SkillId;
	UINT16 m_CurrentMp;

	UINT8 m_Motion;
	UINT8 m_SkillParam;
	UINT8 m_FlagLocal;
	UINT8 m_Critical;

	UINT32 m_Hold;
	UINT32 m_CurrentExp;

	UINT16 m_ReqMp;
	UINT16 Unknown_42;

	stTarget m_Target;
} p39D_754;

typedef struct { 
	char Name[16];	 // 0 a 15 
	char CapeInfo;	 // 16 
	char Merchant;	 // 17 
	unsigned short GuildIndex;	 // 18 a 19 
	unsigned char ClassInfo;	 // 20 
	unsigned char AffectInfo;	 // 21 
	unsigned short QuestInfo;	 // 22 a 23 
	int Gold;	 // 24 a 27 
	unsigned int Exp;	 // 28 a 31 
	st_Position LastPosition;	 // 32 a 35 
	st_Status bStatus;	 // 36 a 63 
	st_Status Status;	 // 64 a 91 
	st_Item Equip[16];	 // 92 a 219 
	st_Item Inventory[64];	// 220 a 731 
	unsigned int Learn;	 // 732 a 735 
	unsigned short StatusPoint;	 // 736 a 737 
	unsigned short MasterPoint;	 // 738 a 739 
	unsigned short SkillPoint;	 // 740 a 741 
	unsigned char Critical;	 // 742 
	unsigned char SaveMana;	 // 743 
	char SkillBar[4];	 // 744 a 747 
	char GuildMemberType;	 // 748 
	unsigned char MagicIncrement;	// 749 
	unsigned char RegenHP;	 // 750 
	unsigned char RegenMP;	 // 751 
	char Resist1;	 // 752 
	char Resist2;	 // 753 
	char Resist3;	 // 754 
	char Resist4;	 // 755 
} stMOB754;

struct NewInvent
{
	st_Item sInv1[64],
			sInv2[64];	

	bool hasBuyed;
};

typedef struct
{
    BYTE SlowMov : 1;
    BYTE DrainHP : 1;
    BYTE VisionDrop : 1;
    BYTE Evasion : 1;
    BYTE Snoop : 1;
    BYTE SpeedMov : 1;
    BYTE SkillDelay : 1;
    BYTE Resist : 1;
} Affects;

struct NewPerso
{
	UINT8 ClassInfo;

	DWORD Exp;

	DWORD Learn;

    UINT16 StatusPoint,
		 MasterPoint,
		 SkillPoint;

	st_Status Stats;

	st_Item Face,
		    Capa;

	Affects AffectInfo;

	char SkillBar1[4];
    char SkillBar2[16];

	stAffects Affects[16];
};

struct p28F
{
	PacketHeader Header;
	WORD npcid;
	int BetValue;
};

struct p3D5
{
    PacketHeader Header;
    int RecruitCid;
    int dat2;
};

struct TradeEvent
{
	st_Item RequestItem[5],
		    SendedItem[5];

	INT8 Rates;
};

struct Events
{
	DropEvent Drop;
	TradeEvent Trade[6];
};

typedef struct ServerInfos
{
	// Status do SombraNegra
	int SombraNegra : 1;

	// Tempo do servidor online
	INT8 Seconds,
		 Minuts,
		 Hours,
		 Days;

	Events Event;
};

struct GuildInfos
{
	UINT32 FAME; // Fame total da guild

	char LiderName[16]; // Nick do lider
	char GuildName[20]; // Nome da guild

	char SubLiderName[3][16]; // Nome dos Subs

	UINT8 Kingdom; // Reino da guild, para comparação na hora de recrutar e para igualar
	               // No GetCreateMob

	UINT16 GuildID, // ID da guild
		   Members; // Número total de membros

	bool Posses[5]; // Cidades que possui

	UINT64 BetValue[4]; // Valor apostado em cada cidade

	INT64 WarPoints; // Pontos na war de terça e quinta

	// Infos referentes a func de transferência de liderança da guild
	bool transfer;
	INT8 confirmTransfer;
	char NewLiderName[16];
};

struct A03
{
	PacketHeader Header;

	GuildInfos Guild;
};

struct AAA
{
	PacketHeader Header;

	INT16 Type;
};

struct wdBase
{
	// Senha numérica
	char Numerica[6],
		 Login[16];

	UINT16 Cash; // Preciso nem falar o que é...

	stTime Ban; // Se estiver banido aqui vai mostrar a data do ban

	UINT8 AcessLevel;	

	struct 
	{
		stTime Date; // Data de validade do vip
		UINT8 Type; // Tipo do vip(plus, simples...)
		UINT8 RegenTime; // Tempo restante para a regen do supportmob
	}VipInfo;

	struct
	{
		// Aqui infos de personagens individualmente, acima, infos da conta em geral
		UINT16 NTs; // Entradas pro pesa
		UINT16 RvRPoints; // Pontos para comprar entradas para o RvR e outros itens

		UINT8 SoulInfo; // Configuração da soul (for/cons etc)
		UINT8 RespectiveMortal; // Mortal que criou o char caso seja arch+

		UINT8 Cidadania;// Define a cidadania do personagem
		
		INT32 Fame; // Fama do personagem

		pQuestInfo Quests; // Infos de conclusão de quests

		NewPerso Persos[2]; // Dados do cele/sub

		NewInvent nInvent;	// Dados do segundo inventário

		char SkillBar2[16]; // Segunda skillbar

		stAffects Affect[16]; // Pra ser usado posteriormente quando o save buffs for feito	

		INT32 ExpBonus;
	} Chars[4];

	struct 
	{
		// As infos escritas aqui não serão salvas
		bool isAdmin;

		bool isMod;

		int LoggedMob;

		struct 
		{
			bool isOn;
			WORD Id[5];
		}AutoDrop;

		char SND[60],
			 Tab[25];

		int userWhisper;

		UINT8 AcessLevel;

		INT16 LastClicked;

		// Quantas vezes o o usuário errou a senha numérica
		UINT8 IncorrectNumeric;

		// Passou pela numerica
		bool canLog;

		// Bônus de mg    
		INT16 MagicIncrement;

		INT8 ChatGlobal,
			 Grito,
			 RetectItem;

		INT16 hasFailed; // Para a skill ressu

		INT16 WarRestTime; // Tempo restante para ser ressucitado

		bool cantRessurect;

		UINT16 HpExtract,
			   MpExtract;
	}Ingame;
};

#define BOSSMORTO 2
#define BOSSNASCIDO 1
#define BOSSNAONASCIDO 0

struct CartasQuest
{
	// A~M~N
	INT8 Type,
		 ActualRoom,
		 bossState;
	// 0 = Boss não nasceu
	// 1 = Boss nasceu e ainda está vivo
	// 2 = Boss morreu

	bool isOn,
		 canGo;

	INT16 cIds[13],
		  TimeLeft,
		  MobsLeft;
};

struct p18A // SendRegenHp
{
	PacketHeader Header;

	UINT16 CurHP;
	INT16 Incress;
};

struct p28B//NPC CLICK
{
	PacketHeader Header;
	WORD npcid;
	BYTE Unknow1;
	BYTE Unknow2;
	short ClickOk;
};

struct DownPC
{
	PacketHeader Header;

	int Mode;
};

struct p802
{
	PacketHeader Header; // Offset 00
	int PosID; // Offset 12
	char NewCharName[16]; // Offset 16
	int ClassID; // Offset 32
};

struct p3B4 
{
    PacketHeader Header;
    BYTE Position;
};

struct p2E1h
{
	PacketHeader Header; // 0 - 11
	st_Item Item[3];//12 - 35
	UINT8 unk[40];// 36 - 75
	UINT8 Slot[3];
};

struct p373
{
	PacketHeader Header;
	DWORD SrcType, 
		  SrcSlot, 
		  DstType, 
		  DstSlot; 
	WORD     PosX, 
		     PosY; 
	DWORD    warp; 
};

struct pFDE{
	PacketHeader Header;
	char num[6];
	char unk[10];
	int RequestChange;
};

struct p182h
{
    PacketHeader Header;
    short invType;
    short invSlot;
    st_Item itemData;
};

struct p213 
{
	PacketHeader Header;
    int CharIndex;
    char Zero[18];
};

typedef struct 
{
	int Amount;
	int Slots[128];
	st_Item *Itens[128];
} FindAmountItem;

typedef struct 
{ 
	PacketHeader Header; 
	INT32 SlotIndex; 
	char Name[16]; 
	char Pwd[12]; 
} REQDELETECHAR; 

struct p379
{
	PacketHeader Header;
    short mobID;
    short sellSlot;
    short invSlot;
    short Unknown1;
    int Unknown2;
};

struct stAccount
{
	char Username[16]; 
	char Password[16]; 
	BYTE unk[0x10A4];
};

typedef struct
{
    PacketHeader Header;
    short npcId,
	      type;
    int sellSlot;
} p37A;

typedef struct
{
    PacketHeader Header;
    int Slot,
        mobId,
        Price,
        Tax;
    st_Item Item;
} p398;

typedef struct
{
	PacketHeader Header;

	st_Position WorldPos;

	char Name[16];
    char CapeInfo;

    struct
    {
        BYTE Merchant : 6;
        BYTE CityID : 2;
    } Info;

    WORD GuildIndex;
    BYTE ClassInfo;

	struct
    {
        BYTE SlowMov : 1;
        BYTE DrainHP : 1;
        BYTE VisionDrop : 1;
        BYTE Evasion : 1;
        BYTE Snoop : 1;
        BYTE SpeedMov : 1;
        BYTE SkillDelay : 1;
        BYTE Resist : 1;
    } AffectInfo;

    WORD QuestInfo;

    int Gold;
    int Exp;

    st_Position Last;
    st_Status bStatus;
    st_Status Status;

    st_Item Equip[16];
    st_Item Inventory[64];

    DWORD Learn;
    WORD pStatus;
    WORD pSkill;
    WORD pMaster;
    BYTE Critical;
    BYTE SaveMana;

    char SkillBar1[4];
    char GuildMemberType;

    BYTE MagicIncrement;
    BYTE RegenHP;
    BYTE RegenMP;

    BYTE Resist1, Resist2;
    BYTE Resist3, Resist4;

    short SlotIndex;
    short ClientIndex;
    short unk;

    char SkillBar2[16];
    short Evasion;
    int Hold;

    char Tab[28];
} p114;

struct stMOBGener
{
	UINT32 Mode; // 0 - 3
	UINT32 MinuteGenerate; // 4 - 7

	UINT32 MaxNumMob; // 8 - 11

	UINT32 MobCount; // 12 - 15
	
	UINT32 MinGroup; // 16 - 19
	UINT32 MaxGroup; // 20 - 23
	
	UINT32 Segment_X[5]; //24 - 43
	UINT32 Segment_Y[5]; // 44 - 63
	UINT32 StartRange; // 64 - 67
	
	UINT32 Segment1Range; // 68 - 71
	UINT32 Segment2Range; // 72 - 75
	UINT32 Segment3Range; // 76 - 79
	
	UINT32 DestRange; // 80 - 83
	
	UINT32 StartWait; // 84 - 87
	
	UINT32 Segment1Wait; // 88 - 91 ou Segment3Wait
	UINT32 Segment2Wait; // 92 - 95
	
	UINT32 Segment3Wait; // 96 - 99 // Não usado na TMsrv -> acho que é um erro, no ParseStrings ele move para o Segment1Wait o que está em Segmen3Wait e.e'

	UINT32 DestWait; // 100 - 103
	
	char SegmentAction[5][80]; // 104 - 503
	char FightAction[4][80]; // 504 - 823
	char FleeAction[4][80]; // 824 - 1143
	char DieAction[4][80]; // 1144 - 1463
	
	UINT32 Formation; // 1464 - 1467
	UINT32 RouteType; // 1468 - 1471 

	UINT32 Unknow; // 1472 - 1475 -> Ele pega o valor do MinuteGenerate (?)

	stMOB754 Leader; // 1476 - 2231	
	stMOB754 Follower; // 2232 - 2987
};

struct MSG_DBCreateArch
{
	PacketHeader Header;
	INT32 charSlot;
	stMOB754 mob;
};

struct p378
{
	PacketHeader Header;
    char SkillBar1[4];
    char SkillBar2[16];
};

struct p374
{
	PacketHeader Header;
	short InitID;
	int state;
    int height;
};

struct p366
{
    PacketHeader Header;
    short xSrc, ySrc;
    int mSpeed;
    int mType;
    short xDst, yDst;
    char mCommand[24];
};

struct pWindow
{
	PacketHeader Header;

	st_Item ItemId[7];

	UINT8 Slot[7];
};

typedef struct
{
	PacketHeader Header;

    st_Item ItemId[8];

    char Slot[8];

} st_Window;

struct pShany
{
	PacketHeader Header;

	st_Item ItemId[7];
	
	UINT8 Unk[18];

	UINT8 Slot[7];
};

struct pCL_181h // SHEPHER
{
	PacketHeader Header;

	unsigned short curHP;
	unsigned short curMP;
	unsigned short maxHP;
	unsigned short maxMP;
};

struct pCL_exitParty 
{
    PacketHeader Header;
    WORD clientId;
};

struct pD1D
{
    PacketHeader Header;
    char message[92];
    int color;
};
 
struct STRUCT_ACCOUNTFILE
{
	char AccountName[16];
	char AccountPass[12];
	st_Mob Char[4];
	st_Item Cargo[128];
	int Gold;
	int ssn1; // referente ao kssn china
	int ssn2; // referente ao kssn china
};

static const char Etc[] = {"1234567890!@#$&*_-=/'"};

//BaseEXP
static const unsigned int exp_table[400] = {
 0, 	 500u,       1124u,       1826u,       2610u,       3480u,       4440u,       5494u,       6646u,
        7900u,       9260u,      10893u,      12817u,      15050u,      17610u,      20515u,      23783u,
       27432u,      31480u,      35945u,      40845u,      46251u,      52187u,      58677u,      65745u,
       73415u,      81711u,      90657u,     100277u,     110595u,     121635u,     133647u,     146671u,
      160747u,     175915u,     192215u,     209687u,     228371u,     248307u,     269535u,     292095u,
      316151u,     341751u,     368943u,     397775u,     428295u,     460551u,     494591u,     530463u,
      568215u,     607895u,     649715u,     693731u,     739999u,     788575u,     839515u,     892875u,
      948711u,    1007079u,    1068035u,    1131635u,    1198670u,    1269230u,    1343405u,    1421285u,
     1502960u,    1588520u,    1678055u,    1771655u,    1869410u,    1971410u,    2078255u,    2190055u,
     2306920u,    2428960u,    2556285u,    2689005u,    2827230u,    2971070u,    3120635u,    3276035u,
     3438521u,    3608249u,    3785375u,    3970055u,    4162445u,    4362701u,    4570979u,    4787435u,
     5012225u,    5245505u,    5488163u,    5740379u,    6002333u,    6274205u,    6556175u,    6848423u,
     7151129u,    7464473u,    7788635u,    8123795u,    8460174u,    8797774u,    9136597u,    9476645u,
     9817920u,   10160424u,   10504159u,   10849127u,   11195330u,   11542770u,   11892311u,   12243959u,
    12597720u,   12953600u,   13311605u,   13671741u,   14034014u,   14398430u,   14764995u,   15133715u,
    15508850u,   15890450u,   16278565u,   16673245u,   17074540u,   17482500u,   17897175u,   18318615u,
    18746870u,   19181990u,   19625811u,   20078403u,   20539836u,   21010180u,   21489505u,   21977881u,
    22475378u,   22982066u,   23498015u,   24023295u,   24559110u,   25105558u,   25662737u,   26230745u,
    26809680u,   27399640u,   28000723u,   28613027u,   29236650u,   29871690u,   30517485u,   31174125u,
    31841700u,   32520300u,   33210015u,   33910935u,   34623150u,   35346750u,   36081825u,   36828465u,
    37587867u,   38360139u,   39145389u,   39943725u,   40755255u,   41580087u,   42418329u,   43270089u,
    44135475u,   45014595u,   45904870u,   46806370u,   47719165u,   48643325u,   49578920u,   50526020u,
    51484695u,   52455015u,   53437050u,   54430870u,   55439542u,   56463162u,   57501826u,   58555630u,
    59624670u,   60709042u,   61808842u,   62924166u,   64055110u,   65201770u,   66366010u,   67547930u,
    68747630u,   69965210u,   71200770u,   72454410u,   73726230u,   75016330u,   76324810u,   77651770u,
    78985354u,   80325578u,   81672458u,   83026010u,   84386250u,   85753194u,   87126858u,   88507258u,
    89894410u,   91288330u,   92693002u,   94108458u,   95534730u,   96971850u,   98419850u,   99878762u,
   101348618u,  102829450u,  104321290u,  105824170u,  107352234u,  108905674u,  110484682u,  112089450u,
   113720170u,  115377034u,  117060234u,  118769962u,  120506410u,  122269770u,  124065890u,  125895058u,
   127757562u,  129653690u,  131583730u,  133547970u,  135546698u,  137580202u,  139648770u,  141752690u,
   143928178u,  146176386u,  148498466u,  150895570u,  153368850u,  155919458u,  158548546u,  161257266u,
   164046770u,  166918210u,  169956978u,  173167682u,  176554930u,  180123330u,  205345890u,  209100050u,
   212902550u,  216753470u,  220652890u,  224600890u,  228597550u,  232642950u,  236737170u,  240880290u,
   245072390u,  249313550u,  253603850u,  257943370u,  262332190u,  266770390u,  271258050u,  275795250u,
   280382070u,  285018590u,  289904810u,  295042730u,  300434350u,  306081670u,  311986690u,  318151410u,
   324577830u,  331267950u,  338223770u,  345447290u,  354039310u,  364049830u,  375528850u,  388526370u,
   403092390u,  419276910u,  437129930u,  456701450u,  476272970u,  495844490u,  515416010u,  534987530u,
   554559050u,  574130570u,  593702090u,  613273610u,  632845130u,  652416650u,  671988170u,  691559690u,
   711131210u,  730702730u,  750274250u,  769845770u,  789417290u,  808988810u,  828560330u,  848131850u,
   867703370u,  887274890u,  906846410u,  926417930u,  945989450u,  965560970u,  985132490u, 1004704010u,
  1024275530u, 1043847050u, 1063418570u, 1082990090u, 1102561610u, 1122133130u, 1141704650u, 1161276170u,
  1180847690u, 1200419210u, 1222705731u, 1244995262u, 1267288477u, 1289622601u, 1311966887u, 1334333102u,
  1356724650u, 1379151914u, 1401651370u, 1424151231u, 1448674779u, 1473220997u, 1497782544u, 1522364697u,
  1546957043u, 1571581919u, 1596243411u, 1620925875u, 1645647464u, 1670373305u, 2000000000u, 2000000000u,
  2000000000u, 2000000000u, 2039000000u, 2078000000u, 2117000000u, 2156000000u, 2195000000u, 2234000000u,
  2273000000u, 2312000000u, 2351000000u, 2390000000u, 2429000000u, 2468000000u, 2507000000u, 2546000000u,
  2585000000u, 2624000000u, 2663000000u, 2702000000u, 2741000000u, 2780000000u, 2819000000u, 2858000000u,
  2897000000u, 2936000000u, 3000000000u, 3043000000u, 3086000000u, 3129000000u, 3172000000u, 3215000000u,
  3258000000u, 3301000000u, 3344000000u, 3387000000u, 3430000000u, 3473000000u, 3516000000u, 3559000000u,
  3602000000u, 3645000000u, 3688000000u, 3731000000u, 3774000000u, 3817000000u, 4000000000u
};

static const UINT32 exp_table_2[200] = {
0,  20000000u,   40000000u,   60000000u,   80000000u,   100000000u,  120000000u,  140000000u,  160000000u,  180000000u,  200000000u,  220000000u, 240000000u,
	260000000u,  280000000u,  300000000u,  320000000u,  340000000u,  360000000u,  380000000u,  400000000u,  420000000u,  440000000u,  460000000u, 480000000u,
	500000000u,  520000000u,  540000000u,  560000000u,  580000000u,  600000000u,  620000000u,  640000000u,  660000000u,  680000000u,  700000000u, 720000000u,
	740000000u,  760000000u,  780000000u,  800000000u,  820000000u,  840000000u,  860000000u,  880000000u,  900000000u,  920000000u,  940000000u, 960000000u,
	980000000u,  1000000000u, 1020000000u, 1040000000u, 1060000000u, 1080000000u, 1100000000u, 1120000000u, 1140000000u, 1160000000u, 1180000000u,
	1200000000u, 1220000000u, 1240000000u, 1260000000u, 1280000000u, 1300000000u, 1320000000u, 1340000000u, 1360000000u, 1380000000u, 1400000000u,
	1420000000u, 1440000000u, 1460000000u, 1480000000u, 1500000000u, 1520000000u, 1540000000u, 1560000000u, 1580000000u, 1600000000u, 1620000000u,
	1640000000u, 1660000000u, 1680000000u, 1700000000u, 1720000000u, 1740000000u, 1760000000u, 1780000000u, 1800000000u, 1820000000u, 1840000000u,
	1860000000u, 1880000000u, 1900000000u, 1920000000u, 1940000000u, 1960000000u, 1980000000u, 2000000000u, 2020000000u, 2040000000u, 2060000000u,
	2080000000u, 2100000000u, 2120000000u, 2140000000u, 2160000000u, 2180000000u, 2200000000u, 2220000000u, 2240000000u, 2260000000u, 2280000000u,
	2300000000u, 2320000000u, 2340000000u, 2360000000u, 2380000000u, 2400000000u, 2420000000u, 2440000000u, 2460000000u, 2480000000u, 2500000000u,
	2520000000u, 2540000000u, 2560000000u, 2580000000u, 2600000000u, 2620000000u, 2640000000u, 2660000000u, 2680000000u, 2700000000u, 2720000000u,
	2740000000u, 2760000000u, 2780000000u, 2800000000u, 2820000000u, 2840000000u, 2860000000u, 2880000000u, 2900000000u, 2920000000u, 2940000000u,
	2960000000u, 2980000000u, 3000000000u, 3020000000u, 3040000000u, 3060000000u, 3080000000u, 3100000000u, 3120000000u, 3140000000u, 3160000000u,
	3180000000u, 3200000000u, 3220000000u, 3240000000u, 3260000000u, 3280000000u, 3300000000u, 3320000000u, 3340000000u, 3360000000u, 3380000000u,
	3400000000u, 3420000000u, 3440000000u, 3460000000u, 3480000000u, 3500000000u, 3520000000u, 3540000000u, 3560000000u, 3580000000u, 3600000000u,
	3620000000u, 3640000000u, 3660000000u, 3680000000u, 3700000000u, 3720000000u, 3740000000u, 3760000000u, 3780000000u, 3800000000u, 3820000000u,
	3840000000u, 3860000000u, 3880000000u, 3900000000u, 3920000000u, 3940000000u, 3960000000u, 4000000000u,
};

static const int CompoeSecretas[4][8] = {
	{5126, 5122, 5121, 5114, 5125, 5111, 5118, 5334},
	{5131, 5113, 5115, 5116, 5125, 5112, 5114, 5335},
	{5110, 5124, 5117, 5129, 5114, 5125, 5128, 5336},
	{5122, 5119, 5132, 5120, 5130, 5133, 5123, 5337},
};

static const int MesesConfig[] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int Configs[][3] = {
		{2442, 2443, 2444}, {2442, 2441, 2443}, {2444, 2441, 2443}, 
		{2443, 2442, 2444}, {2441, 2441, 2441}, {2442, 2442, 2442}, 
		{2443, 2443, 2443}, {2444, 2444, 2444}, {2441, 2442, 2443}, {2441, 2443, 2444}
};

static const int CeleStatsBonuse[][4] = {
		{120,   0,   0,   0},
		{  0, 120,   0,   0},
		{  0,   0, 120,   0},
		{  0,   0,   0, 120},
		{ 80,   0,   0,  40},
		{  0,  80,   0,  40},
		{  0,   0,  80,  40},
		{ 40,   0,   0,  80},
		{  0,  40,   0,  80},
		{  0,   0,  40,  80},
};

static const int MortalStatsBonuse[][4] = {
		{100,   0,   0,   0},
		{  0, 100,   0,   0},
		{  0,   0, 100,   0},
		{  0,   0,   0, 100},
		{ 70,   0,   0,  30},
		{  0,  70,   0,  30},
		{  0,   0,  70,  30},
		{ 30,   0,   0,  70},
		{  0,  30,   0,  70},
		{  0,   0,  30,  70},
};

static const int Capas[] = {3197, 3198, 3199, 3503, 3504, 3505, 3506};

static const int NotReplation[] = {
	1221, 1222, 1223, 1224, 1356, 1357, 1358, 1359, 1506, 1507, 
	1508, 1509, 1656, 1657, 1658, 1659, 1230, 1231, 1232, 1233, 
	1365, 1366, 1367, 1368, 1515, 1516, 1517, 1518, 1665, 1666, 
	1667, 1668
};

static const int CheckAllReplations [] = {
	1101, 1102, 1103, 1104, 1105, 1106, 1113, 1114, 1115, 1116, 1117, 1578, 1579, 1580,
	1118, 1125, 1126, 1127, 1128, 1129, 1130, 1137, 1138, 1139, 1140, 1141, 1142, 1149,
	1150, 1151, 1152, 1153, 1154, 1251, 1252, 1253, 1254, 1255, 1256, 1263, 1264, 1265,
	1266, 1267, 1268, 1275, 1276, 1277, 1278, 1279, 1280, 1287, 1288, 1289, 1290, 1291,
	1292, 1299, 1300, 1301, 1302, 1303, 1304, 1401, 1402, 1403, 1404, 1405, 1406, 1407,
    1408, 1409, 1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420, 1421,
    1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430, 1551, 1552, 1553, 1554, 1555,
    1556, 1557, 1558, 1559, 1560, 1561, 1562, 1563, 1564, 1565, 1566, 1567, 1568, 1569,
    1570, 1571, 1572, 1573, 1574, 1575, 1576, 1577, 1107, 1108, 1109, 1110, 1111, 1112, 
	1119, 1120, 1121, 1122, 1123, 1124, 1131, 1132, 1133, 1134, 1135, 1136, 1143, 1144, 
	1145, 1146, 1147, 1148, 1155, 1156, 1157, 1158, 1159, 1160, 1257, 1258, 1259, 1260, 
	1272, 1273, 1274, 1281, 1282, 1283, 1284, 1285, 1286, 1293, 1294, 1295, 1296, 1297,
	1298, 1305, 1306, 1307, 1308, 1309, 1310, 1431, 1432, 1433, 1434, 1435, 1436, 1437,
    1438, 1439, 1440, 1441, 1442, 1443, 1444, 1445, 1446, 1447, 1448, 1449, 1450, 1451,
    1452, 1453, 1454, 1455, 1456, 1457, 1458, 1459, 1460, 1581, 1582, 1583, 1584, 1585,
    1586, 1587, 1588, 1589, 1590, 1591, 1592, 1593, 1594, 1595, 1596, 1597, 1598, 1599,
    1600, 1601, 1602, 1603, 1604, 1605, 1606, 1607, 1608, 1609, 1610, 1261, 1262, 1269, 
	1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169, 1170, 1171, 1270, 1271, 1625,
	1172, 1173, 1174, 1175, 1176, 1177, 1178, 1179, 1180, 1181, 1182, 1183, 1184, 1185,
	1186, 1187, 1188, 1189, 1190, 1311, 1312, 1313, 1314, 1315, 1316, 1317, 1318, 1319,
	1320, 1321, 1322, 1323, 1324, 1325, 1461, 1462, 1463, 1464, 1465, 1466, 1467, 1468,
	1469, 1470, 1471, 1472, 1473, 1474, 1475, 1611, 1612, 1613, 1614, 1615, 1616, 1617,
    1618, 1619, 1620, 1621, 1622, 1623, 1624, 1660, 1661, 1662, 1663, 1664, 1513, 1514, 
	1191, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199, 1200, 1201, 1511, 1512, 1510,
	1202, 1203, 1204, 1205, 1206, 1207, 1208, 1209, 1210, 1211, 1212, 1213, 1214, 1215,
	1216, 1217, 1218, 1219, 1220, 1326, 1327, 1328, 1329, 1330, 1331, 1332, 1333, 1334,
	1335, 1336, 1337, 1338, 1339, 1340, 1341, 1342, 1343, 1344, 1345, 1346, 1347, 1348,
	1349, 1350, 1351, 1352, 1353, 1354, 1355, 1476, 1477, 1478, 1479, 1480, 1481, 1482,
    1483, 1484, 1485, 1486, 1487, 1488, 1489, 1490, 1491, 1492, 1493, 1494, 1495, 1496,
    1497, 1498, 1499, 1500, 1501, 1502, 1503, 1504, 1505, 1626, 1627, 1628, 1629, 1630,
    1631, 1632, 1633, 1634, 1635, 1636, 1637, 1638, 1639, 1640, 1641, 1642, 1643, 1644,
    1645, 1646, 1647, 1648, 1649, 1650, 1651, 1652, 1653, 1654, 1655, 1362, 1363, 1364, 
	1225, 1226, 1227, 1228, 1229, 1360, 1361 
};

static const int add_critical[7] = { 0, 35, 40, 45, 50, 60, 0},
		         add_ac[6] = { 0, 10, 15, 20, 25, 25 },
		         add_damage[5] = { 0, 9, 18, 24, 30 },
		         add_magic[5] = { 0, 4, 6, 8, 10 },
		         add_attspeed[8] = { 0, 3, 6, 9, 10, 12, 15, 18 },
		         add_hp[3] = { 40, 50, 60 },
		         add_skill[8] = { 2, 4, 6, 8, 10, 12, 15, 18 };

static const int HuntingScrolls[6][10][2] = { 
	//Armia
	{//OK
		{2370, 2106}, {2508, 2101}, {2526, 2009}, {2529, 1882}, {2126, 1600}, {2005, 1617},
		{2241, 1474}, {1858, 1721}, {2250, 1316}, {1989, 1755}
	},
	//Dungeon
	{// OK
		{290, 3799}, {724, 3781}, {481, 4062}, {876, 4058}, {855, 3922}, {808, 3876},
		{959, 3813}, {926, 3750}, {1096, 3730}, {1132, 3800}
	},
	//SubMundo
	{
		{1242 , 4035}, {1264 , 4017}, {1333 , 3994}, {1358 , 4041}, {1462 , 4033}, {1326 , 3788},
		{1493 , 3777}, {1437 , 3741}, {1389 , 3740}, {1422 , 3810}
	},
	//Kult
	{//OK
		{1376 , 1722},
		{1426 , 1686},
		{1381 , 1861},
		{1326 , 1896},
		{1510 , 1723},
		{1543 , 1726},
		{1580 , 1758},
		{1182 , 1714},
		{1634 , 1727},
		{1237 , 1764}
	},
	//Kefra
	{// ok
		{2367 , 4024},
		{2236 , 4044},
		{2236 , 3993},
		{2209 , 3989},
		{2453 , 4067},
		{2485 , 4043},
		{2534 , 3897},
		{2489 , 3919},
		{2269 , 3910},
		{2202 , 3866}
	},
	//Nipple
	{
		{3664 , 3024},
		{3582 , 3007},
		{3514 , 3008},
		{3819 , 2977},
		{3517 , 2889},
		{3745 , 2977},
		{3639 , 2877},
		{3650 , 2727},
		{3660 , 2773},
		{3746 , 2879}
	}
};

static const int ArchNoEquip[] = {	
	1230, 1231, 1232, 1233,	1365, 1366, 1367, 1368, // melpomene / potamides
	1515, 1516, 1517, 1518,	1665, 1666, 1667, 1668, // driade / urania
	1901, 3605, 3606, 3607, 3608, // Machado_Gaoth
	1902, 3625, 3626, 3627, 3628, // Eithna
	1903, 3645, 3646, 3647, 3648, // Lupercus
	1904, 3665, 3666, 3664, 3668, // Gae_Bulg
	1905, 3685, 3686, 3687, 3688, // Tyrfing
	1906, 3705, 3706, 3707, 3708, // Kenten
	1907, 3729, 3730, 3731, 3732, // Cetro
	1908, 3733, 3734, 3735, 3736, // Dordje
	1909, 3765, 3766, 3767, 3768, // Hrotti
	1910, 3785, 3786, 3787, 3788  // Martelo_Kaumodaki
};  

static const int MortalNoEquip[] = {	
	1221, 1222, 1223, 1224, 1230, 1231, 1232, 1233, // flame / melpomene
	1356, 1357, 1358, 1359, 1365, 1366, 1367, 1368, // guard / potamides
	1506, 1507, 1508, 1509, 1515, 1516, 1517, 1518, // destru / driade
	1656, 1657, 1658, 1659, 1665, 1666, 1667, 1668, // rake / urania
	1901, 3605, 3606, 3607, 3608, // Machado_Gaoth
	1902, 3625, 3626, 3627, 3628, // Eithna
	1903, 3645, 3646, 3647, 3648, // Lupercus
	1904, 3665, 3666, 3664, 3668, // Gae_Bulg
	1905, 3685, 3686, 3687, 3688, // Tyrfing
	1906, 3705, 3706, 3707, 3708, // Kenten
	1907, 3729, 3730, 3731, 3732, // Cetro
	1908, 3733, 3734, 3735, 3736, // Dordje
	1909, 3765, 3766, 3767, 3768, // Hrotti
	1910, 3785, 3786, 3787, 3788  // Martelo_Kaumodaki
};  

static char BossWaterMobs[3][2][16] = 
{
	{
		"Troll_Nieger",
        "Cacador_Troll"
	},
	{
		"Hidra_Miger",
        "Hidra_Agua"
	},
	{
		"Lugefer_Acos",
        "Gargula__"
	}
};

static char WaterMobs[3][8][16] = {
	{
		"Meio_Orc_____",
	    "Cacador_Troll",
		"Chefe_Ghoul",
		"Ciclope_Arq__",
		"Evo_Caveira",
		"Lock_Dourado",
		"Ciclope",
		"Ninja_Evo",
	},
	{
	    "Elfo_Negro__",
	    "Troll_Ghoul_",
		"Anf_Assassino_",
		"Tauron_",
		"Grim_Lock_",
		"Bruxa_Elfica_",
		"Gargula_",
		"Aqua_Golem_",
	},
	{
	    "Gargula__",
	    "Golem_de_Fogo",
		"Tauron_",
		"Dragao_Lich_",
		"Cav._Negro__",
		"Morlock____",
		"Aranha_Inferno_",
		"WriggleSwarm",
	}
};

static char CartasBoss[3][20] = 
{
	"Barack",//A
	"Sirius",//M
	"Zurica"//N
};

static char CartasMobs[3][4][20] = 
{
	{// Carta A
		"Nefetus_Nier",
		"Bareg",
		"Nostic",
		"Morg"
	},
	{// Carta M
		"Aldebaram",
		"Utir",
		"Mars",
		"Otuno"
	},
	{// Carta N
		"Conet",
		"Sarah",
		"Princess",
		"Armageddon"
	}
};

static const int CartasNum[3][5] = {
	{
		100, 100, 100, 100, 1
	},
	{
		100, 100, 100, 100, 1
	},
	{
		100, 100, 100, 100, 1
	}
};

static const INT8 BossNum[3][2] = {
	{1, 10},
	{1, 10},
	{1, 10}
};

static const UINT8 WaterNum[3][8] = {
	{
		15, 15, 15, 15, 15, 15, 15, 15
	},
	{
		15, 15, 15, 15, 15, 15, 15, 15
	},
	{
		15, 15, 15,  5, 15, 15, 15, 15
	}
};

static const UINT16 WaterIds[3][10] = {
	{
		3173, 3174, 3175, 3176, 3177, 3178, 3179, 3180, 3181, 0
	},
	{
		777, 778, 779, 780, 781, 782, 783, 784, 785, 0
	},
	{
		3182, 3183, 3184, 3185, 3186, 3187, 3188, 3189, 3190, 0
	}
};

static const INT16 LettersVCoords[4][4] = {
		{776, 3648, 824, 3696},
		{832, 3648, 880, 3696},
		{832, 3592, 880, 3640},
		{776, 3592, 824, 3640}
};

static const INT16 LettersSMCoords[4][4][2] = {
	{// Sala 1
		{800, 3684},
		{816, 3684}, 
		{801, 3670},
		{815, 3670},
	},
	{// Sala 2
		{860, 3681},
		{871, 3681},
		{866, 3677},
		{866, 3672},
	},
	{// Sala 3
		{861, 3625},
		{869, 3625},
		{860, 3619},
		{872, 3619},
	},
	{// Sala 4
		{803, 3606},
		{816, 3609},
		{803, 3637},
		{816, 3632},
	}
	// Sala BOSS: 807, 3621
};

static const INT16 TeleportCarta[4][2] = {
	{785, 3688}, 
	{843, 3688},
	{843, 3632},
	{785, 3640}
};

static const INT16 WaterMMCoords[3][9][4] = {
	{
		{1117, 3549, 1126, 3558},
		{1081, 3549, 1090, 3558},
		{1044, 3548, 1055, 3558},
		{1045, 3513, 1054, 3522},
		{1045, 3477, 1054, 3486},
		{1081, 3477, 1090, 3486},
		{1117, 3477, 1126, 3486},
		{1117, 3513, 1126, 3522},
		{1075, 3506, 1098, 3529}
	},
	{
		{1245, 3677, 1254, 3686},
		{1209, 3677, 1218, 3686},
		{1172, 3676, 1183, 3686},
		{1173, 3641, 1182, 3650},
		{1173, 3605, 1182, 3614},
		{1209, 3605, 1218, 3614},
		{1245, 3605, 1254, 3614},
		{1245, 3641, 1254, 3650},
		{1203, 3633, 1228, 3657}
	},
	{
		{1368, 3545, 1388, 3564},
		{1337, 3549, 1346, 3558},
		{1300, 3548, 1311, 3558},
		{1301, 3513, 1310, 3522},
		{1301, 3477, 1310, 3486},
		{1337, 3477, 1346, 3486},
		{1373, 3477, 1382, 3486},
		{1373, 3513, 1382, 3522},
		{1331, 3506, 1354, 3530}
	}
};

static const INT16 BossCoords[3][2] = {
	{1087, 3518},
	{1216, 3645},
	{1342, 3517}
};

static const INT16 WaterCoords[3][8][2] = {
	{
		// Salas Água N
		{1121, 3556},
		{1085, 3556},
		{1049, 3556},
		{1049, 3520},
		{1049, 3484},
		{1085, 3484},
		{1121, 3484},
		{1121, 3520}
	},
	{
		// Salas Água M
		{1249, 3684},
		{1213, 3684},
		{1177, 3684},
		{1177, 3648},
		{1177, 3612},
		{1213, 3612},
		{1249, 3612},
		{1249, 3648}
	},
	{
		// Salas Água A
		{1378, 3554},
		{1342, 3553},
		{1306, 3554},
		{1306, 3518},
		{1306, 3482},
		{1342, 3482},
		{1378, 3481},
		{1378, 3518}
	}
};

static const INT16 DontRefine[] = {
		1742,1760,1761,1762,1763,1752,1753,1754,1755,1756,1757,1758,1759,3397,3398,3399,
        3400,3401,3402,3403,3404,3405,3406,3197,3198,3199,1744,1745,1746,1747,1748,1749,1750,1751,
        3407,3408,3409,3410,3411,3412,3413,3414,3415,3416,3199,3198,3197,508,509,526,527,528
};

static const INT16 MobFaces[8] = {206, 225, 226, 244, 227, 245, 307, 396};

static const INT16 ClassLevel[] = { 
	30, 35, 40, 45, 50, 
	85, 90, 95, 100, 105,
	120, 125, 130, 135, 140,
	150, 160, 170, 180, 190, 200,
	// Armas
	155, 255
};

static const INT16 Armas[4][4] = {
    {// TK
            2137, 810, // MG - DN - 156
            3566, 3551 // MG - DN - 256
    },
    {// FM
            2128, 2122, // MG - DN - 156
            3582, 3556 // MG - DN - 256
    },
    {// BM
            2137, 810, // MG - DN - 156
            3566, 3551 // MG - DN - 256
    },
    {// HT
            840,  2122, // MG - DN - 156
            3561, 3556 // MG - DN - 256
    }
};

static const INT8 Pos[23] = {
	0, 1, 2, 3, 4,
	0, 1, 2, 3, 4,
	0, 1, 2, 3, 4,
	0, 1, 2, 3, 4,
	0, 1, 2
};

static const INT16 szItens[4][23] = {
    {// TK
            1147, 1159, 2152, 2156, 2154, //Manoplas - Botas  - Elmo - Calça - Armadura 
            1879, 1880, 1177, 1183, 1877,
            2029, 2030, 2026, 2028, 2027,
            2368, 1216, 1219, 1207, 1213, 
			1210, 0, 0
    },
    {// FM
            1297, 1309, 1261, 1285, 2164,
            1889, 1324, 1312, 1318, 1887,
            1899, 1900, 1896, 1898, 1897,
            2368, 1351, 1354, 1342, 1348,
			1345, 0, 0
    },
    {// BM
            1456, 1459, 1991, 1993, 1992,
            1471, 1474, 1996, 1998, 1997,
            1486, 1489, 1477, 1483, 1480,
            2368, 1501, 1504, 1492, 1498, 
			1495, 0, 0
    },
    {// HT
            1606, 1609, 1597, 1603, 2082,
            1621, 1624, 1612, 1618, 1615,
            1636, 1639, 1627, 1633, 1630,
            2368, 1651, 1654, 1642, 1648,
			1645, 0, 0
    }
};

static const INT8 Joia[] = {1, 2, 4, 0, 8, 16, 32, 0, 64, 128};

static int BaseSIDCHM[4][6] = {
    { 8, 4,  7, 6, 80, 45 }, // Transknight
    { 5, 8,  5, 5, 60, 65 }, // Foema
    { 6, 6,  9, 5, 70, 55 }, // BeastMaster
    { 8, 9, 13, 6, 75, 60 }  // Hunter
};

static const INT16 NoTiaras[] = {
	3500, 3501, 3502, 3503, 3504, 3505, 3506, 3507
};

static const INT16 NotSell[] = {
	508, 509, 526, 527, 528, 3503, 3504, 3505, 3506, 3980, 3981, 3982, 3983, 3984, 3985, 3986,
	3987, 3987, 3988, 3989, 4152, 4153, 4155, 4156
};

static const INT16 NotRef[] = {
	540, 541, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 
	567, 568, 569, 570, 591, 592, 593, 594, 595, 631, 632, 633, 1738, 661, 662, 663
};

static const INT16 KingDomCape[2][5] = 
{
	{ // Blue
		545, 543, 3191, 3194, 3197
	}, 
	{ // Red
		546, 544, 3192, 3195, 3198
	}
};

static const INT16 CapeBroker[] =
	{ // White
		548, 549, 3193, 3196, 3199
	};

// Configuração dos leveis permitidos nas quests
static const INT16 Quests_Level[5][2] = { 
	{40, 115},  // Coveiro
	{116, 190}, // Jardim
	{191, 265}, // Kaizen
	{266, 320}, // Mana
	{321, 350}  // Elfo
};

static const INT16 MaxMinPesaCoords[3][4] = 
{
	{1150, 130, 1270, 220}, // Pesa A
	{1040, 260, 1135, 350}, // Pesa M
	{1295, 290, 1325, 365}  // Pesa N
};

// Configuração das coordenadas das quests
static const INT16 CoordsQuest[5][2] =
{
	{2397, 2105}, // Coveiro
	{2234, 1714}, // Jardim
	{464,  3902}, // Kaizen
	{668,  3755}, // Mana
	{1326, 4043}  // Elfo
};

static const INT16 MaxMinCoordsQuest[5][4] = 
{
	{2379, 2077, 2426, 2133}, // Coveiro
	{2227, 1699, 2258, 1729}, // Jardim
	{ 458, 3886,  496, 3917}, // Kaizen
	{ 655, 3728,  706, 3765}, // Hydra
	{1313, 4030, 1353, 4058}  // Elfos
};

static const INT16 MaxMinCoordsGuilds[5][4] = 
{
	{2072, 2139, 2101, 2157}, // Armia
	{2449, 1968, 2469, 1982}, // Erion
	{2529, 1680, 2554, 1709}, // Azran
	{3606, 3101, 3631, 3143}, // Gelo
	{1039, 1756, 1072, 1771}  // Noatum
};

static const INT16 MaxMinCoordsWar[4][4] = 
{
	{195, 211, 240, 232},
	{139, 211, 184, 232},
	{195, 147, 240, 168},
	{139, 147, 184, 168}
};

static const INT16 CoordsReturnArea[4][2] = 
{
	{2100, 2100}, // Armia
	{2503, 1716}, // Azran
	{2462, 2000}, // Erion
	{3650, 3127}, // Gelo
};

// Configuração das exps ganhas nos itens de quest
static const signed long int ExpQuests[5] = 
{
	5000,   // Coveiro
	10000,  // Jardim
	50000,  // Kaizen
	100000, // Mana
	200000  // Elfo
};

static const INT16 MaxMinCoordsCitys[4][4] = 
{
	{2063, 2062, 2150, 2159}, // Armia
	{2459, 1646, 2665, 1765}, // Azran
	{2449, 1968, 2474, 2023}, // Erion
	{3606, 3101, 3687, 3159}  // Karden
};

static const char szCitys[4][7] =
{
	"Armia", "Azran", "Erion", "Karden"
};

static const INT16 SombraItens[3] = 
{
	5128, 5129, 5130
};

static const INT8 SombraRates[3] = 
{
	50, 70, 90
};

static const char Evolution[6][20] =
{
	"Mortal", "Arch", "Celestial", "Sub Celestial", "HardCore", "Sub HardCore"
};

static INT16 ItensReceive[] = 
{
	817, 862, 892
};

static INT16 ItensDelivery[] = 
{
	943, 939, 940
};

static const INT16 MountCheck[7][4] = 
{
	{
		2363, 2364, 2365, 0
	},
	{
		2367, 2368, 2372, 2373
	},
	{
		2369, 2370, 2374, 2375
	},
	{
		2376, 2377, 2378, 0
	},
	{
		2381, 2382, 2383, 0
	},
	{
		2384, 2385, 2386, 0
	},
	{
		2379, 2380, 2387, 2388
	}
};

static const int szRefis[6][2] = 
{
	{230, 233},
	{234, 237},
	{238, 241},
	{242, 245},
	{246, 249},
	{250, 253}
};

static const INT16 NotCharms[] = 
{
	540, 541, 551, 552, 553, 554, 555, 556, 557, 558, 559, 
	560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 
	591, 592, 593, 594, 595, 633, 1738, 661, 662, 663
};

static const INT16 AbsVerific[2] = {540, 541},
		           AbsDelivery[3] = {631, 632, 633};

#define CLIVER 2915

#endif // __BASE_STRUCTURES_H__